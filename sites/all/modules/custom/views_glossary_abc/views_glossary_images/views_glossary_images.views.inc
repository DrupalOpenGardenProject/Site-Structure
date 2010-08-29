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
function views_glossary_images_views_plugins() {
  return array(
    'module' => 'views_glossary_images',
    'style' => array(
      'alphabet_icons_summary' => array(
        'title' => t('Alphabet Summary'),
        'help' => t('Displays the summary with alphabet icons'),
        'handler' => 'views_plugin_style_views_glossary_images',
        'path' => drupal_get_path('module', 'views_glossary_images'),
        'parent' => 'default_summary',
        'theme' => 'views_view_glossary_images',
        'type' => 'summary', // only shows up as a summary style
        'uses options' => TRUE,
        'help topic' => 'style-summary-glossary-images',
      ),
    ),
  );
}
