<?php

/**
 * @file
 * Definition of views_handler_argument_null.
 */

/**
 * Argument handler for query string parameter in a JSON file URL.
 *
 * @ingroup views_argument_handlers
 */
class views_json_query_handler_argument_query_string extends views_handler_argument {

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

  /**
   * {@inheritdoc}
   */
  function default_actions($which = NULL) {
    $keys = array('ignore', 'not found', 'default', 'access denied');
    if ($which) {
      if (in_array($which, $keys)) {
        return parent::default_actions($which);
      }
      return;
    }
    $actions = parent::default_actions();
    foreach (array_keys($actions) as $key) {
      if (!in_array($key, $keys)) {
        unset($actions[$key]);
      }
    }
    return $actions;
  }

  function validate_argument_basic($arg) {
    return parent::validate_argument_basic($arg);
  }

  /**
   * {@inheritdoc}
   */
  function query($group_by = FALSE) {
    $this->query->query_string[$this->options['name']] = $this->argument;
  }
}