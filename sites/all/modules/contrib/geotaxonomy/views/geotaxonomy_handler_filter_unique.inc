<?php
// $Id
/**
 * @file
 * Class definition for geotaxonomy_handler_filter_uniqe.
 * Only allows one base_id/location pair, helpful on map listings.
 */

class geotaxonomy_handler_filter_unique extends views_handler_filter {
  function option_definition() {
    return array();
  }

  /**
   * Add field form.
   */
  function options_form(&$form, &$form_state) {
  }

  function query() {
    $this->ensure_my_table();
    $this->query->add_groupby($this->query->base_field);
    $this->query->add_groupby($this->table_alias .'.'. $this->real_field);
    $this->query->distinct = TRUE;
    $this->query->no_distinct = TRUE;
  }
}