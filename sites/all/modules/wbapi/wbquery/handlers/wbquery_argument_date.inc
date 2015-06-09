<?php

class wbquery_argument_date extends wbquery_argument_text {
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
      $current = variable_get('wbapi_current_year', '2008');
      $arg = strtr($this->argument, array(
        'now' => date('Y'),
        'year' => $current,
        'latest' => ($current - 4) . ':' . $current, // This means last 5 years.
      ));
      if (strpos($arg, ':')) {
        $this->query->add_filter($this->table, 'date', $arg);
      }
      else {
        $this->query->add_filter($this->table, $this->definition['wbapi']['filter_key'], $arg);
      }
    }
  }
}
