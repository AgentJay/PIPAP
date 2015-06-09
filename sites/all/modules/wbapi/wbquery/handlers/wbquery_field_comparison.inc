<?php

class wbquery_field_comparison extends wbquery_field_numeric {
  function pre_render($values) {
    foreach ($this->view->field as $field) {
      if (get_class($field) === 'wbquery_field_latest') {

        // Copy info from prior latest value handler.
        $this->field_alias = $field->field_alias;
        $this->aliases = $field->aliases;
        $this->proxied = TRUE;

        $this->min_value =  100000000000;
        $this->max_value = -100000000000;
        foreach ($values as $row) {
          $value = (float) $row->{$this->field_alias};
          $this->min_value = $value < $this->min_value ? $value : $this->min_value;
          $this->max_value = $value > $this->max_value ? $value : $this->max_value;
        }
        return;
      }
    }
  }

  /*
   function pre_render($values) {
   }
   */

  function render($values) {
    $value = $values->{$this->field_alias};
    if (is_numeric($value)) {
      // If the range does not cross the origin, scale the graph to min/max
      // values. E.g. 25% to 75% is normalized so that 25% is the smallest
      // bar and 75% is the largest.
      if (($this->min_value * $this->max_value) > 0) {
        $width = ($value - $this->min_value) / ($this->max_value - $this->min_value);
        $width = (int) abs($width * 75);

        // For very small non-zero values, still show with width of 2px so it is
        // still visible.
        $width = ($width <= 2 && $value > 0) ? 2 : $width;
      }
      // If the range crosses the origin, do not scale the graph such that the
      // value extremities are used as smalles/largest values.
      else {
        $width = $value / ($this->max_value - $this->min_value);
        $width = (int) abs($width * 75);

        // For very small non-zero values, still show with width of 2px so it is
        // still visible.
        $width = ($width <= 2 && $value > 0) ? 2 : $width;

        $margin = (int) abs($this->min_value / ($this->max_value - $this->min_value) * 75);
        if ($value < 0) {
          $margin = $margin - $width;
        }
      }

      return "<div class='wbquery-comparison' style='margin-left:{$margin}px; width:{$width}px;'></div>";
    }
  }
}
