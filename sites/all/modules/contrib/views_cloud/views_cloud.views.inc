<?php

function views_cloud_views_plugins() {
  return array(
    'style' => array(
      'cloud_summary' => array(
        'title' => t('Cloud'),
        'help' => t('Displays the default summary as a cloud of links.'),
        'handler' => 'views_cloud_plugin_summary_style_cloud',
        'parent' => 'default_summary',
        'theme' => 'views_cloud_summary_style',
        'type' => 'summary', // only shows up as a summary style
        'uses options' => TRUE,
      ),
      'cloud' => array(
        'title' => t('Cloud'),
        'help' => t('Displays the views data as a cloud of items.'),
        'handler' => 'views_cloud_plugin_style_cloud',
        'theme' => 'views_cloud_style',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    )
  );
}
