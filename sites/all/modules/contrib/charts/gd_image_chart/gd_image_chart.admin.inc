<?php
// $Id: gd_image_chart.admin.inc,v 1.1.2.1 2010/07/01 07:10:58 brmassa Exp $
/**
 * @author Mads Peter Henderson http://drupal.org/user/421971
 * @file
 * Settings function for gd_image_chart module.
 */

/**
 * Module settings page. Users can set the default filepath and setup cleaning instructions
 * of their gd image charts.
 *
 * @ingroup form
 */
function _gd_image_chart_settings_page() {
  $form = array();

  $form['path'] = array(
    '#default_value'  => variable_get('gd_image_chart_path', 'gd_image_chart'),
    '#description'    => t('The path to store temporary chart images in relativ to the site default file path (#defpath/)', array('#defpath' => file_directory_path())),
    '#required'       => TRUE,
    '#size'           => 50,
    '#type'           => 'textfield',
    '#title'          => t('Image path'),
  );

  $options['1']         = t('One second');
  $options['3600']      = t('One hour');
  $options['86400']     = t('24 hours');
  $options['604800']    = t('One week');
  $options['2592000']   = t('One month');
  $options['15768000']  = t('Six month');
  $options['-1'] = t('Keep forever (not recomended)');

  $form['keep_files'] = array(
    '#title' => t('Delete generated chart images after'),
    '#description'    => t('When cron runs all images in the image path will be deleted if they are older than the selected value'),
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => variable_get('gd_image_chart_keep_files', '86400'),
  );
  $form['submit'] = array(
    '#type'           => 'submit',
    '#value'          => t('Save settings'),
  );

  return $form;
}

/**
 * Module settings page. Users can set the default filepath and setup cleaning instructions
 * of their gd image charts.
 *
 * @ingroup form
 */
function _gd_image_chart_settings_page_validate(&$form, &$form_state) {
  $desired_path = check_plain($form_state['values']['path']);
  $final_path = file_directory_path() ."/". $desired_path;
  if (!file_check_directory($final_path, FILE_CREATE_DIRECTORY)) {
    form_set_error('path', '"'. $desired_path . t('" is not a valid file path. System must be able to write to #full_path', array('#full_path' => $final_path)));
  }
}

/**
 * Module settings page. Users can set the default filepath and setup cleaning instructions
 * of their gd image charts.
 *
 * @ingroup form
 */
function _gd_image_chart_settings_page_submit(&$form, &$form_state) {
  // Save the data into database
  variable_set('gd_image_chart_path', $form_state['values']['path']);
  variable_set('gd_image_chart_keep_files', $form_state['values']['keep_files']);
}
