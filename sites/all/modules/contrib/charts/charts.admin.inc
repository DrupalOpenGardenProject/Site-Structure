<?php
// $Id: charts.admin.inc,v 1.6.4.1 2010/07/02 00:00:20 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Settings function for Charts module.
 */

/**
 * Subform that integartes Color module with Charts settings. Its called
 * inside the Charts settings page, by _charts_settings().
 *
 * @ingroup from
 */
function _charts_color_form_complete(&$form, $default) {
  // Use ColorPicker module if possible
  $field_type = module_exists('colorpicker') ? 'colorpicker_textfield' : 'textfield';

  $form['color'] = array(
    '#type'           => 'fieldset',
    '#title'          => t('Color'),
    '#tree'           => TRUE
  );
  $form['color']['color_palette'] = array(
    '#type'           => 'select',
    '#title'          => t('Color palettes'),
    '#options'        => $default['#color_palettes'],
    '#default_value'  => $default['#color_palette'],
  );
  $form['color']['background'] = array(
//     '#colorpicker'    => 'colorpicker',
    '#default_value'  => $default['#color']['background'],
    '#title'          => t('Background'),
    '#type'           => $field_type,
  );
  $form['color']['text'] = array(
    '#default_value'  => $default['#color']['text'],
    '#required'       => TRUE,
    '#title'          => t('Text'),
    '#type'           => $field_type,
  );
  for ($series = 0; $series < 8; $series++) {
    $form['color'][$series] = array(
      '#default_value'  => $default['#color'][$series],
      '#required'       => TRUE,
      '#title'          => t('Series %serie', array('%serie' => $series + 1)),
      '#type'           => $field_type,
    );
  }

  drupal_add_js(drupal_get_path('module', 'charts') .'/charts_color.js');
  drupal_add_js(array('chartsColorCustom' => t('Custom')), 'setting');
}

/**
 * Subform that use simple color inputs.
 *
 * @ingroup from
 */
function _charts_color_form_simple(&$form, $settings) {
  // Load some color palettes
  $form['color_palette'] = array(
    '#default_value'  => $settings['#color_palette'],
    '#options'        => $settings['#color_palettes'],
    '#required'       => TRUE,
    '#title'          => t('Color palettes'),
    '#type'           => 'select',
  );
}

/**
 * Generate a generic chart example
 *
 * @param $data
 *   Array (optional). Chart data, following the Charts Schema
 * @return
 *   HTML. The generic Chart example
 */
function _charts_example($type, $name) {
  $data = array(
    '#title'  => t('Testing Chart: !name', array('!name' => $name)),
    '#type'   => $type
  );

  // This will hold the example chart
  // Since the chart is an example, we should provide
  // and example data.
  $data[] = array(
    '#legend'     => 'Profit',
    array('#value' => 35, '#label' => t('Jan')),
    array('#value' => 25, '#label' => t('Feb')),
    array('#value' => 75, '#label' => t('Mar')),
    array('#value' => 50, '#label' => t('Apr')),
    array('#value' => 23, '#label' => t('May')),
    array('#value' => 12, '#label' => t('Jun')),
  );
  $data[] = array(
    '#legend'     => 'Revenue',
    10, 20, 55, 72, 45, 50
  );

  return charts_chart($data);
}

/**
 * Invoke a hook in all enabled modules that implement it.
 *
 * Its copy of module_invoke_all()
 * @see module_invoke_all()
 */
function _charts_module_invoke_all() {
  $args = func_get_args();
  $hook = $args[0];
  unset($args[0]);
  $return = array();
  foreach (module_implements($hook) as $module) {
    $function = $module .'_'. $hook;
    $result = call_user_func_array($function, $args);
    if (isset($result) && is_array($result)) {
      $return += $result;
    }
    elseif (isset($result)) {
      $return[] = $result;
    }
  }

  return $return;
}

/**
 * Module settings page. Users can set the default layout
 * of their charts.
 *
 * @ingroup form
 */
function _charts_settings_form(&$form, $default = array(), $options = array()) {
  module_load_include('inc', 'charts');
  $default = $default + _charts_settings();
  asort($default['#plugins']);
  asort($default['#types']);

  $options = array_fill_keys($options, TRUE);

  if (!empty($options['example'])) {
    foreach ($default['#types'] as $type => $name) {
        $form['chart_example'. $type] = array(
          '#value'          => _charts_example($type, $name),
        );
    }
  }

  $form['plugin'] = array(
    '#default_value'  => $default['#plugin'],
    '#options'        => $default['#plugins'],
    '#required'       => TRUE,
    '#type'           => 'select',
    '#title'          => t('Chart plugin'),
  );
  $form['type'] = array(
    '#default_value'  => $default['#type'],
    '#options'        => $default['#types'],
    '#required'       => TRUE,
    '#type'           => 'radios',
    '#title'          => t('Chart type'),
  );
  $form['size'] = array(
    '#description'    => t('The chart size, in pixels'),
    '#type'           => 'fieldset',
    '#title'          => t('Size'),
  );
  $form['size']['width'] = array(
    '#default_value'  => $default['#width'],
    '#required'       => TRUE,
    '#size'           => 8,
    '#type'           => 'textfield',
    '#title'          => t('Width'),
  );
  $form['size']['height'] = array(
    '#default_value'  => $default['#height'],
    '#required'       => TRUE,
    '#size'           => 8,
    '#type'           => 'textfield',
    '#title'          => t('Height'),
  );

  $form['label'] = array(
    '#default_value'  => $default['#label'],
    '#type'           => 'checkbox',
    '#title'          => t('Display value label'),
  );
  $form['legend'] = array(
    '#default_value'  => $default['#legend'],
    '#type'           => 'checkbox',
    '#title'          => t('Display series legend'),
  );


  if (empty($options['color_complete'])) {
    _charts_color_form_simple($form, $default);
  }
  else {
    _charts_color_form_complete($form, $default);
  }

  return $form;
}

/**
 * Module settings page. Users can set the default layout
 * of their charts.
 *
 * @ingroup form
 */
function _charts_settings_page() {
  $form = array();
  _charts_settings_form($form, array(), array('example', 'color_complete'));

  $form['submit'] = array(
    '#type'           => 'submit',
    '#value'          => t('Save settings'),
  );

  return $form;
}

/**
 * Module settings page. Users can set the default layout
 * of their charts.
 *
 * @ingroup form
 */
function _charts_settings_page_submit(&$form, &$form_state) {
  $settings = $form_state['values'];

  // Discart all form values non related to charts
  unset($settings['submit']);
  unset($settings['form_id']);
  unset($settings['form_build_id']);
  unset($settings['form_token']);
  unset($settings['op']);

  // Unwanted values
  unset($settings['color']['color_palette']);

  // Include a # sign in all attributes, because it will make the
  // merge between the chart data and the defaults easier on every
  // chart display.
  foreach ($settings as $index => $value) {
    $default['#'. $index] = $value;
  }

  // Save the data into database
  variable_set('charts_settings', $default);
}
