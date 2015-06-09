<?php

/**
 * Default argument plugin to extract a topic via menu_get_object
 */
class wbquery_plugin_argument_default_topic extends views_plugin_argument_default {
  function get_argument() {
    foreach (range(1, 3) as $i) {
      $object = menu_get_object('wbapi_topics', $i);
      if (!empty($object)) {
        return $object->id;
      }
      $arg = menu_get_object('views_arg', $i);
      if (!empty($arg)) {
        return $arg;
      }
    }
  }
}

