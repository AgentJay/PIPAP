<?php

/**
 * @file
 *
 * Request objects for the wbapi
 */

/**
 * Base request object
 */
class wbapiRequest {

  // API version, currently unused and for reference only.
  public $version = '2';

  /**
   * $url holds the end point of the request, those methods that
   * alter the path of the end point should change this property.
   */
  public $url;

  /**
   * $language holds the language for the request.
   */
  public $language;

  /**
   * $params is an array of arguments that will be added to the request. Items
   * added to this array should *not* be urlencoded, encoded will be handed by
   * the request() method.
   */
  public $params = array();

  /**
   * Factory method used to create Request objects.
   *
   * @param $type
   *   The key of the request type.
   * @param $lang
   *   Language code; en, es, fr, ar, etc. Optional, defaults to current
   *   language.
   */
  static function factory($type, $lang = NULL) {
    switch ($type) {
      case 'languages':
        return new wbapiRequestLanguages($lang);
      case 'countries':
        return new wbapiRequestCountries($lang);
      case 'regions':
        return new wbapiRequestRegions($lang);
      case 'adminRegions':
        return new wbapiRequestAdminRegions($lang);
      case 'topics':
        return new wbapiRequestTopics($lang);
      case 'sources':
        return new wbapiRequestSources($lang);
      case 'incomeLevels':
        return new wbapiRequestIncomeLevels($lang);
      case 'lendingTypes':
        return new wbapiRequestLendingTypes($lang);
      case 'indicators':
        return new wbapiRequestIndicators($lang);
      case 'data':
        return new wbapiRequestData($lang);
    }
  }

  /**
   * Constructor for the request, need to be invoke by extending classes.
   */
  function __construct($lang) {
    global $language;
    $this->url = 'http://' . variable_get('wbapi_url', 'api.worldbank.org');

    if (!empty($lang)) {
      $this->language = $lang;
      $this->url .= '/' . $lang;
    }
    elseif (!empty($language->language)) {
      $this->language = $language->language;
      $this->url .= '/' . $language->language;
    }
  }

  /**
   * Add a filter to the request. Classes that extend this one should declare
   * what $keys are accepted.
   *
   * @param $key
   *   The filter to set
   * @param $value
   *   The value to set for the $key.
   */
  public function setFilter($key, $value) {
    $this->params[$key] = $value;
    return $this;
  }

  /**
   * Manage and make the http requests. This is the main public entry point.
   *
   * @return an array of items or FALSE if error.
   */
  public function request() {
    // As we only support JSON currently, we bail if we cannnot parse it.
    if (!function_exists('json_decode')) {
      watchdog('error', 'Function `json_decode` is not available.');
      return FALSE;
    }

    // `countries` method content-length is 21178 w/xml vs 13893 w/json. So we
    // use json if we can.
    $this->params['format'] = 'json';

    // The default `per_page` value is way to small, we raise it from 50 to 1K.
    $this->params['per_page'] = '1000';

    $url = $this->url . '?' . $this->query_string();

    if ($cache = $this->cache_get($url)) {
      $data = $cache->data;
      wbapi_log($url, -1);
    }
    else {
      $ts = microtime(true);
      $data = $this->_request($url);
      $this->filter_result($data);
      $t = microtime(true) - $ts;
      $this->cache_set($url, $data);
      wbapi_log($url, $t);
    }
    return $data;
  }

  /**
   * Generate a query string based on object parameters
   */
  protected function query_string() {
    if (!empty($this->params)) {
      $params = array();
      foreach ($this->params as $k => $v) {
        if ($k == 'date') {
          // Date is a special case, contains ":" which shouldn't be urlencoded
          list($start, $end) = explode(':', $v);
          if (is_numeric($start) && is_numeric($end)) {
            $params[] = "$k=$start:$end";
          }
        }
        else {
          $params[] = $k . '=' . urlencode($v);
        }
      }
      return implode('&', $params);
    }
  }

  /**
   * Make the actual HTTP request and parse output
   *
   * TODO support XML also.
   */
  protected function _request($url, $l = 1) {
    // Limit to ten levels of recursion.
    if ($l > 10) {
      watchdog('warning', "World Bank API recusion limit reached.");
      return array();
    }
    $l++;

    $response = drupal_http_request($url);

    if ($response->code == '200') {
      $data = json_decode($response->data);
      if (is_array($data)) {
        list($head, $values) = $data;
        // A full reponse may be spread over several pages, so if there are
        // additional pages we retrieve them.
        if (($head->page < $head->pages) && ($head->per_page < $head->total)) {
          $this->params['page'] = $head->page + 1;
          $url = $this->url . '?' . $this->query_string();
          if ($recurse = $this->_request($url, $l)) {
            $values = array_merge($values, $recurse);
          }
        }
        return $values;
      }
      else {
        watchdog('error', "Didn't receive valid API response (invalid JSON).");
      }
    }
    else {
      watchdog('error', 'HTTP error !code received', array('!code' => $response->code));
    }
    return FALSE;
  }

  /**
   * Populate the cache. Wrapper around Drupal's cache_get()
   *
   * @param $url
   *   The API url that would be used.
   * @param $reset
   *   Set to TRUE to force a retrieval from the database.
   */
  protected function cache_get($url, $reset = FALSE) {
    static $items = array();

    $cid = $this->cache_id($url);
    if (!isset($items[$cid]) || $reset) {
      $items[$cid] = cache_get($cid, 'cache_wbapi');
      // Don't return temporary items more that 5 minutes old.
      if (!empty($items[$cid]) && $items[$cid]->expire === CACHE_TEMPORARY && $items[$cid]->created > (REQUEST_TIME + 300)) {
        return FALSE;
      }
    }
    return $items[$cid];
  }

  /**
   * Retrieve the cache. Wrapper around Drupal's cache_set()
   */
  protected function cache_set($url, $data) {
    if ($data === FALSE) {
      // If we don't get a response we set a temporary cache to prevent hitting
      // the API frequently for no reason.
      cache_set($this->cache_id($url), FALSE, 'cache_wbapi', CACHE_TEMPORARY);
    }
    else {
      cache_set($this->cache_id($url), $data, 'cache_wbapi');
    }
  }

  /**
   * Helper function to generate a cache id based on the class name and
   * hash of the url
   */
  protected function cache_id($url) {
    return get_class($this) . ':' . md5($url);
  }

  /**
   * Filters result.
   */
  protected function filter_result(&$result) { }

  /**
   * Maps internal codes to WB API codes.
   */
  protected function map_code($code) {
    switch ($code) {
      case 'regions':
        $codes = array();
        foreach (wbapiRequest::factory('regions')->request() as $r) {
          if ($r->id != 'NA') {
            $codes[] = $r->id;
          }
        }
        return implode(';', $codes);
      case 'incomes':
      case 'countries':
        return 'all';
    }
    return $code;
  }

  /**
   * Return country blacklist as an array.
   */
  protected function country_blacklist() {
    static $blacklist;
    if (!is_array($blacklist)) {
      if (!$blacklist = explode(',', variable_get('wbapi_blacklist_countries', WBAPI_BLACKLIST_COUNTRIES_DEFAULT))) {
        $blacklist = array();
      }
    }
    return $blacklist;
  }

  /**
   * Determine whether given id is a country id. Invoked from filter_result().
   *
   * Does not return countries that are blacklisted.
   *
   * Unfortunately there is no good way of determining which entity is a country
   * and which is not. This fact is not even properly recorded in the database
   * powering the WB API. We go for a short cut here.
   *
   * @todo Push filtering by country back into WB API.
   */
  protected function is_country($id) {
    if (in_array($id, array('1W', '4E', '7E', '8S', 'ZF'))) {
      return FALSE;
    }
    if (!$this->is_allowed_country($id)) {
      return FALSE;
    }
    if (stripos($id, 'x') === 0) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Determine whether given country id is not blacklisted.
   *
   * @todo: Push blacklist back into WB API.
   */
  protected function is_allowed_country($id) {
    if (in_array($id, $this->country_blacklist())) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Determines whether a given id is an income level id.
   *
   * wbapiRequestIncomeLevels returns three letter codes, can't be used here.
   *
   * @todo Push filtering by income level back into WB API.
   */
  protected function is_income_level($id) {
    if (in_array($id, array('XD', 'XL', 'XM', 'XN', 'XO', 'XQ', 'XR', 'XS'))) {
      return TRUE;
    }
    return FALSE;
  }

}

/**
 * Make request against the Countries method.
 *
 * This class only exposes a small subset of the full functionality. Here we
 * allow only querying for the full list of countries and details about a
 * single country.
 *
 * This class extends the normal setFilter() parameters:
 * - "code" : an country or region id to lookup. The keywords 'countries',
 *            'incomes' are also supported. TODO add 'regions'
 * - "regions" : a regions  to filter countries by
 */
class wbapiRequestCountries extends wbapiRequest {
  /**
   * Request a the list of countries or metadata on single country.
   */
  function request() {
    $this->url .= '/countries';
    if (!empty($this->params['code'])) {
      $this->code = $this->params['code'];
      if ($this->params['code'] != 'incomes' && $this->params['code'] != 'countries') {
        $this->url .= '/' . $this->params['code'];
        unset($this->params['code']);
      }
    }
    $result = parent::request();
    return $result;
  }

  /**
   * Filters result depending on requested code.
   *
   * Pass-by-reference $result to void copying very large arrays.
   */
  protected function filter_result(&$result) {
    if ($result && isset($this->code)) {
      switch ($this->code) {
        case 'incomes':
          $method = 'is_income_level';
          break;
        case 'countries':
          $method = 'is_country';
          break;
        default:
          $method = 'is_allowed_country';
          break;
      }
      foreach ($result as $k => $r) {
        if (isset($r->iso2Code) && !call_user_func(array($this, $method), $r->iso2Code)) {
          unset($result[$k]);
        }
      }
      if (!in_array($this->code, array('countries', 'incomes'))) {
        $code = strtoupper($this->code);
        foreach ($result as $v) {
          if ($v->iso2Code == $code || $v->id == $code) {
            $result = array($v);
            return;
          }
        }
      }
    }
  }
}

/**
 * Request list of regions.
 *
 * There is no direct way of retrieving this information from the API currently
 * so we need to extract it from the country list.
 *
 * This class extends the normal setFilter() parameters:
 *
 * - "code" : a region to lookup.
 */
class wbapiRequestRegions extends wbapiRequest {

  /**
   * Complete override of the parent request method.
   */
  function request() {
    if (!empty($this->params['code'])) {
      $code = strtoupper($this->params['code']);
      unset($this->params['code']);
    }

    $url = $this->url . '/regions?' . $this->query_string();

    if ($cache = $this->cache_get($url)) {
      $data = $cache->data;
    }
    else {
      $countries = wbapiRequest::factory('countries', $this->language)->request();
      $data = array();
      if ($countries) {
        foreach ($countries as $v) {
          if ($v->region->id == 'NA') {
            // Collect aggregates
            $aggregates[$v->id] = $v;
          }
          elseif (!isset($data[$v->region->id]) &&
            $v->region->id != 'NWB'   // Hide non-world-bank countries
          ) {
            $data[$v->region->id] = $v->region;
          }
        }

        // Populate iso2Codes
        foreach ($data as $k => $v) {
          $data[$k]->iso2Code = $aggregates[$v->id]->iso2Code;
        }
      }
      $this->cache_set($url, $data);
    }

    if (isset($code)) {
      foreach ($data as $v) {
        if ($v->id == $code || $v->iso2Code == $code) {
          return $v;
        }
      }
      return FALSE;
    }
    return $data;
  }
}

/**
 * Request list of admin regions.
 *
 * There is no direct way of retrieving this information from the API currently
 * so we need to extract it from the country list.
 *
 * This class extends the normal setFilter() parameters:
 *
 * - "code" : a region to lookup.
 */
class wbapiRequestAdminRegions extends wbapiRequest {

  /**
   * Complete override of the parent request method.
   */
  function request() {
    if (!empty($this->params['code'])) {
      $code = strtoupper($this->params['code']);
      unset($this->params['code']);
    }

    $url = $this->url . '/adminRegions?' . $this->query_string();

    if ($cache = $this->cache_get($url)) {
      $data = $cache->data;
    }
    else {
      $countries = wbapiRequest::factory('countries', $this->language)->request();
      $data = array();
      if ($countries) {
        foreach ($countries as $v) {
          // @todo: revise this. We are using region id's iso2code's here.
          if ($v->region->id == 'NA') {
            // Collect aggregates
            $aggregates[$v->id] = $v;
          }
          elseif ($v->adminregion->id && !isset($data[$v->adminregion->id]) && $v->region->id != 'NWB') {
            $data[$v->adminregion->id] = $v->adminregion;
          }
        }

        // Populate iso2Codes @todo: revise, we are using region id's iso2codes.
        foreach ($data as $k => $v) {
          if (isset($data[$k])) {
            $data[$k]->iso2Code = $aggregates[$v->id]->iso2Code;
          }
        }
      }
      $this->cache_set($url, $data);
    }

    if (isset($code)) {
      foreach ($data as $v) {
        if ($v->id == $code || $v->iso2Code == $code) {
          return $v;
        }
      }
      return FALSE;
    }
    return $data;
  }
}

/**
 * Request topics or a single topic
 *
 * This class extends the normal setFilter() parameters:
 *
 * - "id" : a topic id to lookup.
 */
class wbapiRequestTopics extends wbapiRequest {
  /**
   * Request a the list of topics, or indicators within a single topic.
   *
   * @param $id
   *
   */
  function request() {
    $this->url .= '/topics';
    $data = parent::request();
    if (!empty($data) && isset($this->params['id'])) {
      foreach ($data as $topic) {
        if ($topic->id == $this->params['id']) {
          return array($topic);
        }
      }
      return FALSE;
    }
    return $data;
  }
}

/**
 * Retrieve a list of items from the API, and return the entire list or, if
 * requested information about a single item. Meant to be extended by other
 * classes which target API methods that return simple lists.
 *
 * This class extends the normal setFilter() parameters:
 *
 * - "id" : an id to lookup.
 */
abstract class wbapiRequestList extends wbapiRequest {
  /**
   * Return the entire list or, if requested information about a single item.
   *
   * @param $id
   *   The API id of the source.
   */
  function request() {
    if (!empty($this->params['id'])) {
      $id = $this->params['id'];
      if (!is_numeric($id)) {
        $id = strtoupper($id);
      }
      unset($this->params['id']);
    }

    $items = parent::request();

    if (isset($id)) {
      foreach ($items as $v) {
        if ($v->id == $id) {
          return $v;
        }
      }
      return FALSE;
    }
    return $items;
  }
}

/**
 * Retrieve the list of sources, and return the entire list or, if requested
 * information about a single source.
 */
class wbapiRequestSources extends wbapiRequestList {
  // Override request method to target the right path.
  function request() {
    $this->url .= '/sources';
    return parent::request();
  }
}

/**
 * Retrieve the list of Income Levels, and return the entire list or, if requested
 * information about a single level.
 */
class wbapiRequestIncomeLevels extends wbapiRequestList {
  // Override request method to target the right path.
  // @todo Unify filtering across all request() methods.
  function request() {
    $blacklist = array('NA', 'NWB');
    if (isset($this->params['id']) && in_array($this->params['id'], $blacklist)) {
      return FALSE;
    }

    // Remove code parameter to take better advantage of caching.
    if (!empty($this->params['id'])) {
      $id = strtoupper($this->params['id']);
      unset($this->params['id']);
    }

    $url = $this->url . '/incomeLevels?' . $this->query_string();

    if (FALSE) { // $cache = $this->cache_get($url)) {
      $data = $cache->data;
    }
    else {
      $countries = wbapiRequest::factory('countries', $this->language)->request();
      $data = array();
      if ($countries) {
        foreach ($countries as $v) {
          if ($v->incomeLevel->id == 'NA') {
            // Collect aggregates
            $aggregates[$v->id] = $v;
          }
          elseif ($v->incomeLevel->id &&
            !isset($data[$v->incomeLevel->id]) &&
            !in_array($v->incomeLevel->id, $blacklist)
          ) {
            $data[$v->incomeLevel->id] = $v->incomeLevel;
          }
        }

        // Populate iso2Codes.
        foreach ($data as $k => $v) {
          $data[$k]->iso2Code = $aggregates[$v->id]->iso2Code;
        }
      }
      $this->cache_set($url, $data);
    }

    if (isset($id)) {
      foreach ($data as $v) {
        if ($v->id == $id || $v->iso2Code == $id) {
          return $v;
        }
      }
      return FALSE;
    }
    return $data;
  }
}

/**
 * Retrieve the list of Lending Types, and return the entire list or, if requested
 * information about a single type.
 */
class wbapiRequestLendingTypes extends wbapiRequestList {
  // Override request method to target the right path.
  function request() {
    $this->url .= '/lendingTypes';
    return parent::request($id);
  }
}

/**
 * Retrieve the full indicator listing or, if requested, information about a
 * single one.
 *
 * This class extends the normal setFilter() parameters:
 *
 * - "indicator" : an indicator to lookup.
 * - "topic" : a topic ID by which to filter indicators.
 */
class wbapiRequestIndicators extends wbapiRequest {
  /**
   * Reterive indicator list of information about a single indicator from the
   * API.
   */
  function request() {
    if (!empty($this->params['topic'])) {
      $this->url .= '/topics/' . $this->params['topic'] . '/indicators';
    }
    elseif (empty($this->params['indicator'])) {
      $this->url .= '/indicators';
    }
    else {
      $this->url .= '/indicators[' . $this->params['indicator'] . ']';
    }
    unset($this->params['indicator']);
    $result = parent::request();
    return $result;
  }

  /**
   * Filter out results that weren't requested.
   * Most filtering operations are handled by the API directly - we implement
   * only filtering for "uncategorized" topics (indicated by
   * $this->param['topic'] === FALSE) here.
   */
  protected function filter_result(&$result) {
    if (isset($this->params['topic']) && $this->params['topic'] === FALSE) {
      foreach ($result as $key => $item) {
        if (!empty($item->topics)) {
          unset($result[$key]);
        }
      }
      // Rekey.
      $result = array_values($result);
    }
  }
}

/**
 * Request a data series from the API
 *
 * This class extends the normal setFilter() parameters:
 *
 * - "indicator" : an id to lookup. REQUIRED.
 * - "code" : an country or region id to lookup. The keywords 'all',
 *            'countries', 'regions' and 'incomes' are also supported. REQUIRED.
 * - "year" : an id to lookup.
 * - "date" : set a date range of the form "2000:2002", this parameter is
 *            incompabitle, and takes precedence over, "year".
 *
 */
class wbapiRequestData extends wbapiRequest {
  /**
   * Retrive a data series from the API
   */
  function request() {
    // Bail if required paramaters aren't set.
    if (empty($this->params['indicator']) || empty($this->params['code'])) {
      return FALSE;
    }

    if (
      isset($this->params['year']) &&
      is_numeric($this->params['year']) &&
      !isset($this->params['date'])
    ) {
      $this->params['date'] = $this->params['year'] . ':' . $this->params['year'];
      unset($this->params['year']);
    }

    // Don't allow requesting all years & all countries.
    if (in_array($this->params['code'], array('all', 'regions', 'incomes'))
      && !isset($this->params['date'])
    ) {
      return FALSE;
    }

    // Build URL with code mapped from internal code to WB API code.
    $this->code = $this->params['code'];
    $this->url .= '/countries/' . $this->map_code($this->code) . '/indicators/' . $this->params['indicator'];

    // Don't attach code and indicator to URL in parent::request().
    unset($this->params['code']);
    unset($this->params['indicator']);

    $result = parent::request();
    return $result;
  }

  /**
   * Filters result depending on requested code.
   *
   * Pass-by-reference $result to void copying very large arrays.
   */
  protected function filter_result(&$result) {
    if (!empty($this->code)) {
      switch ($this->code) {
        case 'incomes':
          $method = 'is_income_level';
          break;
        case 'countries':
          $method = 'is_country';
          break;
        default:
          return;
      }
      if (is_array($result)) {
        foreach ($result as $k => $r) {
          if (isset($r->country->id) && !call_user_func(array($this, $method), $r->country->id)) {
            unset($result[$k]);
          }
        }
      }
    }
  }
}

/**
 * Fake a missing API method to get available languages.
 */
class wbapiRequestLanguages {
  // Main function, get the languages.
  public function request() {
    $langs = array(
      'en' => 'English',
      'es' => 'Español',
      'fr' => 'Français',
      'ar' => 'العربية',
    );
    $items = array();
    foreach ($langs as $k => $v) {
      $i = new stdClass();
      $i->id = $k;
      $i->value = $v;
      $items[] = $i;
    }
    return $items;
  }
}
