<?php
// $Id$

/**
 * @file
 *
 * Override a views style for views summary.
 */
class views_handler_argument_title_filter extends views_handler_argument_string {

  function option_definition() {
    $options = parent::option_definition();
    $options['filter_punctuation'] = array('default' => '');
    $options['filter_numeric'] = array('default' => FALSE);
    $options['glossary'] = array('default' => 1);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['filter_punctuation'] = array(
      '#type' => 'textfield',
      '#title' => t('Strip punctuation'),
      '#description' => t('Enter characters to remove, separated by spaces. Example: , . *'),
      '#default_value' => $this->options['filter_punctuation'],
    );
    $form['filter_numeric'] = array(
      '#type' => 'checkbox',
      '#title' => t('Strip Numbers'),
      '#description' => t('If checked, numbers will be removed from title.'),
      '#default_value' => $this->options['filter_numeric'],
    );
  }


  function summary_query() {
    if (empty($this->definition['many to one'])) {
      $this->ensure_my_table();
    }
    else {
      $this->table_alias = $this->helper->summary_join();
    }

    if (empty($this->options['glossary'])) {
      // Add the field.
      $this->base_alias = $this->name_alias = $this->query->add_field($this->table_alias, $this->real_field);
      $this->query->set_count_field($this->table_alias, $this->real_field);
    }
    else {
      // Add the field.
      $formula = $this->get_formula();
      $this->base_alias = $this->name_alias = $this->query->add_field(NULL, $formula, $this->real_field . '_truncated');
      $this->query->set_count_field(NULL, $formula, $this->field, $this->field . '_truncated');
    }

    return $this->summary_basics(FALSE);
  }

  /**
   * Get the formula for this argument.
   *
   * $this->ensure_my_table() MUST have been called prior to this.
   */
  function get_formula() {
    // Build nested trim statement to filter out numbers and selected punctuation from the glossary index.
    $trim_array = array();
    $trim_punctuation = array();
    $trim_numeric = array();

    if (!empty($this->options['filter_punctuation'])) {
      $trim_punctuation = explode(' ', $this->options['filter_punctuation']);
    }
    if ($this->options['filter_numeric']) {
      $trim_numeric = array('0', '1', '2', '3', '4', '5', '6', '7', '8', '9');
    }
    $trim_array = array_merge($trim_punctuation, $trim_numeric);

    $trim_left = '';
    $trim_right = '';

    foreach ($trim_array as $key => $value) {
      $trim_left .= 'TRIM(LEADING \'' . $value . '\' FROM ';
      $trim_right .= ') ';
    }

    $query = "SUBSTR(" . $trim_left . "
      $this->table_alias.$this->real_field "
      . $trim_right . ", 1, " . intval($this->options['limit']) . ")";
    return $query;
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
