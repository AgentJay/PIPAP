<?php

/**
 * Validate that a country is available from the API
 */
class wbquery_plugin_argument_validate_indicator extends views_plugin_argument_validate {

  function validate_argument($arg) {
    if (wbapi_indicators_load($arg)) {
      return TRUE;
    }
    return FALSE;
  }
}
