<?php

/**
 * @file
 *
 * Defines the views query plugin that actually does most of the
 * heavy lifting for the field/argument handlers and plugins.
 * Replaces the default views query plugin we all know and love
 * that assembles MySQL query strings.
 *
 * Supports simple sorts, joins, and filters, but functionality is
 * limited to what wbapi and the World Bank API spec support and
 * to what has actually been implemented by handlers and plugins.
 */

class wbquery_views_plugin_query extends views_plugin_query {
  var $requests;
  var $aliases;
  var $joins;
  var $orderby;
  var $required_fields;

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  function init($base_table, $base_field) {
    module_load_include('inc', 'wbapi', 'wbapi.request');
    $this->requests = array();
    $this->aliases = array();
    $this->joins = array();
    $this->orderby = array();
    $this->ensure_table($base_table);

    // Required fields are fields that may not be empty in rows of the
    // resultset. Any rows with empty required fields are dropped *prior* to
    // paging.
    $this->required_fields = array();
  }

  function get_method($table) {
    return substr($table, 6);
  }

  function ensure_table($table) {
    // @TODO: **If** we ever need to support multiple instances of a request,
    // we need to change this to generate and use an alias.
    if (!isset($this->requests[$table])) {
      $this->requests[$table] = wbapiRequest::factory($this->get_method($table));
    }
  }

  function add_relationship($left_table, $left_field, $right_table, $right_field) {
    if (isset($this->requests[$left_table])) {
      $this->ensure_table($right_table);
      $this->add_field($left_table, $left_field);
      $this->joins[$left_table][$left_field] = array(
        'table' => $right_table,
        'field' => $right_field,
      );
    }
    return FALSE;
  }

  function add_field($table, $field, $required = FALSE) {
    $this->ensure_table($table);
    $alias = "{$table}_{$field}";
    $this->aliases[$table][$field] = $alias;

    if ($required) {
      $this->required_fields[$alias] = $alias;
    }
    return $alias;
  }

  function add_filter($table, $field, $value) {
    $this->ensure_table($table);
    $this->requests[$table]->setFilter($field, $value);
  }

  function add_orderby($table, $field, $order) {
    $alias = $this->add_field($table, $field);
    $this->orderby = array(
      'field_alias' => $alias,
      'order' => $order,
    );
  }

  function subrequest($table, $field, $arg, $base_row) {
    static $cache;
    $cache = !isset($cache) ? array() : $cache;

    if (isset($cache[$table][$field][$arg])) {
      $base_row = array_merge($base_row, $cache[$table][$field][$arg]);
    }
    // Only make the request if there are actually aliases to populate.
    elseif (!empty($this->aliases[$table])) {
      $cache[$table][$field][$arg] = array();

      // Set request filter.
      $request = clone $this->requests[$table];
      $request->setFilter($field, $arg);

      if ($result = $request->request()) {
        $row = array_shift($result);
        foreach ($this->aliases[$table] as $f => $alias) {
          // Populate cache and row values.
          $cache[$table][$field][$arg][$alias] =
          $base_row[$alias] = isset($row->{$f}) && !is_object($row->{$f}) ? $row->{$f} : NULL;

          // Execute sub queries.
          if (isset($this->joins[$table][$f])) {
            $sub_table = $this->joins[$table][$f]['table'];
            $sub_field = $this->joins[$table][$f]['field'];
            $sub_arg = $row->{$f};
            $base_row = $this->subrequest($sub_table, $sub_field, $sub_arg, $base_row);
          }
        }
      }

      // Death & destruction.
      unset($request);
    }
    return $base_row;
  }

  function request(&$view, $table, $request) {
    if (!empty($this->aliases[$table]) && $result = $request->request()) {
      foreach (array_values($result) as $num => $row) {
        // Flatten any nested stdClass->id & stdClass->value properties.
        foreach ($row as $i => $v) {
          if (is_object($v) && isset($v->id, $v->value)) {
            $row->{$i . '_id'} = $v->id;
            $row->{$i . '_value'} = $v->value;
          }
        }

        $view->result[$num] = new stdClass;
        foreach ($this->aliases[$table] as $field => $alias) {
          // Populate field values using aliases.
          $view->result[$num]->{$alias} = isset($row->{$field}) && !is_object($row->{$field}) ? $row->{$field} : NULL;

          // Execute sub queries.
          if (isset($this->joins[$table][$field])) {
            $sub_table = $this->joins[$table][$field]['table'];
            $sub_field = $this->joins[$table][$field]['field'];
            $sub_arg = $row->{$field};
            // Transition to arrays for subrequests for speed.
            // Transition back to object once we're done.
            $view->result[$num] = (object) $this->subrequest($sub_table, $sub_field, $sub_arg, (array) $view->result[$num]);
          }
        }
      }
    }
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->pager['current_page'].
   */
  function execute(&$view) {
    // Pager handling. This sets limit and offset values which are used to
    // truncate or slice result sets independently of the actual API request.
    // Views 3.x-alpha3 and prior.
    if (method_exists($this, 'init_pager')) {
      $this->init_pager($view);
    }
    // Views 3.x dev
    elseif (method_exists($view, 'init_pager')) {
      $view->init_pager();
    }

    if ($this->pager->use_pager()) {
      $this->pager->set_current_page($view->current_page);
    }
    $this->pager->query();

    // Make the actual request.
    $view->result = array();
    $queue = $this->requests;

    $request = reset($this->requests);
    $table = key($this->requests);
    $this->request($view, $table, $request);

    // Remove rows without required fields.
    if (!empty($this->required_fields)) {
      foreach ($this->required_fields as $alias) {
        foreach ($view->result as $num => $row) {
          if (empty($row->{$alias})) {
            unset($view->result[$num]);
          }
        }
      }
    }

    // Sort.
    if (!empty($this->orderby)) {
      global $language;
      wbquery_setlocale($language->language);
      uasort($view->result, array($this, 'uasort_' . strtolower($this->orderby['order'])));
      wbquery_setlocale();
    }

    // Slice the resultset.
    if (isset($this->offset, $this->limit)) {
      $end = $this->offset + $this->limit;
      $end = count($view->result) >= $end ? $end : count($view->result);
      $view->result = array_slice($view->result, $this->offset, $end);
    }
  }

  protected function uasort_asc($a, $b) {
    // Always move NULL values to the end.
    if (!isset($a->{$this->orderby['field_alias']})) {
      return TRUE;
    }
    if (!isset($b->{$this->orderby['field_alias']})) {
      return FALSE;
    }
    // Numeric comparison.
    if (is_numeric($a) && is_numeric($b)) {
      return $a->{$this->orderby['field_alias']} > $b->{$this->orderby['field_alias']};
    }
    // Locale-aware string comparison.
    else {
      return strcoll($a->{$this->orderby['field_alias']}, $b->{$this->orderby['field_alias']});
    }
  }

  protected function uasort_desc($a, $b) {
    // Always move NULL values to the end.
    if (!isset($a->{$this->orderby['field_alias']})) {
      return TRUE;
    }
    if (!isset($b->{$this->orderby['field_alias']})) {
      return FALSE;
    }
    // Numeric comparison.
    if (is_numeric($a) && is_numeric($b)) {
      return $a->{$this->orderby['field_alias']} < $b->{$this->orderby['field_alias']};
    }
    // Locale-aware string comparison.
    else {
      return !strcoll($a->{$this->orderby['field_alias']}, $b->{$this->orderby['field_alias']});
    }
  }
}
