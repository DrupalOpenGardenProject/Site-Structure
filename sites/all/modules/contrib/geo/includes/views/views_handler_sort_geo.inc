<?php // $Id: views_handler_sort_geo.inc,v 1.3 2010/01/13 18:29:46 vauxia Exp $

class views_handler_sort_geo extends views_handler_sort {

  function init(&$view, $options) {
    parent::init($view, $options);
    $this->geo = geo_load(array('gid' => $this->definition['geo_gid']));
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['function'] = array('default' => 'distance');
    $options['target'] = array(
      'input' => array('default' => 'geo_latlon'),
      'value' => array('default' => array()),
    );
    return $options;
  }

  function options_form(&$form, &$form_state) {
    // Call my parent's options_form method.
    parent::options_form($form, $form_state);

    // Use the geo_views helper function to display the target settings.
    geo_views_target_form($form, $form_state, $this, 'sort');
  }

  function query() {
    $this->geo = geo_load(array('gid' => $this->definition['geo_gid']));

    // The GIS function we'll be sorting on.
    $function = $this->options['function'];

    // Figure out whether or not we need a target value to compare against.
    if (FALSE === ($target = geo_views_set_target($this, $this->value))) {
      // Return if target = FALSE to prevent an erroneous query.
      return;
    }

    // If the field was already added by another equation, use its value.
    if (is_object($target)) {
      $orderby = $target->columnName();
    }
   
    // Otherwise, add and use the sort value.
    else {
      $table = $this->ensure_my_table();
      $this->field_alias = $this->field .'_'. $function;

      // Ensure that the query acts on the table and column aliases defined here.
      $this->geo->setTableName($table);
      $this->geo->setColumnName($this->field);

      // Add the field, using the Geo API method for getting it.
      $field = $this->geo->$function($this->geo, $target);
      $this->query->add_field(NULL, $field, $this->field_alias);
      $orderby = $this->field_alias;
    }

    $this->query->add_orderby(NULL, NULL, $this->options['order'], $orderby);
  }
}
