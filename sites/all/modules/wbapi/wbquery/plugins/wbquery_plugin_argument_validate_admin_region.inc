<?php

/**
 * Validate that an admin region is available from the API
 */
class wbquery_plugin_argument_validate_admin_region extends views_plugin_argument_validate {

  function validate_argument($arg) {
    if (wbapi_admin_regions_load($arg)) {
      return TRUE;
    }
    return FALSE;
  }
}
