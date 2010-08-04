<?php
// $Id$

/**
 * @file
 *
 * Override a views style for views summary.
 */
class views_handler_argument_string_alphabet_icons extends views_handler_argument_string {

  /**
   * Get the formula for this argument.
   *
   * $this->ensure_my_table() MUST have been called prior to this.
   */
  function get_formula() {
    $options = parent::get_formula();

    return "SUBSTR(REPLACE($this->table_alias.$this->real_field, '\"', ''), 1, " . intval($this->options['limit']) . ")";
  }


}


