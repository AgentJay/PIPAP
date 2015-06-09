/*(function ($) {
	Drupal.behaviors.addlayertest = {
		attach: function (context, settings) {
			$('.addlayertest', context).click(function () {
			alert("Hello");
				var $maplayer = $('div.map-layer-map-name').text(); 
				var $maplink = $('div.map-layer-map-link').text(); 
				var n=$maplink.indexOf("?");
				if (n == -1) {
				   $maplink = $maplink+'?';
				}
				var layer = new OpenLayers.Layer.WMS
                (
                    $maplayer,
                    $maplink,
                    {
                        layers: $maplayer,
                        format: "image/png",
                        exceptions: "application/vnd.ogc.se_inimage",
                        transparent: "true"
                    },
                    {
                        isBaseLayer: false,
                        visibility: true
                    }
                );
                var ol = $('#openlayers-map').data('openlayers'); //The problem was to get the real Openlayers map object-use jQuery
                ol.openlayers.addLayer( layer );
			});
		}
	};
})(jQuery);*/

(function ($) {
	Drupal.behaviors.addgeonetworklayer = {
		attach: function (context, settings) {
			var $maplayer = $('div.field-name-field-geontwrk-map-name').text(); 
			var $maplinktemp = $('div.field-name-field-geontwrk-uri-wms-url').text();
			var $maplink = $maplinktemp.split("?");
			//alert($maplink[0]);
			if ($maplink[0].indexOf(".") >= 0) { 
				$( "div#map" ).removeClass( "geonode-hide" );
				$( "div#map" ).addClass( "height-fix" );
				var $bbox_top = $('div.field-name-field-geontwrk-bbox-top').text(); 
				var $bbox_bottom = $('div.field-name-field-geontwrk-bbox-bottom').text(); 
				var $bbox_left = $('div.field-name-field-geontwrk-bbox-left').text(); 
				var $bbox_right = $('div.field-name-field-geontwrk-bbox-right').text(); 
				var $maplink2 = $maplink[0]+"?";
				//alert("Maplink="+$maplink2+" maplayer="+$maplayer+" bboxtop="+$bbox_top);

				var southWest = L.latLng($bbox_bottom, $bbox_left),
				northEast = L.latLng($bbox_top, $bbox_right),
				bounds = L.latLngBounds(southWest, northEast);
				

				var mbAttr = 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, ' +
					'<a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
					'Imagery © <a href="http://mapbox.com">Mapbox</a>',
				mbUrl = 'https://{s}.tiles.mapbox.com/v3/{id}/{z}/{x}/{y}.png';

				var grayscale   = L.tileLayer(mbUrl, {id: 'examples.map-20v6611k', attribution: mbAttr}),
				streets  = L.tileLayer(mbUrl, {id: 'examples.map-i875mjb7',   attribution: mbAttr});
				
				var map = L.map('map', {
					layers: [streets]
				});
				map.fitBounds(bounds);

				var geonode_layer = L.tileLayer.wms($maplink2, {
					layers: $maplayer,
					format: 'image/png',
					transparent: true,
					attribution: "BIOPAMA Geonode"
				}).addTo(map);

				var baseLayers = {
					"Grayscale": grayscale,
					"Streets": streets
				};

				var overlays = {
					"Geonode Layer": geonode_layer
				};
				L.control.layers(baseLayers, overlays).addTo(map);
			}
		}
	};
})(jQuery);