<?php
// $Id: flot.views.inc,v 1.1.2.3 2009/09/23 14:14:56 yhahn Exp $

/**
 * Implementation of hook_views_data_alter().
 */
function flot_views_data_alter(&$data) {
  $data['views']['datapoint'] = array(
    'title' => t('Data point'),
    'help' => t('Provide a datapoint suitable for a flot graph.'),
    'field' => array(
      'handler' => 'flot_handler_field_datapoint',
    ),
  );
}

/**
 * Implementation of hook_views_handlers().
 */
function flot_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'flot') . '/views',
    ),
    'handlers' => array(
      'flot_handler_field_datapoint' => array('parent' => 'views_handler_field'),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function flot_views_plugins() {
  return array(
    'style' => array(
      'flot' => array(
        'title' => t('Flot'),
        'help' => t('Displays the result set as a flot graph.'),
        'handler' => 'flot_views_plugin_style',
        'theme' => 'flot_views_style',
        'theme path' => drupal_get_path('module', 'flot') .'/views',
        'path' => drupal_get_path('module', 'flot') .'/views',
        'even empty' => TRUE,
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'flot_summary' => array(
        'parent' => 'flot',
        'title' => t('Flot'),
        'help' => t('Displays the default summary as a flot graph.'),
        'handler' => 'flot_views_plugin_summary_style',
        'path' => drupal_get_path('module', 'flot') .'/views',
        'theme' => 'flot_views_summary_style',
        'theme path' => drupal_get_path('module', 'flot') .'/views',
        'type' => 'summary', // only shows up as a summary style
        'uses options' => TRUE,
      ),
    ),
  );
}

/**
 * Preprocessor for theme_flot_views_summary_style().
 */
function template_preprocess_flot_views_summary_style(&$vars) {
  $options = $vars['view']->style_plugin->preprocess($vars);
}

/**
 * Preprocessor for theme_flot_views_style().
 */
function template_preprocess_flot_views_style(&$vars) {
  $options = $vars['view']->style_plugin->preprocess($vars);
}
