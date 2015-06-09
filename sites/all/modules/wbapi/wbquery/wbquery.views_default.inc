<?php
/**
 * @file
 * wbquery.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function wbquery_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'wbapi_countries';
  $view->description = 'List of countries';
  $view->tag = '';
  $view->base_table = 'wbapi_countries';
  $view->human_name = 'WBAPI countries';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'iso2Code' => 'iso2Code',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'align' => '',
      'separator' => '',
    ),
    'iso2Code' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: World Bank API: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'wbapi_countries';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Country';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  /* Field: World Bank API: iso2 code */
  $handler->display->display_options['fields']['iso2Code']['id'] = 'iso2Code';
  $handler->display->display_options['fields']['iso2Code']['table'] = 'wbapi_countries';
  $handler->display->display_options['fields']['iso2Code']['field'] = 'iso2Code';
  $handler->display->display_options['fields']['iso2Code']['label'] = 'ISO2 Code';
  $handler->display->display_options['fields']['iso2Code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['iso2Code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['iso2Code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['iso2Code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['iso2Code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['iso2Code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['iso2Code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['iso2Code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['iso2Code']['empty_zero'] = 0;
  /* Sort criterion: World Bank API: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'wbapi_countries';
  $handler->display->display_options['sorts']['name']['field'] = 'name';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'wbapi/countries';
  $export['wbapi_countries'] = $view;

  $view = new view;
  $view->name = 'wbapi_income_levels';
  $view->description = 'A list of income levels';
  $view->tag = '';
  $view->base_table = 'wbapi_incomeLevels';
  $view->human_name = 'WBAPI income levels';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Income Levels';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: World Bank API: Income Level */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'wbapi_incomeLevels';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['label'] = '';
  $handler->display->display_options['fields']['value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['value']['empty_zero'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['wbapi_income_levels'] = $view;

  $view = new view;
  $view->name = 'wbapi_indicator_data';
  $view->description = 'Provide this view with an indicator and coutry code argument, like /wbapi/indicator/NY.ADJ.SVNX.CD/BO';
  $view->tag = '';
  $view->base_table = 'wbapi_data';
  $view->human_name = 'WBAPI indicator data';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'wbquery_pager_year';
  $handler->display->display_options['pager']['options']['years_per_page'] = '5';
  $handler->display->display_options['pager']['options']['first_year'] = '1980';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'country_value' => 'country_value',
    'country_id' => 'country_id',
    'value' => 'value',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'country_value' => array(
      'align' => '',
      'separator' => '',
    ),
    'country_id' => array(
      'align' => '',
      'separator' => '',
    ),
    'value' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: World Bank API: Country name */
  $handler->display->display_options['fields']['country_value']['id'] = 'country_value';
  $handler->display->display_options['fields']['country_value']['table'] = 'wbapi_data';
  $handler->display->display_options['fields']['country_value']['field'] = 'country_value';
  $handler->display->display_options['fields']['country_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['country_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['country_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['country_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['country_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['country_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['country_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['country_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['country_value']['empty_zero'] = 0;
  /* Field: World Bank API: Country code */
  $handler->display->display_options['fields']['country_id']['id'] = 'country_id';
  $handler->display->display_options['fields']['country_id']['table'] = 'wbapi_data';
  $handler->display->display_options['fields']['country_id']['field'] = 'country_id';
  $handler->display->display_options['fields']['country_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['country_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['country_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['country_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['country_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['country_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['country_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['country_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['country_id']['empty_zero'] = 0;
  /* Field: World Bank API: Value */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'wbapi_data';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['value']['set_precision'] = 0;
  $handler->display->display_options['fields']['value']['precision'] = '0';
  $handler->display->display_options['fields']['value']['drop_empty'] = 0;
  /* Contextual filter: World Bank API: Indicator id */
  $handler->display->display_options['arguments']['indicator_id']['id'] = 'indicator_id';
  $handler->display->display_options['arguments']['indicator_id']['table'] = 'wbapi_data';
  $handler->display->display_options['arguments']['indicator_id']['field'] = 'indicator_id';
  $handler->display->display_options['arguments']['indicator_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['indicator_id']['title_enable'] = 1;
  $handler->display->display_options['arguments']['indicator_id']['title'] = '%1';
  $handler->display->display_options['arguments']['indicator_id']['default_argument_type'] = 'wbquery_indicator';
  $handler->display->display_options['arguments']['indicator_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['indicator_id']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['indicator_id']['validate']['type'] = 'wbquery_indicator';
  /* Contextual filter: World Bank API: Country code */
  $handler->display->display_options['arguments']['country_id']['id'] = 'country_id';
  $handler->display->display_options['arguments']['country_id']['table'] = 'wbapi_data';
  $handler->display->display_options['arguments']['country_id']['field'] = 'country_id';
  $handler->display->display_options['arguments']['country_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['country_id']['exception']['value'] = 'null';
  $handler->display->display_options['arguments']['country_id']['exception']['title_enable'] = 1;
  $handler->display->display_options['arguments']['country_id']['exception']['title'] = 'NULL';
  $handler->display->display_options['arguments']['country_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['country_id']['default_argument_options']['argument'] = 'countries';
  $handler->display->display_options['arguments']['country_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['country_id']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['country_id']['validate']['type'] = 'wbquery_country';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'wbapi/indicator';
  $export['wbapi_indicator_data'] = $view;

  $view = new view;
  $view->name = 'wbapi_indicators';
  $view->description = 'List of World Bank indicators';
  $view->tag = '';
  $view->base_table = 'wbapi_indicators';
  $view->human_name = 'WBAPI indicators';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'source_value' => 'source_value',
    'sourceNote' => 'sourceNote',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'align' => '',
      'separator' => '',
    ),
    'source_value' => array(
      'align' => '',
      'separator' => '',
    ),
    'sourceNote' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: World Bank API: Indicator name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'wbapi_indicators';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'Indicator';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  /* Field: World Bank API: Source */
  $handler->display->display_options['fields']['source_value']['id'] = 'source_value';
  $handler->display->display_options['fields']['source_value']['table'] = 'wbapi_indicators';
  $handler->display->display_options['fields']['source_value']['field'] = 'source_value';
  $handler->display->display_options['fields']['source_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['source_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['source_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['source_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['source_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['source_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['source_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['source_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['source_value']['empty_zero'] = 0;
  /* Field: World Bank API: Source note */
  $handler->display->display_options['fields']['sourceNote']['id'] = 'sourceNote';
  $handler->display->display_options['fields']['sourceNote']['table'] = 'wbapi_indicators';
  $handler->display->display_options['fields']['sourceNote']['field'] = 'sourceNote';
  $handler->display->display_options['fields']['sourceNote']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['sourceNote']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['sourceNote']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['sourceNote']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['sourceNote']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['sourceNote']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['sourceNote']['alter']['html'] = 0;
  $handler->display->display_options['fields']['sourceNote']['hide_empty'] = 0;
  $handler->display->display_options['fields']['sourceNote']['empty_zero'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'wbapi/indicators';
  $export['wbapi_indicators'] = $view;

  $view = new view;
  $view->name = 'wbapi_regions';
  $view->description = 'World Bank regions';
  $view->tag = '';
  $view->base_table = 'wbapi_regions';
  $view->human_name = 'WBAPI regions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: World Bank API: Region name */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'wbapi_regions';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['label'] = '';
  $handler->display->display_options['fields']['value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['value']['empty_zero'] = 0;
  /* Sort criterion: World Bank API: Region name */
  $handler->display->display_options['sorts']['value']['id'] = 'value';
  $handler->display->display_options['sorts']['value']['table'] = 'wbapi_regions';
  $handler->display->display_options['sorts']['value']['field'] = 'value';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Regions';
  $export['wbapi_regions'] = $view;

  $view = new view;
  $view->name = 'wbapi_topics';
  $view->description = 'List of World Bank topics and descriptions';
  $view->tag = '';
  $view->base_table = 'wbapi_topics';
  $view->human_name = 'WBAPI topics';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Topics';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'value' => 'value',
    'sourceNote' => 'sourceNote',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'value' => array(
      'align' => '',
      'separator' => '',
    ),
    'sourceNote' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  /* Field: World Bank API: Topic */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'wbapi_topics';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['value']['empty_zero'] = 0;
  /* Field: World Bank API: Description */
  $handler->display->display_options['fields']['sourceNote']['id'] = 'sourceNote';
  $handler->display->display_options['fields']['sourceNote']['table'] = 'wbapi_topics';
  $handler->display->display_options['fields']['sourceNote']['field'] = 'sourceNote';
  $handler->display->display_options['fields']['sourceNote']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['sourceNote']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['sourceNote']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['sourceNote']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['sourceNote']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['sourceNote']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['sourceNote']['alter']['html'] = 0;
  $handler->display->display_options['fields']['sourceNote']['hide_empty'] = 0;
  $handler->display->display_options['fields']['sourceNote']['empty_zero'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'wbapi/topics';
  $export['wbapi_topics'] = $view;

  return $export;
}
