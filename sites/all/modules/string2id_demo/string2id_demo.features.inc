<?php
/**
 * @file
 * string2id_demo.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function string2id_demo_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "feeds_tamper" && $api == "feeds_tamper_default") {
    return array("version" => "2");
  }
}

/**
 * Implements hook_views_api().
 */
function string2id_demo_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function string2id_demo_node_info() {
  $items = array(
    'account' => array(
      'name' => t('Account'),
      'base' => 'node_content',
      'description' => t('Different payment methods, treated as a full page'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'purchase' => array(
      'name' => t('Purchase'),
      'base' => 'node_content',
      'description' => t('Each purchase made, imported from a CSV'),
      'has_title' => '1',
      'title_label' => t('Purchase Reference ID'),
      'help' => '',
    ),
  );
  return $items;
}
