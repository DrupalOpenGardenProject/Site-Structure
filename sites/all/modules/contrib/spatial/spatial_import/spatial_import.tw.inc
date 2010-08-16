<?php

/**
 * Implementation of hook_tw_form().
 *
 * Declare to Table Wizard that we have an upload / import form that it can use.
 */
function spatial_import_tw_form() {
  // Upload spatial files
  $fieldsets['shapefile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Upload spatial files'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'uploadhelp' => array(
      '#prefix' => '<div>',
      '#value' => t('Uploading a new file imports the contents of the file into a database table and
        adds it to the list above. Uploading a new copy of a previously-uploaded file replaces the
        file data - it should be reanalyzed before doing anything further. Note that any existing
        comments, ignored fields, and excluded rows are preserved when reloading the data.'),
      '#suffix' => '</div>',
    ),
    'file' => array(
      '#type' => 'file',
      '#title' => t('Upload shapefile'),
      '#size' => 48,
      '#description' => t('File containing the data to be imported. Should be a zipped shapefile.'),
    ),
    'tablename' => array(
      '#type' => 'textfield',
      '#title' => t('Table name'),
      '#size' => 64,
      '#maxlength' => 64,
      '#description' => t('Name of the database table to create from this file. If left blank,
        the uploaded filename (without its extension) will be used to name the table. For example,
        uploading <em>OldRecords.shp</em> will create the table <em>OldRecords</em>.')
    ),
    'spatial_field_name' => array(
      '#type' => 'textfield',
      '#title' => t('Spatial Data Column'),
      '#default_value' => 'geom',
      '#size' => 24,
      '#maxlength' => 24,
      '#description' => t('The database column name that the spatial data should be stored in.')
    ),
    'srid' => array(
      '#type' => 'textfield',
      '#title' => t('SRID (Spatial projection)'),
      '#default_value' => '4326',
      '#size' => 24,
      '#maxlength' => 24,
      '#description' => t('Integer represeting the SRID of the uploaded shapefile. If you are unsure, leave blank to use lat/lon (4326). ')
    ),
    'storage' => array(
      '#type' => 'select',
      '#title' => t('Database Storage'),
      '#options' => array(
        'wkt' => t('Well-Known-Text (Recommended)'),
        'geometry' => t('Spatial Database Geometries (WKB)'),
      ),
      '#description' => t('Storage of this data may be stored either as raw text (<a href="http://en.wikipedia.org/wiki/Well-known_text">WKT</a>), or as spatial database geometries.'),
      '#required' => TRUE,
    ),
    'spatialsubmit' => array(
      '#type' => 'submit',
      '#value' => t('Import shapefile'),
    ),
  );

  return $fieldsets;
}


/**
 * Implementation of hook_tw_form_submit().
 *
 * Process tw form data into a database table
 */
function spatial_import_tw_form_submit_shapefile($options) {
  $file = file_save_upload('shapefile');
  if ($file) {
    // Move the uploaded file to the tw_delimited directory
    $dest = _spatial_import_file_name($file->filename);
    if ($dest) {
      file_move($file, $dest, FILE_EXISTS_REPLACE);
    }
    else {
      drupal_set_message(t('Could not upload !filename', array('!filename' => $file->filename)));
      return;
    }

    // If an explicit table name was not provided...
    if ($options['tablename']) {
      $tablename = trim($options['tablename']);
    }
    else {
      // ... Derive one from the filename (minus extension)
      $pieces = explode('.', $file->filename);
      $tablename = trim($pieces[0]);
    }

    if (!$tablename) {
      drupal_set_message(t('Could not derive a table name for !filename', array('!filename' => $file->filename)));
      return;
    }

    // Set SRID -- @@TODO: grab this from the shapfile
    $srid = $options['srid'] ? $options['srid'] : '4326';

    // Lowercase table names make views integration much easier
    $tablename = drupal_strtolower(preg_replace('/[^a-z0-9]/i', '_', $tablename));

    // Truncate to 63 characters (valid for either MySQL or Postgres)
    $tablename = drupal_substr($tablename, 0, 63);

    // Actually crunch the data from the shapefile and get the results.
    $shapefile_data = spatial_import_process_shapefile($file->filepath, $options['spatial_field_name'], $options['storage']);

    // TODO: Option to append instead of replace (i.e., skip the TRUNCATE)
    if (db_table_exists($tablename)) {
      if ($options['tablename']) {
        db_query('DROP TABLE {' . $tablename . '}');
        drupal_set_message('Replacing existing table');
        db_create_table($ret, $tablename, $shapefile_data['schema']);
      }
      else {
         drupal_set_message('If you wish to replace an existing table, you must specify the table name explicitly','error');
         return;
      }
    }
    else {
      // Note that when using table prefixes, a prefix is prepended to the table name
      db_create_table($ret, $tablename, $shapefile_data['schema']);
    }
    
    // If we want to store things as geometries, then we should create a spatial index.
    // @@TODO: Add to 'spatial columns' in postGIS
    if ($options['storage'] == 'geometry') {
      $field = $options['spatial_field_name'];
      switch ($GLOBALS['db_type']) {
        case 'pgsql':
          db_query("CREATE INDEX {". $tablename ."}_". $field ."_idx ON {". $table ."} USING GIST ($field GIST_GEOMETRY_OPS)");
          break;
        case 'mysql':
        case 'mysqli':
          db_query("CREATE SPATIAL INDEX {$tablename}_${field}_idx ON  {". $tablename ."} ($field)");
          break;
      }
    }
    
    // Import the data into the database
    foreach ($shapefile_data['data'] as $row) {
      $values = array();
      foreach ($row as $key => $value) {
        // Add quotes, and other nessisary cleanup
        $callback = $shapefile_data['headers']['field_filters'][$shapefile_data['columns'][$key]];
        $values[] = $callback($value);
      }
      
      // We've already handled sanitization of tablename, column names and 
      // values, so we're going to skip the substitutions.
      db_query("INSERT INTO {$tablename} ( ". implode(', ', $shapefile_data['columns'] ) .") VALUES (". join(', ', $values) .")");
    }
    
    // Load the results into our list of spatial tables
    $spatial_import_tables = variable_get("spatial_import_tables", array());
    
    $spatial_import_tables[$tablename] = array (
      'table' => $tablename,
      'field' => $options['spatial_field_name'],
      'type' => $options['storage'],
      'module' => 'tw',
    );
    
    variable_set("spatial_import_tables", $spatial_import_tables);
    
    // Pass the table name back to Table Wizard
    return array($tablename);
    
  }
  else {
    drupal_set_message(t('Failed to upload spatial file'));
  }
}