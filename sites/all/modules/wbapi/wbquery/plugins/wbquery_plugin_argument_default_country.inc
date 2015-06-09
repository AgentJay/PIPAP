<?php

/**
 * Default argument plugin to extract a country via menu_get_object
 */
class wbquery_plugin_argument_default_country extends views_plugin_argument_default {
  function get_argument() {
    foreach (range(1, 3) as $i) {
      $object = menu_get_object('wbapi_countries', $i);
      if (!empty($object)) {
        return $object->iso2Code;
      }
      $arg = menu_get_object('views_arg', $i);
      if (!empty($arg)) {
        return $arg;
      }
    }
  }
}

