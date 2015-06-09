<?php

class wbquery_filter_text extends views_handler_filter_equality {
  /**
   * Provide simple equality operator
   */
  function operator_options() {
    return array(
      '=' => t('Is equal to'),
    );
  }

  function query() {
    if (isset($this->value, $this->definition['wbapi']['filter_key'])) {
      $this->query->add_filter($this->table, $this->definition['wbapi']['filter_key'], $this->value);
    }
  }
}
