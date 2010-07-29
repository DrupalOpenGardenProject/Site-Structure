<?php // $Id: geo_ui.admin.inc,v 1.2 2009/12/02 19:51:05 vauxia Exp $

/**
 * Put together a form of all the spatial columns.
 */
function geo_ui_admin_list() {
  $hdrs = array(
    t('Name'),
    t('Table'),
    t('Records'),
    '',
  );

  $rows = array();
  foreach (geo_list() as $id => $geo) {
    $row = array();
    $row[] = $geo->title();
    $row[] = method_exists($geo, 'tableName') ? $geo->tableName() : '';
    $row[] = method_exists($geo, 'count') ? $geo->count() : '';
    $row[] = '';
    $rows[] = $row;
  }

  $output = theme('table', $hdrs, $rows);
  $output .= drupal_render($form);
  return $output;
}

function geo_ui_admin($form_state) {
  $form['#attributes']['enctype'] = 'multipart/form-data';

  $form['tables'] = array(
    '#type' => 'markup',
    '#value' => geo_ui_admin_list(),
  );

  $form['import'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import shapefile'),
    '#tree' => TRUE,
    '#description' => t('The shapefile must be a .zip file that includes, at a minimum, a .shp, .dbf and .shx file.'),
  );
  $form['import']['file'] = array(
    '#type' => 'file',
    '#title' => t('Shapefile'),
    //'#required' => TRUE,
  );
  $form['import']['table_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Table name'),
    '#description' => t('The name of the table to import the data into. This name must contain only lowercase letters, numbers, and underscores.'),
    '#required' => TRUE,
  );
  $form['import']['srid'] = array(
    '#type' => 'textfield',
    '#title' => t('SRID'),
    '#default_value' => GEO_SRID_DEFAULT,
    '#description' => t('The <a href="http://en.wikipedia.org/wiki/SRID">Spatial Reference IDentifier</a> that indicates the projection system of the shapefile to be imported.'),
    '#required' => TRUE,
  );
  $form['import']['create'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create a new table.'),
    '#default_value' => 1,
    '#description' => t('Check this box to import the shapefile into a new table.'),
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Import Shapefile'));
  return $form;
}

function geo_ui_admin_submit($form, &$form_state) {
  if (isset($_FILES['files']['name']['import'])) {
    module_load_include('inc', 'geo', 'includes/shp2sql');
    $file = $_FILES['files']['tmp_name']['import'];
    $table_name = 'geo_data_'. $form_state['values']['import']['table_name'];
    $create = $form_state['values']['import']['create'];
    $srid = $form_state['values']['import']['srid'];
    geo_shp2sql($file, $table_name, $create, $srid);
  }
}
