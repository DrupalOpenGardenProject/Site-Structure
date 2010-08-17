<?php
// $Id$
/**
 * @file
 * include the theme settings from theme
 */

/**
 * This is a shameless copy from the zen subtheme (starterkit) theme-settings
 * go grap the code and send john Albin a beer :)
 * drupal.org/project/zen
 */
include_once './' . drupal_get_path('theme', 'mothership') . '/theme-settings.php';


function SUBTHEME_settings($saved_settings) {
  // Get the default values from the .info file.
  $defaults = mothership_theme_get_default_settings('SUBTHEME');

  $settings = array_merge($defaults, $saved_settings);
  // Add the base theme's settings.
  $form = array();
  $form += mothership_settings($saved_settings, $defaults);

  // Return the form
  return $form;
}
