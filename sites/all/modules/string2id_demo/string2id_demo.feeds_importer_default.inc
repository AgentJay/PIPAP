<?php
/**
 * @file
 * string2id_demo.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function string2id_demo_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_expense_sheet';
  $feeds_importer->config = array(
    'name' => 'Import Expense Sheet',
    'description' => 'Imports a bank statement and categorizes expenses',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          0 => 'public',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => 0,
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'Title',
            'target' => 'title',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'Amount',
            'target' => 'field_amount',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Account',
            'target' => 'entityreference:field_account',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Type',
            'target' => 'field_type',
            'term_search' => '1',
            'autocreate' => 0,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'purchase',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_expense_sheet'] = $feeds_importer;

  return $export;
}
