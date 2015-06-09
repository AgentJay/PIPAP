<?php
/**
 * @file
 * Base filter handler for views_json_query.
 */

class views_json_query_handler_filter_query_string extends views_handler_filter_string {

  /**
   * {@inheritdoc}
   */
  public $no_operator = TRUE;

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['name'] = array('default' => '');
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function operators() {
    return array();
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#default_value' => $this->options['name'],
      '#description' => t('The name of the query string parameter, as used in the JSON file URI.'),
      '#required' => TRUE,
    );
  }

  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#size' => 30,
      '#default_value' => $this->value,
    );
    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];
      if (!isset($form_state['input'][$identifier])) {
        $form_state['input'][$identifier] = $this->value;
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  function query() {
    $this->query->query_string[$this->options['name']] = $this->value;
  }

  /**
   * {@inheritdoc}
   */
  function ui_name($short = FALSE) {
    if (!empty($this->options['ui_name'])) {
      $title = check_plain($this->options['ui_name']);
      return $title;
    }
    $title = ($short && isset($this->definition['title short'])) ? $this->definition['title short'] : $this->definition['title'];
    return t('!title: !name', array('!name' => $this->options['name'], '!title' => $title));
  }
}