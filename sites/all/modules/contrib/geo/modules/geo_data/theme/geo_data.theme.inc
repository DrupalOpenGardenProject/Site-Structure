<?php // $Id: geo_data.theme.inc,v 1.2 2009/12/01 21:49:48 vauxia Exp $

/**
 * Implementation of hook_theme().
 */
function geo_data_theme_theme() {
  $path = drupal_get_path('module', 'geo_data') .'/theme';

  return array(
    'geo_data_formatter_default' => array(
      'arguments' => array('element' => NULL),
      'file' => 'geo_data.theme.inc',
      'path' => $path,
    ),
    'geo_data_formatter_key' => array(
      'arguments' => array('element' => NULL),
      'file' => 'geo_data.theme.inc',
      'path' => $path,
    ),
    'geo_data_select' => array(
      'arguments' => array('element' => NULL),
      'file' => 'geo_data.theme.inc',
      'path' => $path,
    ),
  );
}

/**
 * Default field theme function: return value field.
 */
function theme_geo_data_formatter_default($element) {
  return check_plain($element['#item']['label']);
}

/**
 * Default field theme function: return key field.
 */
function theme_geo_data_formatter_key($element) {
  return check_plain($element['#item']['value']);
}

/**
 * Theme function for the geo_data select element.
 */
function theme_geo_data_select($element) {
  return $element['#children'];
}
