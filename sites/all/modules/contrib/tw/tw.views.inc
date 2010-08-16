<?php
// $Id: tw.views.inc,v 1.1.2.17 2010/06/29 01:51:51 mikeryan Exp $

/**
 * @file
 * Views hooks
 */

require_once drupal_get_path('module', 'tw') . '/tw_tablebuild.inc';

/**
 * Implementation of hook_views_data().
 *
 * Utilizes shared table building functions to generate the full views data
 * array.
 */
function tw_views_data() {
  $tables = _tw_generate_views_table_data();
  $tables = _tw_generate_views_relationship_data($tables);
  drupal_alter('tw_views_data', $tables);
  return $tables;
}
