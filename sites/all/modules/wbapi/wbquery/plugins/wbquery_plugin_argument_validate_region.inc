<?php

/**
 * Validate that a region is available from the API
 */
class wbquery_plugin_argument_validate_region extends views_plugin_argument_validate {

  function validate_argument($arg) {
    if (wbapi_regions_load($arg)) {
      return TRUE;
    }
    return FALSE;
  }
}
