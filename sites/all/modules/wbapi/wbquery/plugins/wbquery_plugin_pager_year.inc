<?php

/**
 * Provide a year based pager to use with the wbquery plugin.
 */
class wbquery_plugin_pager_year extends views_plugin_pager {

  function summary_title() {
    return t('@count years', array('@count' => $this->options['years_per_page']));
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['years_per_page'] = array('default' => 5);
    $options['first_year'] = array('default' => 1980);
    $options['id'] = array('default' => 0);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['years_per_page'] = array(
      '#title' => t('Years per page'),
      '#type' => 'textfield',
      '#description' => t('The number of years to display per page.'),
      '#default_value' => $this->options['years_per_page'],
    );
    $form['first_year'] = array(
      '#title' => t('First year to display'),
      '#type' => 'textfield',
      '#description' => t('The oldest year to display.'),
      '#default_value' => $this->options['first_year'],
    );
    $form['id'] = array(
      '#type' => 'textfield',
      '#title' => t('Pager ID'),
      '#description' => t("Unless you're experiencing problems with pagers related to this view, you should leave this at 0. If using multiple pagers on one page you may need to set this number to a higher value so as not to conflict within the ?page= array. Large values will add a lot of commas to your URLs, so avoid if possible."),
      '#default_value' => $this->options['id'],
    );
  }

  function query() {
    global $pager_page_array, $pager_total_items;

    if ($this->view->base_table == 'wbapi_data') {
      $pager_total_items = pager_load_array($this->options['first_year'], $this->options['id'], $pager_total_items);
      $page = isset($_GET['page']) ? $_GET['page'] : '';
      $pager_page_array = explode(',', $page);

      $offset = $pager_page_array[$this->options['id']] * $this->options['years_per_page'];
      $start = variable_get('wbapi_current_year', '2008') - $offset;
      $end = $start - $this->options['years_per_page'] + 1;
      if ($end < $this->options['first_year']) {
        $end = $this->options['first_year'];
      }
      $this->view->query->requests['wbapi_data']->setFilter('date', "$end:$start");
    }
  }

  function render($input) {
    $pager_theme = views_theme_functions('wbquery_year_pager', $this->view, $this->display);
    return theme($pager_theme, array('input' => $input, 'limit' => $this->options['years_per_page'], 'id' => $this->options['id']));
  }
}
