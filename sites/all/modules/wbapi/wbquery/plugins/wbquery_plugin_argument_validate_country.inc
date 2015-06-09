<?php

/**
 * Validate that a country is available from the API
 */
class wbquery_plugin_argument_validate_country extends views_plugin_argument_validate {

  /**
   * Validate that the argument contains all valid country codes. Codes may be
   * seperated by a semi-colon as per the API.
   */
  function validate_argument($arg) {
    // 1W is an actual aggregate code (not an invented key like 'incomes' or
    // 'countries'. It is included as an explicit validation exception, as at
    // time of writing country API calls using non-english locale are not
    // returning 1W as part of the result set.
    if (in_array($arg, array('all', 'regions', 'incomes', 'countries', '1W'))) {
      return TRUE;
    }
    if (strpos($arg, ';') !== FALSE) {
      $arg = explode(';', $arg);
    }
    elseif (strpos($arg, '-') != FALSE) {
      $arg = explode('-', $arg);
    }
    else {
      $arg = array($arg);
    }
    foreach ($arg as $cc) {
      if (!wbapi_countries_load($cc)) {
        return FALSE;
      }
    }
    return TRUE;
  }
}
