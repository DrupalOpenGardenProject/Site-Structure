<?php
// $Id$

/**
 * @file
 *
 * Views integration code for Views Glossary Title module.
 */


/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function views_glossary_title_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'views_glossary_title'),
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

/**
 * Implementation of hook_views_data_alter().
 */
function views_glossary_title_views_data_alter(&$data) {
  $data['node']['title_alphabet'] = $data['node']['title'];
  $data['node']['title_alphabet']['real field'] = 'title';
  $data['node']['title_alphabet']['title'] = t('Node Title passed through filtering.');
  $data['node']['title_alphabet']['help'] = t('Field !field', array('!field' => 'Node Title'));
  $data['node']['title_alphabet']['field']['handler'] = 'views_handler_field_title_filter';
  $data['node']['title_alphabet']['argument']['handler'] = 'views_handler_argument_title_filter';
  $data['node']['title_alphabet']['field']['group'] = 'Views Alphabet Summary';
  return $data;
}
