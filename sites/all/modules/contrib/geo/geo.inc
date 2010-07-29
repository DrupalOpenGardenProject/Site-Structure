<?php // $Id: geo.inc,v 1.18 2009/12/09 17:34:02 vauxia Exp $

/**
 * Return the geo backend database type.
 *
 * @return string
 *  The name of the backend: postgis, cck, mysql_spatial
 */
function geo_backend_type() {
  static $backend;

  if (!isset($backend)) {
    switch ($GLOBALS['db_type']) {
      case 'pgsql':
        // use the postgis backend if installed
        if (db_result(db_query("SELECT 1 FROM pg_catalog.pg_proc
          WHERE proname = 'postgis_version'"))) {
          $backend = 'postgis';
        }
        break;

      case 'mysql':
      case 'mysqli':
        // Capabilities check.
        // If it can convert between native and wkt, assume it's working.
        if (db_result(@db_query("SELECT AsText(GeomFromText('POINT(1 1)'))")) == 'POINT(1 1)') {
          $backend = 'mysql_spatial';
        }
    }
  }

  return $backend;
}

function geo_supported_types() {
  return array(
    'point' => t('Point'),
    'linestring' => t('Linestring'),
    'polygon' => t('Polygon'),
  );
}

// TODO seriously clean this up! And add data types!
function geo_wkt($data) {
  if (!is_scalar($data)) {
    $data = (object) $data;
    if (!isset($data->type)) $data->type = 'point';
    switch ($data->type) {
      case 'point':
        return 'POINT('. $data->lon .' '. $data->lat .')';
    }
  }
}

function geo_wkt_from_point($lat, $lon) {
  if (strlen($lat) || strlen($lon)) {
    return 'POINT('. $lon .' '. $lat .')';
  }
}

function geo_field_select($field) {
  if (!$field) return;
  $field = check_plain($field);
  $alias = str_replace('.', '_', $field);
  $alias = preg_replace('/_geo$/', '', $alias);

  return " SRID($field) as {$alias}_srid,
    AsBinary($field) AS {$alias}_wkb,
    AsBinary(Envelope($field)) AS {$alias}_bbox,
    AsBinary(Centroid($field)) AS {$alias}_centroid";
}

function geo_query_perimeter($field, $srid = null) {
  return 'Length(ConvexHull('. $field .')';
}

function geo_query_distance($field, $srid = null, $target) {
  $target = geo_wkt_from_point($target['lat'], $target['lon']);
  $query  = 'Distance('. $field .", GeomFromText('". $target ."', $srid))";
  return '('. GEO_DEGREE_M .' * '. $query .')';
}

function geo_schema_field($gis_type = 'geometry', $name = 'geo', $srid = NULL) {
  $types = geo_supported_types();
  $schema = array();
  if (isset($types[$gis_type])) {
    $schema[$name] = array(
      'type' => 'blob',
      'mysql_type' => 'geometry',
      'pgsql_type' => 'geometry',
      'gis type' => $gis_type,
      'description' => t('Geometry field'),
    );
  }
  return $schema;
}

function geo_make_bbox($target, $limit) {
  $x = $target['lon'];
  $y = $target['lat'];
  $offset_x = $limit / (GEO_DEGREE_M * cos($y));
  $offset_y = $limit / GEO_DEGREE_M;

  $offset_x = $limit / GEO_DEGREE_M; // TODO Miles
  $offset_y = $limit / round(GEO_DEGREE_M * cos($x / 92215));

  $bbox = array(
    'points' => array(
      array('lon' => $x - $offset_x, 'lat' => $y + $offset_y),
      array('lon' => $x + $offset_x, 'lat' => $y + $offset_y),
      array('lon' => $x + $offset_x, 'lat' => $y - $offset_y),
      array('lon' => $x - $offset_x, 'lat' => $y - $offset_y),
      array('lon' => $x - $offset_x, 'lat' => $y + $offset_y),
    ),
  );
  // TODO call a function?
  $wkt = '';
  foreach ($bbox['points'] as $p) $wkt .= $p['lon'] .' '. $p['lat'] .', ';
  $bbox['wkt'] = 'POLYGON(('. substr($wkt, 0, -2) .'))';
  return $bbox;
}

/**
 * Insert a geometry object into the database on the specified row
 *
 * @param $table
 *  The name of the table that currently holds the geometry information.
 * @param $field_name
 *  The name of the field in which to insert the data.
 * @return void
 */
function geo_geo_from_wkt($wkt, $srid = GEO_DEFAULT_SRID) {
  return " GeomFromText('". $wkt ."') ";
}

function geo_rss_item($wkb) {
  $data = geo_wkb_get_data($wkb, 'text');
  return array(
    'key' => 'georss:'. strtolower($data['type']),
    'value' => $data['value'],
    'namespace' => array('xmlns:georss' => 'http://www.georss.org/georss'),
  );
}

function geo_wkt_validate($wkt, $geo_type = NULL, $srid = GEO_SRID_DEFAULT) {

  // TODO this should probabaly be moved into db-specific backend files.
  $type = db_result(@db_query("SELECT GeometryType(GeomFromText('%s'))", $wkt));

  if (empty($type)) {
    return t('Unable to parse WKT.');
  }

  if ($geo_type && strtolower($geo_type) != strtolower($type)) {
    return t('Wrong geometry type. Got %result, was expecting %type.', array('%result' => $type, '%type' => $geo_type));
  }

  // All's well that ends well!
  return TRUE;
}
