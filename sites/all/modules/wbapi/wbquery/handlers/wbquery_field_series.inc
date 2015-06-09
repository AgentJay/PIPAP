<?php

/**
 * Series handler for WB Query object.
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
 *     - country_id: us, value_2008: 0, value_2007: 1, value_2006: 2
 *     - country_id: fr, value_2008: 0, value_2007: 1, value_2006: 2
 *
 *   labelby: Used by parent class wbquery_field_numeric for formatting values.
 *
 *   CANNOT be used in conjuction with wbquery_field_latest on the same view.
 */
class wbquery_field_series extends wbquery_field_numeric {
  function option_definition() {
    $options = parent::option_definition();
    $options['series_sort'] = array('default' => 'ASC');
    return $options;
  }

  function options_form(&$form, $form_state) {
    $form['series_sort'] = array(
      '#title' => t('Series behavior'),
      '#type' => 'select',
      '#options' => array(
        'ASC' => t('Ascending'),
        'DESC' => t('Descending'),
        'LATEST' => t('Latest value'),
      ),
      '#default_value' => $this->options['series_sort'],
    );

    parent::options_form($form, $form_state);
  }

  function construct() {
    parent::construct();
    $this->expanded = array();
    $this->labels = array();
  }

  function pre_render($values) {
    $this->view->result = $this->expand_fields($values);
  }

  function expand_fields($values) {
    $groupby = $this->aliases[$this->definition['groupby']];

    // First process the resultset to determine how many fields instances we
    // need to spawn.
    foreach ($values as $num => $row) {
      $new_alias = NULL;
      $id = $row->{$groupby};
      if (isset($row->{$this->aliases['date']})) {
        if (isset($row->{$this->field_alias})) {
          $new_alias = $row->{$this->aliases['date']};
          $new_alias = "{$this->field_alias}_{$new_alias}";
          $new_value = $row->{$this->field_alias};

          // Add new field to list of expanded fields.
          $this->expanded[$new_alias] = $new_alias;
          $this->labels[$new_alias] = !isset($this->labels[$new_alias]) ? $row->{$this->aliases['date']} : $this->labels[$new_alias];
        }

        // Compress value rows.
        if (!isset($values[$id])) {
          unset($row->{$this->field_alias});
          unset($row->{$this->aliases['date']});
          $values[$id] = $row;
        }
        if (isset($new_alias)) {
          $values[$id]->{$new_alias} = $new_value;
        }
      }
      unset($values[$num]);
    }
    // Sort years either ASC or DESC.
    if ($this->options['series_sort'] === 'ASC') {
      ksort($this->expanded);
      ksort($this->labels);
    }
    else {
      krsort($this->expanded);
      krsort($this->labels);
      if ($this->options['series_sort'] == 'LATEST') {
        $this->expanded = array(array_shift($this->expanded));
        $this->labels = array(array_shift($this->labels));
      }
    }

    // Generate nicer IDs for theming expanded fields.
    // Note that this takes advantage of the fact that Views css safe allows
    // spaces to pass through.
    $renamed = array();
    $labels = array();
    foreach (array_values($this->expanded) as $num => $new_alias) {
      if ($num === 0) {
        $renamed["{$new_alias} {$this->field_alias} {$this->field_alias}-first"] = $new_alias;
        $labels["{$new_alias} {$this->field_alias} {$this->field_alias}-first"] = $this->labels[$new_alias];
      }
      elseif ($num == count($this->expanded) - 1) {
        $renamed["{$new_alias} {$this->field_alias} {$this->field_alias}-last"] = $new_alias;
        $labels["{$new_alias} {$this->field_alias} {$this->field_alias}-last"] = $this->labels[$new_alias];
      }
      else {
        $renamed["{$new_alias} {$this->field_alias}"] = $new_alias;
        $labels["{$new_alias} {$this->field_alias}"] = $this->labels[$new_alias];
      }
    }
    $this->labels = $labels;
    $this->expanded = $renamed;

    // Set our new field id.
    reset($this->expanded);
    $this->options['id'] = key($this->expanded);

    // Slice out the fields before and after us.
    $position = 0;
    foreach ($this->view->field as $field => $handler) {
      if ($handler === $this) {
        $before = array_slice($this->view->field, 0, $position);
        $after = array_slice($this->view->field, $position + 1);
        break;
      }
      $position++;
    }

    // Spawn new field instances that point to this handler.
    $pseudo_fields = array();
    foreach ($this->expanded as $id => $alias) {
      $pseudo_fields[$id] = $this;
    }

    // Recombine the fields and replace.
    $combined = $before + $pseudo_fields + $after;
    $this->view->field = $combined;

    // If style plugin is storing options about this field spawn copies.
    if (isset($this->view->style_plugin->options['info'][$this->field])) {
      $field_options = $this->view->style_plugin->options['info'][$this->field];
      foreach ($this->expanded as $id => $alias) {
        $this->view->style_plugin->options['info'][$id] = $field_options;
      }
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

  function query() {
    parent::query();

    // Series sort handling if style plugin supports it.
    if (isset($this->view->style_plugin) && ($this->view->style_plugin->build_sort() || $this->view->style_plugin->build_sort_post())) {
      if (isset($_GET['order'])) {
        $split = explode(' ', $_GET['order']);
        foreach ($split as $piece) {
          if ($piece === "{$this->table}_{$this->real_field}") {
            $this->orderby = array(
              'field_alias' => $split[0],
              'order' => $_GET['sort'],
            );
            $this->view->style_plugin->order = $_GET['sort'];
            $this->view->style_plugin->active = $_GET['order'];
          }
        }
      }
    }
  }

  /**
   * Override default click sort handler. Series must do its sorting post
   * query & field expansion so setting an orderby on the query object
   * itself would be pointless.
   */
  function click_sort($order) { }

  function label() {
    // Start.
    if (empty($this->rendered_labels)) {
      $this->rendered_labels = TRUE;
      $label = reset($this->labels);
    }
    // There is still a next label...
    elseif ($label = next($this->labels)) {
    }
    // Rewind.
    else {
      $this->rendered_labels = TRUE;
      $label = reset($this->labels);
    }
    return check_plain($label);
  }

  function render($row) {
    // Store the row as an indicator of which pseudo field has been last
    // rendered. If the current row differs from our last row, we've finished
    // all pseudo fields for the last row and we can reset our stack.
    if (!isset($this->last_row) || $this->last_row != $row) {
      $this->last_row = $row;
      $this->all_values = array();
      $this->all_values_rendered = array();
      reset($this->expanded);
    }
    else {
      $has_next = next($this->expanded);
      // If there is no next pseudo field, there is only a single field in this
      // series. Stay on this field.
      if (!$has_next) {
        reset($this->expanded);
      }
    }
    $this->field_alias = current($this->expanded);
    return parent::render($row);
  }
}
