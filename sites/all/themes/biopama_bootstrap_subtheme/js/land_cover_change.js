
(function ($) {

$( document ).ready(function() {
	var RGBval = "3,2,1";
	lccfunct(RGBval);
});

Drupal.behaviors.lcc_color_bands = {
	attach: function(context, settings) {
		$( "button.lcc-color-bands" ).mouseup(function() {
			$( "div.lccval-legend" ).addClass( "lcc-hide" );
			$( "div.lccunval-legend" ).addClass( "lcc-hide" );
			var myRadio = $('input[name=group1]');
			var selected = myRadio.filter(':checked').val();
			if(selected == "natural_color"){
				var RGBval = "3,2,1";
				lccfunct(RGBval);
			}
			else if(selected == "false_color"){
				var RGBval = "6,4,3";
				lccfunct(RGBval);
			}
			else if(selected == "other_color"){
				var red = $("#selectred").find('option:selected').val();
				red += '';
				var green = $("#selectgreen").find('option:selected').val();
				green += '';
				var blue = $("#selectblue").find('option:selected').val();
				blue += '';
				var RGBval = red+","+green+","+blue;
				lccfunct(RGBval);
			}
		});
	}
}

Drupal.behaviors.lcc_validated = {
	attach: function(context, settings) {
		$( "button.lcc-validated" ).mouseup(function() {
			$( "div.lccval-legend" ).removeClass( "lcc-hide" );
			lccvalidatedfunct();
		});
	}
}

Drupal.behaviors.lcc_other = {
	attach: function(context, settings) {
		$( "input.lcc-natural" ).mouseup(function() {
			$( "div.lcc-handle" ).addClass( "lcc-hide" );
			//alert("yes");
		});
		$( "input.lcc-false" ).mouseup(function() {
			$( "div.lcc-handle" ).addClass( "lcc-hide" );
			//alert("yes");
		});
		$( "input.lcc-other" ).mouseup(function() {
			$( "div.lcc-handle" ).removeClass( "lcc-hide" );
			//alert("yes");
		});
	}
}

Drupal.behaviors.lcc_unvalidated = {
	attach: function(context, settings) {
		$( "button.lcc-unvalidated" ).mouseup(function() {
			$( "div.lccunval-legend" ).removeClass( "lcc-hide" );
			lccunvalidatedfunct();
		});
	}
}

	
function lccfunct(RGBval) {
		var $paname2 =  $('#pa-name').text();
		var $paname = $paname2.trim();
		var $mapid2 =  $('#wdpaid').text();
		var $mapid = $mapid2.trim();
		var $paborder2 =  $('.field-name-field-pa-boundary').text();
		var $paborder1 = $paborder2.trim();
		
		var wkt = new OpenLayers.Format.WKT();
		var polygonFeature = wkt.read($paborder1);
		var paborder = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder.addFeatures(polygonFeature);
		
		var polygonFeature2 = wkt.read($paborder1);
		var paborder2 = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder2.addFeatures(polygonFeature2);
		
		var polygonFeature3 = wkt.read($paborder1);
		var paborder3 = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder3.addFeatures(polygonFeature3);
		
		
		/*
		var red = $("#selectred").find('option:selected').text();
		red += '';
		var green = $("#selectgreen").find('option:selected').text();
		green += '';
		var blue = $("#selectblue").find('option:selected').text();
		blue += '';
		var RGBval = red+","+green+","+blue;
		*/
		var $year = "1990";
		var $mapname = $paname+" "+$year;
		var $maplink = "http://lrm-maps.jrc.ec.europa.eu/mapserver_utils/raster_WMS.php?"
		+"data="+$mapid+"_"+$year+".tif"+"&epsg=4326&autoscale=YES&SRS=EPSG:4326"; 
		
		var layer = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "rasterLayer", 
						reproject: true,
						displayprojection: 'EPSG:4326', 
						RGB: RGBval, 
						mergable: true,
						TRANSPARENT: true
						//rendererOptions: { zIndexing: true }
					}
				);
		var ol = $('.openlayers-map-lcc-1990').data('openlayers');        
		//console.log(ol);

		ol.openlayers.addLayer(layer);
		ol.openlayers.addLayer(paborder);
		
		//ol.openlayers.layer.setZIndex( 1 );

		$year = "2000";
		var $mapname = $paname+" "+$year;
		$maplink = "http://lrm-maps.jrc.ec.europa.eu/mapserver_utils/raster_WMS.php?"
		+"data="+$mapid+"_"+$year+".tif"+"&epsg=4326&autoscale=YES&SRS=EPSG:4326"; 
		var layer2 = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "rasterLayer", 
						reproject: true,
						displayprojection: 'EPSG:4326', 
						RGB: RGBval, 
						mergable: true,
						TRANSPARENT: true,
						//rendererOptions: { zIndexing: true }
					}
				);
		var ol2 = $('.openlayers-map-lcc-2000').data('openlayers');
		ol2.openlayers.addLayer(layer2);
		ol2.openlayers.addLayer(paborder2);
		//layer2.setZIndex( 745 );
		//ol2.setLayerIndex(layer2, 0);
						
		$year = "2010";
		var $mapname = $paname+" "+$year;
		$maplink = "http://lrm-maps.jrc.ec.europa.eu/mapserver_utils/raster_WMS.php?"
		+"data="+$mapid+"_"+$year+".tif"+"&epsg=4326&autoscale=YES&SRS=EPSG:4326"; 
		var layer3 = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "rasterLayer", 
						reproject: true,
						displayprojection: 'EPSG:4326', 
						RGB: RGBval, 
						mergable: true,
						TRANSPARENT: true
					}
				);
		var ol3 = $('.openlayers-map-lcc-2010').data('openlayers');
		ol3.openlayers.addLayer(layer3);
		ol3.openlayers.addLayer(paborder3);
}

function lccvalidatedfunct() {

		var $paborder2 =  $('.field-name-field-pa-boundary').text();
		var $paborder1 = $paborder2.trim();
		
		var wkt = new OpenLayers.Format.WKT();
		var polygonFeature = wkt.read($paborder1);
		
		var paborder = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder.addFeatures(polygonFeature);
		
		var polygonFeature2 = wkt.read($paborder1);
		var paborder2 = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder2.addFeatures(polygonFeature2);
		
		var polygonFeature3 = wkt.read($paborder1);
		var paborder3 = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder3.addFeatures(polygonFeature3);

		var $mapname = "PAIS 1990";
		var $maplink = "http://lrm-maps.jrc.ec.europa.eu:8080/geoserver/wms?"; 
		
		var layer = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "pais:segments1990", 
						TRANSPARENT: true
					}
				);
		var ol = $('.openlayers-map-lcc-1990').data('openlayers');
		ol.openlayers.addLayer(layer);
		ol.openlayers.addLayer(paborder);
		
		var $mapname = "PAIS 2000";
		var layer2 = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "pais:segments2000", 
						TRANSPARENT: true
					}
				);
		var ol2 = $('.openlayers-map-lcc-2000').data('openlayers');
		ol2.openlayers.addLayer(layer2);
		ol2.openlayers.addLayer(paborder2);
		
		var $mapname = "PAIS 2010";
		var layer3 = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "pais:segments2010", 
						TRANSPARENT: true
					}
				);
		var ol3 = $('.openlayers-map-lcc-2010').data('openlayers');
		ol3.openlayers.addLayer(layer3);
		ol3.openlayers.addLayer(paborder3);
}

function lccunvalidatedfunct() {
		
		var $paborder2 =  $('.field-name-field-pa-boundary').text();
		var $paborder1 = $paborder2.trim();
		
		var wkt = new OpenLayers.Format.WKT();
		var polygonFeature = wkt.read($paborder1);
		
		var paborder = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder.addFeatures(polygonFeature);
		
		var polygonFeature2 = wkt.read($paborder1);
		var paborder2 = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder2.addFeatures(polygonFeature2);
		
		var polygonFeature3 = wkt.read($paborder1);
		var paborder3 = new OpenLayers.Layer.Vector("PA Border", {
			styleMap: new OpenLayers.StyleMap({
				"default": new OpenLayers.Style({
					fillColor: "#fff",
					fillOpacity: "0",
					strokeColor: "#000000",
					strokeWidth: 1
				})
			})
		});
		paborder3.addFeatures(polygonFeature3);

		var $mapname = "PAIS 1990";
		var $maplink = "http://lrm-maps.jrc.ec.europa.eu:8080/geoserver/wms?"; 
		
		var layer = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "pais:unvalidated_1990", 
						TRANSPARENT: true
					}
				);
		var ol = $('.openlayers-map-lcc-1990').data('openlayers');
		ol.openlayers.addLayer(layer);
		ol.openlayers.addLayer(paborder);
		
		var $mapname = "PAIS 2000";
		var layer2 = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "pais:unvalidated_2000", 
						TRANSPARENT: true
					}
				);
		var ol2 = $('.openlayers-map-lcc-2000').data('openlayers');
		ol2.openlayers.addLayer(layer2);
		ol2.openlayers.addLayer(paborder2);
		
		var $mapname = "PAIS 2010";
		var layer3 = new OpenLayers.Layer.WMS
				(
					$mapname,
					$maplink,
					{
						isBaseLayer: false, 
						layers: "pais:unvalidated_2010", 
						TRANSPARENT: true
					}
				);
		var ol3 = $('.openlayers-map-lcc-2010').data('openlayers');
		ol3.openlayers.addLayer(layer3);
		ol3.openlayers.addLayer(paborder3);
}
	
	
})(jQuery);

