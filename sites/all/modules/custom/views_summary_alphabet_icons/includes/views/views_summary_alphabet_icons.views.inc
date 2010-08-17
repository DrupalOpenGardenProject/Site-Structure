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
      'views_handler_argument_string_alphabet_icons' => array(
        'parent' => 'views_handler_argument_string',
      ),
    ),
  );
}