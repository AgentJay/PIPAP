<?php

class wbquery_argument_text extends views_handler_argument {
  /**
   * The following functions express SQLisms in the base handler class. They
   * are all blanked out in overrides.
   */
  function default_summary($order, $by = NULL) { }
  function summary_query() { }
  function summary_name_field() { }
  function summary_basics($count_field = TRUE) { }
  function summary_sort($order, $by = NULL) { }

  function query() {
    if (isset($this->argument, $this->definition['wbapi']['filter_key'])) {
      $this->query->add_filter($this->table, $this->definition['wbapi']['filter_key'], $this->argument);
    }
  }

  function title() {
    switch ($this->field) {
      case 'indicator_id':
        if ($indicator = wbapi_indicators_load($this->argument)) {
          return check_plain($indicator->name);
        }
        break;
      case 'country_id':
        if (!in_array($this->argument, array('all', 'regions', 'incomes', 'countries')) && $country = wbapi_countries_load($this->argument)) {
          return check_plain($country->name);
        }
        break;
    }
    return check_plain($this->argument);
  }


  /**
   * Provide a list of default behaviors for this argument if the argument
   * is not present.
   *
   * Override this method to provide additional (or fewer) default behaviors.
   */
  function default_actions($which = NULL) {
    $defaults = array(
      'ignore' => array(
        'title' => t('Display all values'),
        'method' => 'default_ignore',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
      ),
      'not found' => array(
        'title' => t('Hide view / Page not found (404)'),
        'method' => 'default_not_found',
        'hard fail' => TRUE, // This is a hard fail condition
      ),
      'empty' => array(
        'title' => t('Display empty text'),
        'method' => 'default_empty',
        'breadcrumb' => TRUE, // generate a breadcrumb to here
      ),
      'default' => array(
        'title' => t('Provide default argument'),
        'method' => 'default_default',
        'form method' => 'default_argument_form',
        'has default argument' => TRUE,
        'default only' => TRUE, // this can only be used for missing argument, not validation failure
      ),
    );

    if ($which) {
      if (!empty($defaults[$which])) {
        return $defaults[$which];
      }
    }
    else {
      return $defaults;
    }
  }
}
