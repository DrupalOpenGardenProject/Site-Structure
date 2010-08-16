<?php

/**
 * Speicifc Layer Callback for Imported Spatial Layers
 *
 * This function handles the speicifc layer handling
 * of layers enabled for Sptial Import module
 *
 * @param $layer
 *   name of layer passed by rendering
 * @return
 *   Layer data
 */
function spatial_table_process_layers($layername = NULL) {
  $layers = spatial_table_openlayers_layers_info();
  
  $layer = $layers[$layername];
  $table = $layer['data']['spatial_table'];
  $title = $layer['data']['title'];
  $field = $layer['data']['field_geometry'];
  $fid = $layer['data']['field_fid'];
  $attributes = $layer['data']['field_attributes'];
  
  if ($attributes) {
    $attributes_sql = ','.implode(', ', $attributes);
  }
  
  // Get geometry text
  if ($layer['data']['field_type'] == 'text') {
    $query = "SELECT $field as field_geometry ".$attributes_sql." from {$table}"; 
  }
  else {
  	$query = "SELECT asText($field) as field_geometry ".$attributes_sql." from {$table}"; 
  }
  $res = db_query($query);
  $features = array();

  // Go through results
  while ($row = db_fetch_array($res)) {
    $attributes = array();
    foreach (array_keys($row) as $attr_name) {
      if ($attr_name != 'field_geometry') { 
        $attr_val = $row[$attr_name];
        $attributes[$attr_name] = $attr_val;
      }
    }
    // Put together features
    $features[] = array(
      'wkt' => $row['field_geometry'],
      'attributes' => $attributes,
      'projection' => '4326', //@@TODO: This needs to be fixed. 
    );
  }

  // Create layer data array
  $layer_data = array(
    'id' => $layer,
    'type' => 'Vector',
    'name' => $title,
    'features' => $features,
  );
  return $layer_data;
}