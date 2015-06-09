L.TileLayer.BetterWMS = L.TileLayer.WMS.extend({
    onAdd: function(map) {
        // Triggered when the layer is added to a map.
        // Register a click listener, then do all the upstream WMS things
        L.TileLayer.WMS.prototype.onAdd.call(this, map);
        map.on('click', this.getFeatureInfo, this);
    },
    onRemove: function(map) {
        // Triggered when the layer is removed from a map.
        // Unregister a click listener, then do all the upstream WMS things
        L.TileLayer.WMS.prototype.onRemove.call(this, map);
        map.off('click', this.getFeatureInfo, this);
    },
    getFeatureInfo: function(evt) {
        // Make an AJAX request to the server and hope for the best
        var url = this.getFeatureInfoUrl(evt.latlng),
            showResults = L.Util.bind(this.showGetFeatureInfo, this);
        $.ajax({
            url: url,
            success: function(data, status, xhr) {
                var err = typeof data === 'string' ? null : data;
                showResults(err, evt.latlng, data);
            },
            error: function(xhr, status, error) {
                showResults(error);
            }
        });
    },
    getFeatureInfoUrl: function(latlng) {
        // Construct a GetFeatureInfo request URL given a point
        var point = this._map.latLngToContainerPoint(latlng, this._map.getZoom()),
            size = this._map.getSize(),
            params = {
                request: 'GetFeatureInfo',
                service: 'WMS',
                srs: 'EPSG:4326',
                styles: this.wmsParams.styles,
                transparent: this.wmsParams.transparent,
                version: this.wmsParams.version,
                format: this.wmsParams.format,
                bbox: this._map.getBounds().toBBoxString(),
                height: size.y,
                width: size.x,
                layers: this.wmsParams.layers,
                query_layers: this.wmsParams.layers,
                info_format: 'text/html'
            };
        params[params.version === '1.3.0' ? 'i' : 'x'] = point.x;
        params[params.version === '1.3.0' ? 'j' : 'y'] = point.y;
        return this._url + L.Util.getParamString(params, this._url, true);
    },
    showGetFeatureInfo: function(err, latlng, content) {
        if (err) {
            //console.log(err);
            return;
        } // do nothing if there's an error
        // Otherwise show the content in a popup, or something.
        L.popup({
                maxWidth: 800
            })
            .setLatLng(latlng)
            .setContent(content)
            .openOn(this._map);
    }
});

L.tileLayer.betterWms = function(url, options) {
    return new L.TileLayer.BetterWMS(url, options);
};

(function($) {

    var datepicker_dates = {};
    var slider_dates = {};

    $(document).bind('leaflet.map', function(e, map, lMap) {
	/*
		var load_fire = 0;

        $('.quicktabs-style-biopama').eq(0).find('a.quicktabs-tab:contains("Fires")').click(function() {
			if (load_fire == 0){
				load_fire=1;
				$.getScript( "/sites/all/themes/biopama_bootstrap_subtheme/js/themes/fires.js", function( data ) {
					    console.log( data ); // Data returned
				});
				alert("Fire loaded");
			}
        }); */


        var url = 'http://geo.gob.bo/geoserver/ows?SERVICE=WMS';
        var geobov = L.tileLayer.betterWms(url, {
            layers: 'mddryt:CoberturaUso2010',
            transparent: true,
            format: 'image/png'
        })

        var local_municipios = L.tileLayer.betterWms('http://h05-dev-vm32.jrc.it:8080/geoserver/pacsbio/wms?SERVICE=WMS', {
            layers: 'pacsbio:municipios',
            transparent: true,
            format: 'image/png'
        })

        mbUrl = 'https://{s}.tiles.mapbox.com/v3/{id}/{z}/{x}/{y}.png';

        var grayscale = L.tileLayer(mbUrl, {
                id: 'examples.map-20v6611k'
            }),
            streets = L.tileLayer(mbUrl, {
                id: 'examples.map-i86knfo3'
            });

        var baseMaps = [{
            groupName: "Map base layers",
            expanded: true,
            layers: {

                "Grayscale": grayscale,
                "Streets": streets

            }
        }];

        var overlays = [{
                groupName: "Second Group",
                expanded: false,
                layers: {
                    "Option 1": geobov
                }
            }, {
                groupName: "Third Group",
                expanded: false,
                layers: {
                    //"Actividades humanas": WFSLayer,
                    "Bolivian Municipalities": local_municipios
                }
            }
        ]

        var options = {
            container_width: "300px",
            group_maxHeight: "80px",
            //container_maxHeight : "350px", 
            exclusive: false
        };

        var control = L.Control.styledLayerControl(baseMaps, overlays, options);
        lMap.addControl(control);


})
})(jQuery);


