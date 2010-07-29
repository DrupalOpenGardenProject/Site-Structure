<?php // $Id: mysql_spatial.inc,v 1.15 2009/12/09 17:34:02 vauxia Exp $

/**
 * @file
 * MySQL Spatial Extensions backend for the geo field module
 *
 * @package geo
 */

/*** API Functions ***/

function geo_mysql_spatial_query_function($func, $field, $value, $srid) {
  return array("$func(GeomFromText('$value', $srid), $field)");
}

/*** Helper functions ***/

/**
 * Return a list of fields, keyed by table, of geo tables.
 *
 * @param $table
 *  an optional string of the table name to look in
 *
 * @return array
 *  an array of fields, keyed by table
 */
function geo_mysql_spatial_tables($exclude = NULL) {
  static $tables;

  if (!is_array($tables)) {
    $tables = array();

    // Query for all available geometry columns.
    // @@@ Mysql5 + only.
    $res = db_query("SELECT TABLE_NAME AS 'table', COLUMN_NAME AS 'field'
      FROM information_schema.columns
      WHERE TABLE_SCHEMA = database()
      AND DATA_TYPE IN ('GEOMETRY','POINT','LINESTRING','POLYGON','MULTIPOINT',
      'MULTILINESTRING','MULTIPOLYGON','GEOMETRYCOLLECTION')
      ORDER BY TABLE_NAME, COLUMN_NAME");

    while ($row = db_fetch_object($res)) {
      // Ignore exclusions.
      if ($exclude && preg_match($exclude, $row->table)) continue;

      if (!isset($tables[$row->table])) {
        $tables[$row->table] = array();
      }
      $tables[$row->table][] = $row->field;
    }
  }
  return $tables;
}

/**
 * Parse out the table descriptions from the geometry information stored in the table.
 */
function geo_mysql_spatial_table_desc($table) {
  $res = db_query("SELECT COLUMN_NAME AS 'name',
    COLUMN_COMMENT AS 'description',
    DATA_TYPE AS 'type',
    IS_NULLABLE AS 'null_ok',
    COLUMN_DEFAULT AS 'default'
    FROM information_schema.columns
    WHERE TABLE_SCHEMA = database()
    AND TABLE_NAME = '%s' ORDER BY ORDINAL_POSITION", $table);

  $columns = array();
  $geo = array();
  while ($row = db_fetch_array($res)) {
    if ($row['type'] == 'geometry') {
      $geo[] = $row['name'];
    }

    $columns[$row['name']] = $row;
    $columns[$row['name']]['not_null'] = $row['null_ok']=='YES' ? FALSE : TRUE;
    unset($columns[$row['name']]['null_ok']);
  }
  return $columns;
}

// provide a quick way to get the SRID of a column and use it in the storage
function _geo_fromtext($string, $table, $field) {
  $srid = db_result(db_query("SELECT srid FROM {gis_sources}
    WHERE table = '%s' AND field = '%s'"));

  return "GeomFromText('$string', $srid)";
}

// Point to latlon
function _geo_latlonfrompoint($wkt, $srid = GEO_SRID_DEFAULT) {
  // Yep. Not efficient.
  return array(
    'lat' => db_result(db_query("SELECT X(GeomFromText('%s', %d))", $wkt, $srid)),
    'lon' => db_result(db_query("SELECT Y(GeomFromText('%s', %d))", $wkt, $srid)),
  );
}

// returns the PostGIS version information
function geo_mysql_spatial_version() {
  // No clue what to do here...
  // return db_result(db_query("SELECT postgis_version()"));
}
