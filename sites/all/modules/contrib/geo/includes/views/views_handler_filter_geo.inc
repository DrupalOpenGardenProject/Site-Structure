<?php // $Id: views_handler_filter_geo.inc,v 1.15 2010/01/13 18:29:46 vauxia Exp $

class views_handler_filter_geo extends views_handler_filter_numeric {

  var $no_single = TRUE;

  function init(&$view, $options) {
    parent::init($view, $options);
    $this->geo = geo_load(array('gid' => $this->definition['geo_gid']));
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['operator'] = array('default' => '<=');
    $options['function'] = array('default' => 'distance');
    $options['input'] = array('default' => 'geo_latlon');

    $options['value'] = array(
      'contains' => array(
        'min' => array('default' => ''),
        'max' => array('default' => ''),
        'value' => array('default' => ''),
        'units' => array('default' => 'mi'),
        'target' => array('default' => array()),
      ),
    );
    $options['target'] = array('default' => array());
    return $options;
  }

  function value_form(&$form, &$form_state) {
    $exposed = !empty($form_state['exposed']);

    // Use the default value_form from the numeric handler.
    parent::value_form($form, $form_state);

    // Add "units"
    $form['value']['units'] = array(
      '#type' => 'select',
      '#title' => t('Units'),
      '#options' => geo_units(),
      '#default_value' => $this->value['units'],
    );
  }

  function options_form(&$form, &$form_state) {
    // Ensure that these inputs get appropriate weights.
    $form['function'] = array();
    $form['op_val_start'] = array();
    $form['operator'] = array();
    $form['value'] = array();
    $form['op_val_end'] = array();
    $form['target_prefix'] = array();
    $form['input'] = array();
    $form['target'] = array();
    $form['target_suffix'] = array();

    // Call my parent's options_form method.
    parent::options_form($form, $form_state);

    // Use the geo_views helper function to display the target settings.
    geo_views_target_form($form, $form_state, $this, 'filter');
  }

  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);

    // Set the value
    $input = $form_state['values']['options']['input'];
    $value = $form_state['values']['options']['target'][$input];
    $form_state['values']['options']['value']['target'] = $value;
  }

  function expose_form_right(&$form, &$form_state) {
    parent::expose_form_right($form, $form_state);

    $form['expose']['show_value'] = array(
      '#type' => 'select',
      '#title' => t('Show value as'),
      '#options' => array(
        'none' => t('Do not allow user to change the value'),
        'select' => t('A list of predefined values'),
        'textfield' => t('A freeform text field'),
      ),
      '#description' => t('Expose the length value for distance and length queries.'),
      '#default_value' => $this->options['expose']['show_value'],
    );
    $form['expose']['value_options'] = array(
      '#type' => 'textfield',
      '#title' => t('Value options'),
      '#description' => t('The list of values a user can select from, separated by commas.'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-options-expose-show-value' => array('select')),
      '#default_value' => $this->options['expose']['value_options'],
    );

    $form['expose']['show_units'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show units'),
      '#description' => t('Allow user to select units of measurement for distance and length queries.'),
      '#default_value' => $this->options['expose']['show_units'],
    );
  }

  function exposed_form(&$form, &$form_state) {
    $key = $this->options['expose']['identifier'];

    // We need to pretend the user already input the defaults.
    if (!isset($form_state['input'][$key])) {
      $form_state['input'][$key] = $this->value;
    }

    $form[$key] = array( '#tree' => TRUE );

    if ($this->options['expose']['show_value'] == 'none') {
      $form[$key]['value'] = array(
        '#type' => 'value',
        '#value' => $this->value['value'],
      );
    }
    else {
      // Use the default value_form from the numeric handler.
      parent::value_form($form[$key], $form_state);

      if ($this->options['expose']['show_value'] == 'select') {
        $options = array();
        foreach (explode(',', $this->options['expose']['value_options']) as $op) {
          $op = trim($op);
          $options[$op] = $op;
        }

        foreach (element_children($form[$key]) as $item) {
          $current = $form_state['input'][$key][$item];
          if (!isset($options[$current])) {
            $form_state['input'][$key][$item] = NULL;
          }
          $form[$key][$item] = array(
            '#type' => 'select',
            '#multiple' => FALSE,
            '#options' => $options,
            '#default_value' => isset($options[$current]) ? $current : NULL,
          );
          // TODO default value.
        }
      }
    }

    // Set units.
    if ($this->options['expose']['show_units']) {
      $form[$key]['units'] = array(
        '#type' => 'select',
        '#options' => geo_units(),
        '#default_value' => $this->value['units'],
      );
    }
    else {
      $form[$key]['units'] = array(
        '#type' => 'value',
        '#value' => $this->value['units'],
      );
    }

    // Set input.
    $element = geo_input_element_info($this->options['input']);
    $element['#default_value'] = $this->value['target'];

    $form[$key]['target'] = $element;

    $form[$key]['#attributes'] = array(
    );
  }

  function query() {

    // The GIS function we'll be filtering on.
    $function = $this->options['function'];
    $info = $this->geo->functionInfo($function);

    // Figure out whether or not we need a target value to compare against.
    if (FALSE === ($target = geo_views_set_target($this, $this->value['target']))) {
      // Return if target = FALSE to prevent an erroneous query.
      return;
    }

    $table = $this->ensure_my_table();
    $this->field_alias = $this->field .'_'. $function;

    // Ensure that the query acts on the table and column aliases defined here.
    $this->geo->setTableName($table);
    $this->geo->setColumnName($this->field);

    // Add the field, using the Geo API method for getting it.
    $query = $this->geo->$function($this->geo, $target);

    if ($info['returns'] == 'boolean') {
      $this->query->add_where(0, $query);
    }

    // Adopt the behavior of the views_filter_numeric parent class.
    if ($info['returns'] == 'float') {
   		// TODO Add a bounding box filter to leverage the geo index for performance

      // Convert the limiting values to meters.
      if ($units = $this->value['units']) {
        foreach (array('value', 'min', 'max') as $key) {
          $this->value[$key] = (int) geo_unit_convert($this->value[$key], $units, 'm');
        }
      }

      // Call the limiting function, just like the numeric handler would have.
      $info = $this->operators();
      if (!empty($info[$this->operator]['method'])) {
        $this->{$info[$this->operator]['method']}($query);
      }
    }
  }
}
