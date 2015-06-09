<?php
/**
 * @file
 * string2id_demo.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function string2id_demo_taxonomy_default_vocabularies() {
  return array(
    'expense_type' => array(
      'name' => 'Expense type',
      'machine_name' => 'expense_type',
      'description' => 'Type of Expense',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
