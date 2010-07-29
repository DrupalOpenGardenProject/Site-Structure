<?php // $Id: postgis.inc,v 1.14 2009/12/03 00:43:43 vauxia Exp $

/**
 * Postgresql + PostGIS backend for the geo field module
 *
 * @author Mark Fredrickson
 * @version $Id: postgis.inc,v 1.14 2009/12/03 00:43:43 vauxia Exp $
 * @package geo
 */

/*** API Functions ***/

function geo_postgis_query_function($func, $field, $value, $srid) {
  $ret = array();
  $value = "ST_Transform(GeomFromText('$value', $srid), SRID($field))";

  // These relations should have overlapping bounding boxes, so use an index here.
  if (in_array($func, array('Equals', 'Within', 'Intersects'))) {
    $ret[] = "$value && $field";
  }

  $ret[] = "$func($value, $field)";
  return $ret;
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
function geo_postgis_tables($exclude = NULL) {
  static $tables;

  if (!is_array($tables)) {
    $tables = array();

    // Query for all available geometry columns.
    $res = db_query("SELECT c.relname AS table, a.attname AS field
      FROM pg_catalog.pg_attribute a
      LEFT JOIN pg_catalog.pg_class c ON a.attrelid = c.oid
      WHERE pg_catalog.format_type(a.atttypid, a.atttypmod) = 'geometry'
      AND  c.relname != 'geometry_dump'
      ORDER BY c.relname, a.attnum");

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
function geo_postgis_table_desc($table) {
  $res = db_query("SELECT  a.attname AS name,
    col_description(c.oid, a.attnum) AS description,
    format_type(a.atttypid, a.atttypmod) AS type,
    a.attnotnull AS not_null,
    d.adsrc AS default
    FROM pg_class c
    LEFT JOIN pg_attribute a ON (a.attrelid = c.oid)
    LEFT OUTER JOIN pg_attrdef d ON (d.adrelid = c.oid AND d.adnum = a.attnum)
    WHERE c.relname = '%s'
    AND a.attnum > 0
    AND NOT a.attisdropped
    AND a.attrelid = c.oid
    ORDER BY a.attnum", $table);

  $columns = array();
  $geo = array();
  while ($row = db_fetch_array($res)) {
    if ($row['type'] == 'geometry') {
      $geo[] = $row['name'];
    }

    $columns[$row['name']] = $row;
    $columns[$row['name']]['not_null'] = (bool) str_replace('f', '', $row['not_null']);
  }

  $res = db_query("SELECT c.relname AS table,
      pg_catalog.pg_get_constraintdef(r.oid, true) AS constraint
    FROM pg_catalog.pg_constraint r
    LEFT JOIN pg_catalog.pg_class c ON r.conrelid = c.oid
    WHERE c.relname = '%s' AND r.contype = 'c'", $table);

  /*
   Find constraints that are similar to the ones here, and set attributes

   CHECK (geometrytype(the_geom) = 'MULTIPOLYGON'::text OR the_geom IS NULL)
   CHECK (ndims(the_geom) = 2)
   CHECK (srid(the_geom) = 26915)
  */
  while ($row = db_fetch_object($res)) {
    $table = $row->table;
    foreach ($geo as $f) {
      if (strpos($row->constraint, "ndims($f)")) {
        $columns[$f]['dimensions'] = preg_replace('/\D/', '', $row->constraint);
      }
      elseif (strpos($row->constraint, "srid($f)")) {
        $columns[$f]['srid'] = preg_replace('/\D/', '', $row->constraint);
      }
      elseif (strpos($row->constraint, "geometrytype($f)")) {
        $columns[$f]['geometry_type'] = preg_replace('/.*\'(\w+)\'.*/', '$1', $row->constraint);
      }
    }
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
function geo_postgis_version() {
  return db_result(db_query("SELECT postgis_version()"));
}
