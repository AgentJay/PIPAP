<?php
/**
 * @file
 * For Syncing maps
 *
 */

class openlayers_behavior_sync_map extends openlayers_behavior {
  
  public function options_init() {
    $options = array();
    return $options;
  }

  public function options_form($defaults = array()) {
    return array(
      'MapSync1' => array(
        '#type' => 'textfield',
        '#title' => t('First map to be synced'),
        '#description' => t('To syncronize the map, pass the CSS CLASS attribute of the HTML div element that contains the map. eg. a map titled OSM might would likely have the CSS CLASS openlayers-maps-osm'),
        '#default_value' => isset($defaults['MapSync1']) ? $defaults['MapSync1'] : 'openlayers-maps',
      ),
      'MapSync2' => array(
        '#type' => 'textfield',
        '#title' => t('Second map to be synced'),
        '#description' => t('To syncronize the map, pass the CSS CLASS attribute of the HTML div element that contains the map. eg. a map titled OSM might would likely have the CSS CLASS openlayers-maps-osm'),
        '#default_value' => isset($defaults['MapSync2']) ? $defaults['MapSync2'] : FALSE,
      ),
    );
  }

  public function render(&$map) {
	//drupal_add_js(array('openlayers_sync' => $options), 'setting');
	//drupal_add_js(array('openlayers_sync' => array ('mapsync' => $options),),'setting');
    drupal_add_js(drupal_get_path('module', 'openlayers_sync') . '/includes/js/openlayers_behavior_sync_map.js');
	$options = $this->options;
    return $options;
  }
}