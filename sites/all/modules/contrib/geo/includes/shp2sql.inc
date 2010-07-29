<?php // $Id: shp2sql.inc,v 1.3 2009/12/02 19:51:05 vauxia Exp $

/**
 * CREDITS
 * This shp and dbf parsing code is based on the following documentation:
 *   http://www.esri.com/library/whitepapers/pdfs/shapefile.pdf
 *   http://en.wikipedia.org/wiki/SHP_file
 *   http://www.phpdig.net/ref/rn45re878.html
 *   http://www.clicketyclick.dk/databases/xbase/format/dbf.html
 *
 * I also borrowed heavily from existing code by Juan Carlos Gonzalez Ulloa:
 *   http://sourceforge.net/projects/shp2mysql-php
 */
function geo_shp2sql($filename, $table_name = '', $create_table = TRUE, $srid = GEO_SRID_DEFAULT) {
  if (!$table_name) {
    $parts = pathinfo($filename);
    $table_name = $parts['filename'];
  }
  $table_name = preg_replace('/[^a-z0-9_]/', '', strtolower($table_name));

  if (!is_readable($filename) || (!is_resource($zip = zip_open($filename)))) {
    drupal_set_message(t('zip file nonexistant or unreadable.'), 'error');
    return FALSE;
  }

  // Catalog the contents of the zip file.
  $files = array();
  while ($res = zip_read($zip)) {
    $ext = strtolower(substr(strrchr(zip_entry_name($res), '.'), 1));
    $files[$ext] = $res;
  }

  // The zip file must minimally contain a shp, dbf and shx file.
  if (!isset($files['shp']) || !isset($files['dbf']) || !isset($files['shx'])) {
    drupal_set_message(t('This does not appear to be an archive that contains valid shp data.'), 'error');
    return FALSE;
  }

  // See if we can get the projection information from the prj file.
  if (isset($files['prj'])) {
    // TODO Parse srid from prj file, for conversion if necessary.
  }

  if (isset($files['dbt'])) {
    drupal_set_message(t('This database contains longtext/memo fields, which are unsupported.  Proceeding to enter other data anyway.'), 'warning');
  }

  // Get headers and table definition from the dbf file.
  $schema = array('description' => t('Geo data table'), 'fields' => array());
  $headers = _dbf_headers($files['dbf'], $schema);

  // Shape file headers are stored in the first 100 bytes of the shp/shx files.
  $headers += _shp_headers(zip_entry_read($files['shp'], 100));

  // Add the geo column that will contain shape data.
  $schema['fields'] = array_merge($schema['fields'], geo('schema_field', $headers['geo_type']));
  $schema['fields']['geo']['not null'] = TRUE;

  // Create a geo dataset.
  $name = preg_replace('/^geo_data_/', '', $table_name);
  $values = array(
    'name' => $name,
    'title' => ucwords(strtolower($name)),
    'table_name' => $table_name,
    'column_name' => 'geo',
    'geo_type' => geo_type($headers['geo_type']),
    'srid' => $srid,
    'indexed' => TRUE,
    'schema' => array($table_name => $schema),
  );
  $geo = geo_create_dataset($values);

  // TODO indexed, correctly deal with 'create_table' flag.

  $row_count = 0;
  while ($shp = _shp_get_record($files['shp'])) {
    $values = array();
    $dbf_data = zip_entry_read($files['dbf'], $headers['record_size']);
    $dbf_data = substr($dbf_data, 1); // Remove "record deleted" flag.
    foreach($headers['field_lengths'] as $name => $length) {
      $value = substr($dbf_data, 0, $length);
      $dbf_data = substr($dbf_data, $length);

      // Use a predefined function to filter and process each value.
      $process = $headers['field_filters'][$name];
      $values[$name] = $process($value);
    }

    // TODO NOT EFFICIENT
    $values['geo'] = db_result(db_query("SELECT GeomFromText('%s', %d)", $shp['data']['wkt'], $srid));

    drupal_write_record($table_name, $values);

    $row_count++;
  }

  drupal_set_message(t('Import complete. @count rows imported into @table', array('@count' => $row_count, '@table' => $table_name)));
}

function _shp_geo_types($key = null) {
  $geo_types = array(
    0 => 'none',
    1 => 'point',
    3 => 'linestring',  //TODO this is specified as 'polyline' in the standard.
    5 => 'polygon',
    8 => 'multipoint',
    11 => 'pointz',
    13 => 'polylinez',
    15 => 'polygonz',
    18 => 'multipointz',
    21 => 'pointm',
    23 => 'polylinem',
    25 => 'polygonm',
    28 => 'multipointm',
    31 => 'multipatch',
  );

  if ($key) return $geo_types[$key];
  return $geo_types;
}

function _dbf_headers(&$fp, &$schema) {

  // Crack open the dbf file for processing.
  $data = zip_entry_read($fp, 32);

  // Set basic headers.
  $headers = unpack('H2db_id/Cy/Cm/Cd/Lcount/Sheader_size/Srecord_size', $data);
  $date = $headers['m'] .'/'. $headers['d'] .'/'. $headers['y'] + 1900;
  $headers['date'] = strtotime($date);

  // Get the remainder of the dbf headers.
  $field_data = zip_entry_read($fp, $headers['header_size'] - 32);

  $type_map = array(
    'C' => 'char',
    'N' => 'int',
    'L' => 'int',
    'D' => 'date',
    'M' => 'text',
    'F' => 'float',
    'B' => 'blob',
    'Y' => 'decimal',
    'P' => 'blob',
    'I' => 'int',
    'Y' => 'decimal',
    'T' => 'datetime',
    'V' => 'varchar',
    'X' => 'varchar',
    '@' => 'timestamp',
    '0' => 'decimal',
    '+' => 'serial',
  );

  // Gather the column definitions from the field headers.
  $mask = 'A11name/Atype/x4/Clength/Cprecision';
  while (strlen($field_data) >= 32) {
    $d = unpack($mask, $field_data);
    $field_data = substr($field_data, 32);

    // Field name.
    $name = drupal_convert_to_utf8(strtolower(trim($d['name'])), 'ascii');
    $name = preg_replace('/[^a-z0-9_]/', '', $name);

    // Datatype.
    $type = isset($type_map[$d['type']]) ? $type_map[$d['type']] : 'varchar';
    if ($type == 'char' && $d['length'] > 3) $type = 'varchar';

    // Default data processing function, which will escape and UTF8 convert.
    $filter = '_shp_data_text';

    // Use all-purpose PHP functions for standard numeric types.
    if (in_array($type, array('float', 'decimal'))) $filter = 'floatval';
    if (in_array($type, array('int', 'timestamp', 'serial'))) $filter = 'intval';
    if ($type == 'date') $filter = '_shp_data_date';

    // Special case for boolean, convert to int.
    if ($d['type'] == 'L') $filter = '_shp_data_bool';

    $headers['field_filters'][$name] = $filter;

    // Datatype futzing.
    $schema['fields'][$name] = array('type' => $type, 'length' => $d['length']);
    if ($d['precision']) {
      $schema['fields'][$name]['not null'] = TRUE;
      $schema['fields'][$name]['default'] = 0.0;
    }

    // Remove precision from simple types.
    if (in_array($type, array('int', 'float', 'real', 'timestamp'))) {
      unset($schema['fields'][$name]['length']);
    }

    // Store field length for processing.
    $headers['field_lengths'][$name] = $d['length'];
  }

  unset($headers['y'], $headers['m'], $headers['d'], $headers['header_size']);
  return $headers;
}

function _shp_data_text($value) {
  return trim(drupal_convert_to_utf8($value, 'ascii'));
}

function _shp_data_bool($value) {
  return (int) in_array($value, array('t', 'T', 'y', 'Y'));
}

function _shp_data_date($value) {
  // Per the spec, we get the data in YYYYMMDD format.
  $y = (int) substr($value, 0, 4);
  $m = (int) substr($value, 4, 2);
  $d = (int) substr($value, 6, 2);
  return "$y-$m-$d";
}

function _shp_headers($data) {
  $mask = 'x28/iversion/igeo_type/dmin_x/dmax_x/dmin_y/dmax_y/dmin_z/dmax_z/dmin_m/dmax_m';
  $headers = unpack($mask, $data);
  $headers['geo_type'] = _shp_geo_types($headers['geo_type']);
  return $headers;
}

function _shp_get_record(&$fp) {
  if (!$row_header = zip_entry_read($fp, 12)) return FALSE;

  $row = unpack('Nnumber/Nlength/igeo_type', $row_header);
  $row['geo_type'] = _shp_geo_types($row['geo_type']);

  // Look for _shp_get_point(), _shp_get_linestring(), etc.
  if (!function_exists($func = '_shp_get_'. $row['geo_type'])) {
    drupal_set_message(t('Unsupported geo type %type found in file.', array('%type' =>  $row['geo_type'])), 'error');
    return FALSE;
  }

  $row['data'] = $func($fp);
  return $row;
}

function _shp_get_point_data(&$fp) {
  $data = unpack('dx/dy', zip_entry_read($fp, 16));
  return join(' ', $data);
}

function _shp_get_point(&$fp) {
  return 'POINT('. _shp_get_point_data($fp) .')';
}

function _shp_get_linestring(&$fp) {
  $data = array(
    'bbox'  => unpack('dmin_x/dmin_y/dmax_x/dmax_y', zip_entry_read($fp, 32)),
    'point_count' => current(unpack('i', zip_entry_read($fp, 4))),
  );

  $wkt = 'LINESTRING(';
  for ($i = 1; $i <= $data['point_count']; $i++) {
    $wkt .= _shp_get_point_data($fp) .',';
  }
  $wkt = substr($wkt, 0, -1) . ')';

  return $data;
}

function _shp_get_polygon(&$fp) {
  $data = array(
    'bbox'  => array(
      'min_x' => _shp_data_fetch('d', $fp),
      'min_y' => _shp_data_fetch('d', $fp),
      'max_x' => _shp_data_fetch('d', $fp),
      'max_y' => _shp_data_fetch('d', $fp),
    ),
    'part_count' => _shp_data_fetch('i', $fp),
    'point_count' => _shp_data_fetch('i', $fp),
  );

  $wkt = '';

  $points_counted = 0; $point_count; $last_offset = 0;
  $parts = array();
  for ($i = 0; $i < ($data['part_count']); $i++) {
    $parts[] = _shp_data_fetch('i', $fp);
  }

  $points_counted = 0;
  foreach ($parts as $i => $offset) {
    if ($next_offset = $parts[$i+1]) {
      $points_counted += $point_count = ($next_offset - $offset);
    }
    else {
      $point_count = $data['point_count'] - $points_counted;
    }

    if (!$point_count) continue;

    // Gather the point data for each part segment.
    $wkt .= '(';
    for ($j = 1; $j <= $point_count; $j++) {
      $wkt .= _shp_get_point_data($fp) .',';
    }
    $wkt = substr($wkt, 0, -1) . '),';
  }
  $data['wkt'] = 'POLYGON('. substr($wkt, 0, -1) .')';
  return $data;
}

function _shp_data_fetch($type, &$fp, $offset = null) {
  if (in_array($type, array('i', 'N'))) {
    $length = 4;
  }
  elseif (in_array($type, array('d' ))) {
    $length = 8;
  }
  if (is_string($fp)) {
    return current(unpack($type, substr($fp, $offset, $length)));
  }
  return current(unpack($type, zip_entry_read($fp, $length)));
}
