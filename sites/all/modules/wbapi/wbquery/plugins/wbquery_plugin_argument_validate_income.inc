<?php

/**
 * Validate that an income level is available from the API
 */
class wbquery_plugin_argument_validate_income extends views_plugin_argument_validate {

  function validate_argument($arg) {
    if (wbapi_income_levels_load($arg)) {
      return TRUE;
    }
    return FALSE;
  }
}
