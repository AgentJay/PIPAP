<?php
/**
 * @file
 * string2id_demo.features.uuid_node.inc
 */

/**
 * Implements hook_uuid_features_default_content().
 */
function string2id_demo_uuid_features_default_content() {
  $nodes = array();

  $nodes[] = array(
  'uid' => 1,
  'title' => 'Cheque',
  'log' => '',
  'status' => 1,
  'comment' => 2,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => 'f26ef0e7-1b72-2644-ed77-18a7c4192034',
  'type' => 'account',
  'language' => 'und',
  'created' => 1390979476,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '348bd8bc-8790-ab24-193e-1d166cff09a1',
  'revision_uid' => 1,
  'body' => array(),
  'field_account_synonyms' => array(
    'und' => array(
      0 => array(
        'value' => 'cheque',
        'format' => NULL,
        'safe_value' => 'cheque',
      ),
      1 => array(
        'value' => 'chq',
        'format' => NULL,
        'safe_value' => 'chq',
      ),
    ),
  ),
  'rdf_mapping' => array(
    'rdftype' => array(
      0 => 'sioc:Item',
      1 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'dc:title',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'foaf:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
  ),
  'name' => 'phpuser',
  'picture' => 0,
  'data' => 'b:0;',
  'date' => '2014-01-29 20:11:16 +1300',
);
  $nodes[] = array(
  'uid' => 1,
  'title' => 'Savings',
  'log' => '',
  'status' => 1,
  'comment' => 0,
  'promote' => 1,
  'sticky' => 0,
  'vuuid' => '4b742c17-83ef-af24-9df1-4d022c6c9538',
  'type' => 'account',
  'language' => 'und',
  'created' => 1390979611,
  'tnid' => 0,
  'translate' => 0,
  'uuid' => '9ea61619-5f35-add4-cd58-fcf5b3a468b7',
  'revision_uid' => 1,
  'body' => array(),
  'field_account_synonyms' => array(
    'und' => array(
      0 => array(
        'value' => 'savings',
        'format' => NULL,
        'safe_value' => 'savings',
      ),
      1 => array(
        'value' => 'ett',
        'format' => NULL,
        'safe_value' => 'ett',
      ),
      2 => array(
        'value' => 'eft-pos',
        'format' => NULL,
        'safe_value' => 'eft-pos',
      ),
      3 => array(
        'value' => 'transfer',
        'format' => NULL,
        'safe_value' => 'transfer',
      ),
      4 => array(
        'value' => 'cash',
        'format' => NULL,
        'safe_value' => 'cash',
      ),
    ),
  ),
  'rdf_mapping' => array(
    'rdftype' => array(
      0 => 'sioc:Item',
      1 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'dc:title',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'foaf:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
  ),
  'name' => 'phpuser',
  'picture' => 0,
  'data' => 'b:0;',
  'date' => '2014-01-29 20:13:31 +1300',
);
  return $nodes;
}
