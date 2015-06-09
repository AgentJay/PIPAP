<?php

class wbquery_filter_boolean extends views_handler_filter_boolean_operator {
  function query() {
    if (empty($this->value)) {
      $this->query->add_filter($this->table, $this->definition['wbapi']['filter_key'], '0');
    }
    else {
      $this->query->add_filter($this->table, $this->definition['wbapi']['filter_key'], '1');
    }
  }
}
