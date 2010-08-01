<?php
// $Id: charts.inc,v 1.31.2.3 2010/07/01 07:00:27 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * The real caller for building charts.
 */

// For everyone that does not use PHP 5.2 or newer
if (!function_exists('array_fill_keys')) {
  function array_fill_keys(array $keys, $value) {
    return array_combine($keys, array_fill(0, count($keys), $value));
  }
}

/**
 * The main Chart API function, that calls any chart provider
 * to print the given data.
 *
 * @param &$data
 *   Array. The chart data, described on chart_api.txt
 * @return
 *   String. The HTML with the propper chart (might include Flash or
 *   JavaScript external files)
 */
function _charts_chart(&$data) {
  // Get the previously saved data from database
  $settings = _charts_settings();

  // Check if the Chart will use the color palette for individual values
  // instead for series, like Pie charts
  $options = array('pie2D' => TRUE, 'pie3D' => TRUE);
  if ((!empty($data['#type']) and !empty($options[$data['#type']])) or !empty($options[$settings['#type']])) {
    $invert_attributes = TRUE;
  }

  // Merge deafult series attributes with data
  $number = -1;
  foreach (element_children($data) as $series) {
    ++$number;
    if (!is_numeric($series)) {
      $data[$number] = $data[$series];
      unset($data[$series]);
      $series = $number;
    }

    foreach (element_children($data[$series]) as $value) {
      if (!is_array($data[$series][$value])) {
        $data[$series][$value] = array(
          '#value' => $data[$series][$value]
        );
      }
      if (!empty($invert_attributes)) {
        _chart_series_attributes($data[$series][$value], $value, $settings);
      }
    }
    if (empty($invert_attributes)) {
      _chart_series_attributes($data[$series], $series, $settings);
    }
  }
  $data += $settings;

  if (!empty($data['#plugin'])
      and $chart_provider = module_invoke_all('charts_info')
      and isset($chart_provider[$data['#plugin']]['file'])
      and is_file($chart_provider[$data['#plugin']]['file'])
      and $func = $chart_provider[$data['#plugin']]['render']) {

    // Include the file that has the rendering function
    include_once $chart_provider[$data['#plugin']]['file'];

    // Using the filter's rendering function, print the chart
    return $func($data);
  }
  return '';
}

/**
 * Merge the default series attributes with the actual data.
 */
function _chart_series_attributes(&$data, &$value, &$settings) {
  foreach ($settings['#series_attributes'] as $attribute) {
    $data[$attribute] = $settings[$attribute][$value];
  }
}

/**
 * Even if the series have values with attributes,
 * return only the numeric values of them.
 *
 * @param
 *   Array. A given data series with or without attributes.
 * @return
 *   Array. A data series, but only with the values, without
 *   the attributes.
 */
function _charts_series_values($series) {
  $data = array();

  foreach ($series as $index => $value) {
    if (!is_numeric($index)) {
      continue;
    }

    if (is_array($value)) {
      $data[] = $value['#value'];
    }
    else {
      $data[] = $value;
    }
  }

  return $data;
}

/**
 * Module settings page. Users can set the default layout
 * of their charts.
 *
 * @ingroup form
 */
function _charts_settings() {
  // Get the previously saved data from Data Base
  static $default = array();

  if (empty($default)) {
    $default = variable_get('charts_settings', array());

    // Plugin
    $charts_info = module_invoke_all('charts_info', 'list');
    foreach ($charts_info as $chart_code => $chart) {
      $default['#plugins'][$chart_code] = $chart['name'];
    }
    asort($default['#plugins']);
    $default['#plugin'] = empty($default['#plugin']) ? current(array_keys($default['#plugins'])) : $default['#plugin'];

    // Type
    $default['#types'] = module_invoke_all('chart_types');
    $ctypes_allowed = array_fill_keys($charts_info[$default['#plugin']]['types'], TRUE);
    foreach (array_keys($default['#types']) as $ctype_code) {
      if (empty($ctypes_allowed[$ctype_code])) {
        unset($default['#types'][$ctype_code]);
      }
    }
    $default['#type']  = empty($default['#type']) ? current(array_keys($default['#types'])) : $default['#type'];

    // Width and Height
    $default['#width']  = empty($default['#width'])  ? 400 : $default['#width'];
    $default['#height'] = empty($default['#height']) ? 200 : $default['#height'];

    // Color Palette
    $default['#series_attributes'][] = '#color';
    $default['#color_palettes'] = _charts_settings_color_palette();
    if (empty($default['#color'])) {
      $default['#color_palette'] = current(array_keys($default['#color_palettes']));
      $default['#color'] = explode(',', $default['#color_palette']);
      $default['#color']['background'] = array_shift($default['#color']);
      $default['#color']['text'] = array_shift($default['#color']);
    }
    else {
      $color_palette = implode(',', $default['#color']);
      $default['#color_palette'] = isset($default['#color_palettes'][$color_palette]) ? $color_palette : '';
    }
  }

  return $default;
}

/**
 * List all preset color palette
 */
function _charts_settings_color_palette() {
  return array(
    '#ffffff,#000000,#ff0000,#00cc00,#0066b3,#ff8000,#ffcc00,#330099,#990099,#ccff00' => t('Primary'),
    '#ffffff,#000000,#ff6600,#009999,#1919b3,#ffb200,#ffff00,#660099,#e60066,#33ff00' => t('Secondary'),
    '' => t('Custom'),
  );
}
