(function($) {
	Drupal.OpenLayersSync = {};
	jQuery('.openlayers-map').each(function() {
		var map_id = $(this).attr('id');
	})
	var datas=[]
	var maps=[]

	Drupal.behaviors.openlayers_behavior_sync_map = 
	{
		attach: function(context, settings) 
		{		
			if ($(context).hasClass('openlayers-map'))
			{
				$this_id=$(context).attr('id');
				switch ($this_id){
					case 'openlayers-map':
						break;
					default:
						var data = $(context).data('openlayers');
						var map = data.openlayers;
						datas.push(data)
						maps.push(map)
				}
				var updatingMap1 = false;
				//var updatingMap2 = false;
				//var updatingMap3 = false;
				if ($this_id==='openlayers-map' && updatingMap1 === false)
				{
					var data = $(context).data('openlayers');
					var map = data.openlayers;
						map.events.register("moveend", map, function() 
						{
							updatingMap1 = true;
							var c1 = map.getCenter();
							var z1 = map.getZoom();
							var map_id = $(this).attr('id');
							$(maps).each(function ()
							{
								var map_id2 = $(this).attr('id');
								if(map_id2 != 'OpenLayers_Map_2')
								{
										
										this.panTo(c1);
										this.zoomTo(z1);
								}
							})
							
						});
					updatingMap1 = false;
				}
				/*if ($this_id==='openlayers-map--3' && updatingMap1 === false && updatingMap2 === false && updatingMap3 === false)
				{
					var data = $(context).data('openlayers');
					var map = data.openlayers;
						map.events.register("moveend", map, function() 
						{
							updatingMap2 = true;
							var c1 = map.getCenter();
							var z1 = map.getZoom();
							var map_id = $(this).attr('id');
							$(maps).each(function ()
							{
								var map_id2 = $(this).attr('id');
								if(map_id2 != 'OpenLayers_Map_2')
								{
										
										this.panTo(c1);
										this.zoomTo(z1);
								}
							})
							
						});
					updatingMap2 = false;
				}
				if ($this_id==='openlayers-map--4' && updatingMap1 === false && updatingMap2 === false && updatingMap3 === false)
				{
					var data = $(context).data('openlayers');
					var map = data.openlayers;
						map.events.register("moveend", map, function() 
						{
							updatingMap3 = true;
							var c1 = map.getCenter();
							var z1 = map.getZoom();
							var map_id = $(this).attr('id');
							$(maps).each(function ()
							{
								var map_id2 = $(this).attr('id');
								if(map_id2 != 'OpenLayers_Map_2')
								{
										
										this.panTo(c1);
										this.zoomTo(z1);
								}
							})
							
						});
					updatingMap3 = false;
				}*/
			}
		}
	};
})(jQuery);