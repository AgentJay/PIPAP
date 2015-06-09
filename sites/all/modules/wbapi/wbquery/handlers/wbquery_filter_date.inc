<?php

class wbquery_filter_date extends wbquery_filter_text {
  function query() {
    if (isset($this->value, $this->definition['wbapi']['filter_key'])) {
      $current = variable_get('wbapi_current_year', '2008');
      $arg = strtr($this->value, array(
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
