<?php
/**
 * @file
 * string2id_demo.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function string2id_demo_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Food',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '13c0a0ba-27e9-b834-a16a-bf6901935837',
    'vocabulary_machine_name' => 'expense_type',
    'field_expense_synonym' => array(
      'und' => array(
        0 => array(
          'value' => 'coffee',
          'format' => NULL,
          'safe_value' => 'coffee',
        ),
        1 => array(
          'value' => 'lunch',
          'format' => NULL,
          'safe_value' => 'lunch',
        ),
        2 => array(
          'value' => 'supermarket',
          'format' => NULL,
          'safe_value' => 'supermarket',
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'misc',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '7037f248-5536-dc14-0111-cfc5b1df8695',
    'vocabulary_machine_name' => 'expense_type',
    'field_expense_synonym' => array(
      'und' => array(
        0 => array(
          'value' => 'gifts',
          'format' => NULL,
          'safe_value' => 'gifts',
        ),
        1 => array(
          'value' => 'drinks',
          'format' => NULL,
          'safe_value' => 'drinks',
        ),
        2 => array(
          'value' => 'magazines',
          'format' => NULL,
          'safe_value' => 'magazines',
        ),
      ),
    ),
  );
  $terms[] = array(
    'name' => 'travel',
    'description' => '',
    'format' => 'filtered_html',
    'weight' => 0,
    'uuid' => '8912a9bc-53df-0ba4-350c-73817ac5a71a',
    'vocabulary_machine_name' => 'expense_type',
    'field_expense_synonym' => array(
      'und' => array(
        0 => array(
          'value' => 'bus',
          'format' => NULL,
          'safe_value' => 'bus',
        ),
        1 => array(
          'value' => 'taxi',
          'format' => NULL,
          'safe_value' => 'taxi',
        ),
      ),
    ),
  );
  return $terms;
}
