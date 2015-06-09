<?php

class wbquery_relationship extends views_handler_relationship {
  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    $left_table = $this->table;
    $left_field = $this->field;

    $right_table = $this->definition['base'];
    // Figure out what base table this relationship brings to the party.
    $table_data = views_fetch_data($this->definition['base']);
    $right_field = empty($this->definition['base field']) ? $table_data['table']['base']['field'] : $this->definition['base field'];

    $this->query->add_relationship($left_table, $left_field, $right_table, $right_field);
  }
}
