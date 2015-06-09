<?php
/**
 * @file
 * string2id_demo.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function string2id_demo_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'fetch_account_id_by_synonym';
  $view->description = 'Used by Feeds entity2id. Given a string describing the account, return the entity ID';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Fetch account id by synonym';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fetch account id by synonym';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Account synonyms (field_account_synonyms) */
  $handler->display->display_options['arguments']['field_account_synonyms_value']['id'] = 'field_account_synonyms_value';
  $handler->display->display_options['arguments']['field_account_synonyms_value']['table'] = 'field_data_field_account_synonyms';
  $handler->display->display_options['arguments']['field_account_synonyms_value']['field'] = 'field_account_synonyms_value';
  $handler->display->display_options['arguments']['field_account_synonyms_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_account_synonyms_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_account_synonyms_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_account_synonyms_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_account_synonyms_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_account_synonyms_value']['limit'] = '0';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'account' => 'account',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'fetch-account-id-by-synonym';
  $export['fetch_account_id_by_synonym'] = $view;

  $view = new view();
  $view->name = 'fetch_expense_type_by_synonym';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Fetch expense type by synonym';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Fetch expense type by synonym';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Contextual filter: Taxonomy term: expense synonym (field_expense_synonym) */
  $handler->display->display_options['arguments']['field_expense_synonym_value']['id'] = 'field_expense_synonym_value';
  $handler->display->display_options['arguments']['field_expense_synonym_value']['table'] = 'field_data_field_expense_synonym';
  $handler->display->display_options['arguments']['field_expense_synonym_value']['field'] = 'field_expense_synonym_value';
  $handler->display->display_options['arguments']['field_expense_synonym_value']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_expense_synonym_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_expense_synonym_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_expense_synonym_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_expense_synonym_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_expense_synonym_value']['limit'] = '0';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'expense_type' => 'expense_type',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'fetch-expense-type-by-synonym';
  $export['fetch_expense_type_by_synonym'] = $view;

  return $export;
}
