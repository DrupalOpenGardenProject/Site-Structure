<?php
// $Id$

/**
 * @file
 *
 * Views integration code for Alphabet Summary Icons module.
 */

/**
 * Implementation of hook_views_plugins().
 */
function views_summary_alphabet_icons_views_plugins() {
  return array(
    'module' => 'views_summary_alphabet_icons',
    'style' => array(
      'alphabet_icons_summary' => array(
        'title' => t('Alphabet Summary'),
        'help' => t('Displays the summary with alphabet icons'),
        'handler' => 'views_plugin_style_views_summary_alphabet_icons',
        'path' => drupal_get_path('module', 'views_summary_alphabet_icons') . '/includes/views',
        'parent' => 'default_summary',
        'theme' => 'views_view_summary_alphabet_icons',
        'type' => 'summary', // only shows up as a summary style
        'uses options' => TRUE,
        'help topic' => 'style-summary-alphabet-icons',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function views_summary_alphabet_icons_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'views_summary_alphabet_icons') . '/includes/views',
    ),
    'handlers' => array(
      'views_handler_field_title_filter' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_argument_title_filter' => array(
        'parent' => 'views_handler_argument_string',
      ),
    ),
  );
}

function views_summary_alphabet_icons_views_data_alter(&$data) {
  $data['node']['title']['title'] = t('Node Title passed through filtering.');
  $data['node']['title']['help'] = t('Field !field', array('!field' => 'Node Title'));
  $data['node']['title']['field']['handler'] = 'views_handler_field_title_filter';
  $data['node']['title']['argument']['handler'] = 'views_handler_argument_title_filter';
  $data['node']['title']['field']['group'] = 'Views Alphabet Summary';
  return $data;
}
