<?php
// $Id$

/**
 * @file
 *
 * Override a views style for views summary.
 */
class views_handler_field_title_filter extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();
    $options['filter_punctuation'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['filter_punctuation'] = array(
      '#type' => 'checkbox',
      '#title' => t('Strip punctuation'),
      '#description' => t('If checked, punctuation will be removed from title.'),
      '#default_value' => $this->options['filter_punctuation'],
    );
    $form['filter_numeric'] = array(
      '#type' => 'checkbox',
      '#title' => t('Strip Numbers'),
      '#description' => t('If checked, numbers will be removed from title.'),
      '#default_value' => $this->options['filter_numeric'],
    );
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    if ($this->options['filter_punctuation']) {
      $value = $this->filter_punctuation($value);
    }
    if ($this->options['filter_numbers']) {
      $value = $this->filter_numbers($value);
    }
    return $value;
  }

  function filter_punctuation($value) {
    $value = preg_replace('/[^a-zA-Z0-9-\s]/', '', $value);
    return $value;
  }

  function filter_numbers($value) {
    $value = preg_replace('/[^0-9-\s]/', '', $value);
    return $value;
  }
}
