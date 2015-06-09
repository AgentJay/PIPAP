<?php
/**
 * @file
 * string2id_demo.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function string2id_demo_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'import_expense_sheet-account-convert_string_into_entity_id';
  $feeds_tamper->importer = 'import_expense_sheet';
  $feeds_tamper->source = 'Account';
  $feeds_tamper->plugin_id = 'string2id';
  $feeds_tamper->settings = array(
    'method' => 'views',
    'autocomplete' => array(
      'entity_type' => 'node',
      'field_name' => 'field_account',
      'bundle_name' => NULL,
    ),
    'views' => array(
      'view' => 'fetch_account_id_by_synonym:default',
    ),
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Convert string into entity ID';
  $export['import_expense_sheet-account-convert_string_into_entity_id'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'import_expense_sheet-amount-trim';
  $feeds_tamper->importer = 'import_expense_sheet';
  $feeds_tamper->source = 'Amount';
  $feeds_tamper->plugin_id = 'trim';
  $feeds_tamper->settings = array(
    'mask' => '$',
    'side' => 'ltrim',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Trim';
  $export['import_expense_sheet-amount-trim'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'import_expense_sheet-type-convert_string_into_entity_id';
  $feeds_tamper->importer = 'import_expense_sheet';
  $feeds_tamper->source = 'Type';
  $feeds_tamper->plugin_id = 'string2id';
  $feeds_tamper->settings = array(
    'method' => 'views',
    'autocomplete' => array(
      'entity_type' => 'node',
      'field_name' => 'field_account',
      'bundle_name' => NULL,
    ),
    'views' => array(
      'view' => 'fetch_expense_type_by_synonym:default',
      'col_id' => '0',
    ),
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Convert string into entity ID';
  $export['import_expense_sheet-type-convert_string_into_entity_id'] = $feeds_tamper;

  return $export;
}
