<?php // $Id: geo_ui.theme.inc,v 1.1 2009/12/01 21:49:48 vauxia Exp $

/**
 * Implementation of hook_theme().
 */
function geo_ui_theme_theme() {
  $path = drupal_get_path('module', 'geo_ui') .'/theme';

  return array(
    'geo_ui_admin_tables' => array(
      'arguments' => array('form' => NULL),
      'file' => 'geo_ui.theme.inc',
      'path' => $path,
    ),
  );
}

/**
 * Theme function for the geo_data table listing.
 */
function theme_geo_ui_admin_tables($form) {
  $hdrs = array(
    t('Name'),
    t('Table'),
    t('Records'),
    '',
  );

  $rows = array();
  foreach (element_children($form['tables']) as $k => $table) {
    $row = array();
    $row[] = drupal_render($form['tables'][$k]['label']);
    $row[] = drupal_render($form['tables'][$k]['count']);
    $row[] = drupal_render($form['tables'][$k]);
    $rows[] = $row;
  }

  $output = theme('table', $hdrs, $rows);
  $output .= drupal_render($form);

  return $output;
}
