<?php //$Id: views_handler_field_geo.inc,v 1.8 2010/01/13 18:29:46 vauxia Exp $

class views_handler_field_geo extends views_handler_field {

  function init(&$view, $options) {
    parent::init($view, $options);
    $this->geo = geo_load(array('gid' => $this->definition['geo_gid']));
  }

  function options_definition() {
    $options = parent::option_definition();
    $options['function'] = array('default' => 'AsText');
    $options['target'] = array(
      'value' => array('default' => array()),
    );
    $options['input'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    // Call my parent's options_form method.
    parent::options_form($form, $form_state);

    // Use the geo_views helper function to display the target settings.
    geo_views_target_form($form, $form_state, $this, 'display');
  }

  function query() {

    // The GIS Function we'll be using to query the database.
    $function = $this->options['function'];
    if (!$function) return;

    // Figure out whether or not we need a target value to compare against.
    if (FALSE === ($target = geo_views_set_target($this, $this->value))) {
      // Return if target = FALSE to prevent an erroneous query.
      return;
    }

    // We are deriving the target from a filter value.
    if (is_object($target)) {
      drupal_set_message(print_r($target, 1));
    }

    $table = $this->ensure_my_table();
    $this->geo->setTableName($table);
    $this->geo->setColumnName($this->field);

    // Add the field, using the Geo API method for getting it.
    $field = $this->geo->$function($this->geo, $target);
    $alias = $this->real_field .'_'. strtolower($function);
    $this->field_alias = $this->query->add_field(NULL, $field, $alias);
  }
}
