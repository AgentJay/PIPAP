<?php

class wbquery_field_numeric extends views_handler_field_numeric {
  // Store all values for later access from other handlers.
  public $all_values;
  public $all_values_rendered;

  function option_definition() {
    $options = parent::option_definition();
    $options['drop_empty'] = array('default' => FALSE);
    $options['format_units'] = array('default' => TRUE);
    $options['wb_precision'] = array('default' => TRUE);
    return $options;
  }

  function options_form(&$form, $form_state) {
    $form['drop_empty'] = array(
      '#title' => t('Drop empty rows'),
      '#description' => t('Drop rows from the result set where this field is empty.'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['drop_empty'],
    );
    $form['format_units'] = array(
      '#title' => t('Formatting: add units'),
      '#description' => t('Add units (e.g. $, %) where appropriate.'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['format_units'],
    );
    $set_precision = $form['set_precision'];
    $precision = $form['precision'];
    unset($form['set_precision'], $form['precision']);
    $form['set_precision'] = $set_precision;
    $form['wb_precision'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use World Bank\'s rounding rules (recommended)'),
      '#description' => t('If checked, any other rounding rules will be ignored.'),
      '#default_value' => $this->options['wb_precision'],
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('edit-options-set-precision' => array(TRUE)),
      '#size' => 2,
    );
    $form['precision'] = $precision;
    parent::options_form($form, $form_state);
  }

  function add_additional_fields($fields = NULL) {
    foreach ($fields as $field) {
      $this->aliases[$field] = $this->query->add_field($this->table, $field);
    }
  }

  function click_sort($order) {
    $this->query->add_orderby($this->table, $this->real_field, $order);
  }

  function query() {
    $this->field_alias = $this->query->add_field($this->table, $this->real_field, $this->options['drop_empty']);

    // Add in additional fields.
    if (!empty($this->additional_fields)) {
      $this->add_additional_fields($this->additional_fields);
    }
  }

  function render($row) {
    // If nothing is set, just return an empty string.
    if (!isset($row->{$this->field_alias})) {
      return '';
    }

    $original_options = $this->options;

    // Implement empty value hiding correctly. See views_handler_field_numeric
    // for how this is implemented after precision/number formatting and thus
    // fails in the parent class.
    if ($this->options['hide_empty'] && empty($row->{$this->field_alias}) && ($row->{$this->field_alias} !== 0 || $this->options['empty_zero'])) {
      return '';
    }

    // Unit formatting if enabled.
    if (isset($this->definition['labelby'], $this->aliases[$this->definition['labelby']], $row->{$this->aliases[$this->definition['labelby']]})) {
      $labelby = $row->{$this->aliases[$this->definition['labelby']]};
      // Percent
      if (strpos($labelby, '%') !== FALSE) {
        $is_percent = TRUE;
        $this->options['suffix'] = $this->options['format_units'] ? '%' : $this->options['suffix'];
        $this->options['precision'] = 1;
      }
      // USD
      elseif (strpos($labelby, '$') !== FALSE) {
        $is_currency = TRUE;
        $this->options['prefix'] = $this->options['format_units'] ? '$' : $this->options['prefix'];
      }
    }

    global $language;
    switch ($language->language) {
      case 'en':
      case 'ar':
        $this->options['decimal'] = '.';
        $this->options['separator'] = ',';
        break;
      case 'es':
        $this->options['decimal'] = ',';
        $this->options['separator'] = '.';
        $this->options['prefix'] = '';
        $this->options['suffix'] = !empty($is_currency) ? '$' : $this->options['suffix'];
        break;
      case 'fr':
        $this->options['decimal'] = ',';
        $this->options['separator'] = ' ';
        $this->options['prefix'] = '';
        $this->options['suffix'] = !empty($is_currency) ? '$' : $this->options['suffix'];
        break;
    }

    // Use the Bank's rounding rules.
    if ($this->options['set_precision'] && $this->options['wb_precision']) {
      $this->options['precision'] = is_numeric($row->wbapi_data_decimal) ? $row->wbapi_data_decimal : 0;
    }

    // Render value, stash it for later access of the raw rounded value.
    $val = parent::render($row);
    $this->all_values[$this->field_alias] = $row->{$this->field_alias};
    $this->all_values_rendered[$this->field_alias] = $val;

    // Add a css wrapper for large numbers to allow for text scaling.
    // Larger than one billion.
    if ($row->{$this->field_alias} > 1000000000) {
      $render = "<span class='hugenum'>" . $val . "</span>";
    }
    // Larger than one million.
    elseif ($row->{$this->field_alias} > 1000000) {
      $render = "<span class='bignum'>" . $val . "</span>";
    }
    else {
      $render = parent::render($row);
    }

    // Put original options back.
    $this->options = $original_options;

    return $render;
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
    if (is_numeric($a->{$this->orderby['field_alias']}) && is_numeric($b->{$this->orderby['field_alias']})) {
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
    if (is_numeric($a->{$this->orderby['field_alias']}) && is_numeric($b->{$this->orderby['field_alias']})) {
      return $a->{$this->orderby['field_alias']} < $b->{$this->orderby['field_alias']};
    }
    // Locale-aware string comparison.
    else {
      return !strcoll($a->{$this->orderby['field_alias']}, $b->{$this->orderby['field_alias']});
    }
  }
}
