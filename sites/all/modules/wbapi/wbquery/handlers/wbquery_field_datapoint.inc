<?php

/**
 * Flot datapoint handler for WB Query object. Requires the following keys to
 * be defined in hook_views_data():
 *
 *   series_field: The field to use as the "X" axis in a linear series.
 *   value_field: The field to use as the "Y" axis in a linear series.
 */

class wbquery_field_datapoint extends wbquery_field_numeric {
  function allow_advanced_render() {
    return FALSE;
  }

  /**
   * Return an array usable as a plot point by flot.
   */
  function flot_render($values) {
    $this->series_field = $this->aliases[$this->definition['series_field']];
    $this->value_field = $this->aliases[$this->definition['value_field']];
    $series = check_plain($values->{$this->series_field});
    $value = check_plain($values->{$this->value_field});

    // For our purposes, consider 0 to be a NULL value.
    if ($value == 0) {
      $value = NULL;
    }

    return array(
      'value' => array($series, $value),
      'label' => array($series, $value),
    );
  }

  /**
   * The default render function.
   */
  function render($values) {
    $this->series_field = $this->aliases[$this->definition['series_field']];
    $this->value_field = $this->aliases[$this->definition['value_field']];
    $series = check_plain($values->{$this->series_field});
    $value = check_plain($values->{$this->value_field});
    return "{$series}, {$value}";
  }
}
