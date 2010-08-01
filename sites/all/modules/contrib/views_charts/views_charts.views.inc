<?php
// $Id: views_charts.views.inc,v 1.1.2.1 2010/07/08 13:50:32 rsevero Exp $

/**
 * @file
 * Holds methods directly related to the Views module.
 */


function views_charts_views_plugins() {
  $plugins = array();

  $plugins['style'] = array('charts' => array(
      'title' => t('Charts'),
      'help' => t('Displays rows in a chart.'),
      'handler' => 'views_plugin_style_chart',
      'path' => drupal_get_path('module', 'views_charts'),
      'uses row plugin' => TRUE,
      'uses options' => TRUE,
      'uses fields' => TRUE,
      'type' => 'normal',
    ),
  );

  return $plugins;
}
