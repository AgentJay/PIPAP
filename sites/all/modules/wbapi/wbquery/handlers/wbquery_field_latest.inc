<?php

/**
 * Latest value handler for WB Query object.
 * Requires the following keys to be defined in hook_views_data():
 *
 *   groupby: The field to use for collapsing multiple rows into a single row
 *     with expanded series fields. This field handler assumes the `date` field
 *     will be used as the expanded series field. Example: country_id will
 *     collapse rows by country, with each country row getting a new field for
 *     each distinct date returned.
 *
 *     Original result set:
 *     - country_id: us, date: 2008, value: 0
 *     - country_id: us, date: 2007, value: 1
 *     - country_id: us, date: 2006, value: 2
 *     - country_id: fr, date: 2008, value: 0
 *     - country_id: fr, date: 2007, value: 1
 *     - country_id: fr, date: 2006, value: 2
 *
 *     Processed result set:
 *     - country_id: us, latest: 0, date: 2008
 *     - country_id: fr, latest: 0, date: 2008
 *
 *   labelby: Used by parent class wbquery_field_numeric for formatting values.
 *
 *   CANNOT be used in conjunction with wbquery_field_series on the same view.
 */
class wbquery_field_latest extends wbquery_field_numeric {
  function construct() {
    parent::construct();
    $this->current_label = NULL;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['include_label'] = array('default' => FALSE);
    return $options;
  }

  function options_form(&$form, $form_state) {
    $form['include_label'] = array(
      '#title' => t('Include label'),
      '#description' => t('Render the label as part of the field value. Useful when using this field as a Views render token.'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['include_label'],
    );
    parent::options_form($form, $form_state);
  }

  function pre_render($values) {
    $this->view->result = $this->expand_fields($values);
  }

  function expand_fields($values) {
    $groupby = $this->aliases[$this->definition['groupby']];

    // First process the resultset to determine how many fields instances we
    // need to spawn.
    foreach ($values as $num => $row) {
      $id = $row->{$groupby};
      if (isset($row->{$this->aliases['date']})) {
        // Compress value rows.
        if (!isset($values[$id])) {
          $values[$id] = $row;
        }
        // If the current row has more recent data than the last, replace the old entry.
        elseif ($values[$id]->{$this->aliases['date']} < $row->{$this->aliases['date']}) {
          $values[$id] = $row;
        }
      }
      unset($values[$num]);
    }

    // Series sort.
    global $language;
    wbquery_setlocale($language->language);
    if (isset($this->orderby['field_alias']) && in_array($this->orderby['field_alias'], $this->expanded)) {
      uasort($values, array($this, 'uasort_' . strtolower($this->orderby['order'])));
    }
    else {
      $this->orderby['field_alias'] = $groupby;
      uasort($values, array($this, 'uasort_asc'));
    }
    wbquery_setlocale();
    return $values;
  }

  /**
   * Override default click sort handler. Series must do its sorting post
   * query & field expansion so setting an orderby on the query object
   * itself would be pointless.
   */
  function click_sort($order) { }

  function label() {
    return '';
  }

  function render($row) {
    $this->current_label = $row->{$this->aliases['date']};
    if ($this->options['include_label']) {
      return parent::render($row) . " <label>" . check_plain($this->current_label) . "</label>";
    }
    return parent::render($row);
  }
}
