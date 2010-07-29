<?php // $Id: geo_sql_postgis.inc,v 1.4 2009/12/21 17:29:55 vauxia Exp $

class GeoSQLPostGIS extends GeoSQL {

  protected $geometry_columns_info;

  private function postgisGeometryColumnInfo() {
    if (!isset($this->$geometry_columns_info)) {
      $res = db_query("SELECT * FROM geometry_columns
        WHERE f_table_name = '{". $this->tableName() ."}'
        AND f_geometry_column = '%s'", $this->columnName());
      $this->geometry_columns_info = db_fetch_object($res);
    }
    return $this->geometry_columns_info;
  }

   /**
    * Return a list of columns that contain Geospatial information.
    *
    * @return array
    *  an array of fields
    */
  private function postgisColumnList() {
    static $columns;

    if (!is_array($columns)) {
      $tables = $columns = array();

      // Query for all available geometry columns.
      $res = db_query("SELECT s.nspname AS schema,
          c.relname AS table,
          a.attname AS column
        FROM pg_catalog.pg_attribute a
        INNER JOIN pg_catalog.pg_class c ON a.attrelid = c.oid
        INNER JOIN pg_catalog.pg_namespace s ON c.relnamespace = s.oid
        WHERE pg_catalog.format_type(a.atttypid, a.atttypmod) = 'geometry'
        AND  c.relname != 'geometry_dump'
        ORDER BY s.nspname, c.relname, a.attnum");

      while ($row = db_fetch_array($res)) {
        $table = $row['table'];
        $column = $row['column'];

        // Gather constraints on this table.
        if (!isset($tables[$table])) {
          $tables[$table] = array();

          $res2 = db_query("SELECT pg_catalog.pg_get_constraintdef(r.oid, true)
            FROM pg_catalog.pg_constraint r
            LEFT JOIN pg_catalog.pg_class c ON r.conrelid = c.oid
            WHERE c.relname = '%s' AND r.contype = 'c'", $table);
          while ($constraint = db_result($res2)) {
            $tables[$table][] = $constraint;
          }
        }

        foreach ($tables[$table] as $c) {
          // Dimension: "CHECK (ndims(the_geom) = 2)"
          if (strpos($c, "ndims($column)")) {
            $row['geo_dimension'] = preg_replace('/\D/', '', $c);
          }

          // GeometryType: CHECK (geometrytype(the_geom) = 'POINT'::text OR the_geom IS NULL)"
          elseif (strpos($c, "geometrytype($column)")) {
            $row['geometry_type'] = preg_replace('/.*\'(\w+)\'.*/', '$1', $c);
            $row['geo_type'] = constant('GEO_TYPE_'. $row['geometry_type']);
          }

          // SRID: "CHECK (srid(the_geom) = 26915)"
          elseif (strpos($c, "srid($column)")) {
            $row['srid'] = preg_replace('/\D/', '', $c);
          }
        }

        $columns[] = $row;
      }
    }
    return $columns;
  }

  public function setSRID($value = NULL) {
    if ($value && is_numeric($value)) {
      $this->srid = $value;
    }
    // Attempt to look up this value from the geometry_columns table.
    elseif ($info = $this->postgisGeometryColumnInfo()) {
      $this->srid = $info->srid;
    }
    // Attempt to retreive the the SRID from one of the data values.
    // note that this only works when the column has data.
    elseif (($table = $this->tableName()) && ($column = $this->columnName())) {
      $this->srid = db_result(db_query("SELECT SRID(%s)
        FROM {". $table ."} LIMIT 1", $column));
    }
  }

  public function setGeoType($value = NULL) {
    if (!is_null($value) && is_numeric($value)) {
      $this->geo_type = $value;
    }
    // Attempt to look up this value from the geometry_columns table.
    elseif ($info = $this->postgisGeometryColumnInfo()) {
      $type = $info->type;
    }
    // Attempt to retreive the the geo_type from one of the data values.
    // note that this only works when the column has data.
    elseif (($table = $this->tableName()) && ($column = $this->columnName())) {
      $type = db_result(db_query("SELECT GeometryType(%s)
        FROM {". $table ."} LIMIT 1", $column));
    }

    // Convert from a named type to Geo API's constant value.
    if (isset($type)) {
      $this->geo_type = constant('GEO_TYPE_'. $type);
    }
  }

  protected function addIndex() {
    if (!$this->indexed) return;

    $name = $this->tableName() .'__'. $this->columnName(). '_idx';
    if (strlen($name) > 6) {
      db_query("CREATE INDEX $name ON  {". $this->tableName() ."}
        USING gist(%s)", $this->columnName());
    }
  }

  protected function dropIndex() {
    if ($this->indexed) return;

    $name = $this->tableName() .'__'. $this->columnName(). '_idx';
    if (strlen($name) > 6) {
      db_query("CREATE SPATIAL INDEX $name ON  {". $this->tableName() ."}
        USING gist(%s)", $this->columnName());
    }
  }

  public function addPoint($g, $point, $position = NULL) {
    if ($position) {
      return $this->sql("ST_AddPoint(%g, %g, %d)", array($g, $point, $position));
    }
    else {
      return $this->sql("ST_AddPoint(%g, %g)", array($g, $point));
    }
  }

  public function point($x, $y) {
    return $this->sql("ST_MakePoint(%f, %f)", array($x, $y));
  }

  public function linestring() {
    // TODO see http://www.postgis.org/docs/ST_MakeLine.html and figure out
    // how to do this correctly.
    return $this->sql("ST_MakeLine(%g)", array($point));
  }

  public function polygon() {
    // TODO see http://www.postgis.org/docs/ST_MakePolygon.html and figure out
    // how to do this correctly.
    return $this->sql("ST_MakePolygon(%g)", array($linestring));
  }

  public function geomFromText($wkt, $srid = GEO_SRID_DEFAULT, $type = NULL) {
    return $this->sql("ST_GeomFromText('%s', %d)", array($wkt, $srid));
  }

  public function pointFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_PointFromText('%s', %d)", array($wkt, $srid));
  }

  public function lineFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_LineFromText('%s', %d)", array($wkt, $srid));
  }

  public function polyfromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_PolygonFromText('%s', %d)", array($wkt, $srid));
  }

  public function mPointFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_MPointFromText('%s', %d)", array($wkt, $srid));
  }

  public function mLineFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_MLineFromText('%s', %d)", array($wkt, $srid));
  }

  public function mPolyFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_MPolyFromText('%s', %d)", array($wkt, $srid));
  }

  public function geomCollFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_GeomCollFromText('%s', %d)", array($wkt, $srid));
  }

  public function bdPolyFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_BdPolyFromText('%s', %d)", array($wkt, $srid));
  }

  public function bdMPolyFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_BdMPolyFromText('%s', %d)", array($wkt, $srid));
  }

  public function geomFromWKB($wkb, $srid = GEO_SRID_DEFAULT, $type = NULL) {
    return $this->sql("ST_GeomFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function pointFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_PointFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function lineFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("ST_LineFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function polyFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
  }

  public function mPointFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
  }

  public function mLineFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
  }

  public function mPolyFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
  }

  public function geomCollFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
  }

  public function bdPolyFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
  }

  public function bdMPolyFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
  }

  public function asText($g) {
    return $this->sql("ST_AsText(%g)", array($g));
  }

  public function asBinary($g) {
    return $this->sql("ST_AsBinary(%g)", array($g));
  }

  public function dimension($g) {
    return $this->sql("ST_Dimension(%g)", array($g));

    // If the geometry is NULL, derive the dimension for this instance.
    $this->setDimension();
    return $this->geo_dimension;
  }

  public function geometryType($g = NULL) {
    return $this->sql("ST_GeometryType(%g)", array($g));

    // If the geometry is NULL, derive the SRID for this instance.
    $this->setGeoType();
    return GeoSimple::geometryType($this);
  }

  public function SRID($g = NULL) {
    return $this->sql("ST_SRID(%g)", array($g));

    // If the geometry is NULL, derive the SRID for this instance.
    $this->setSRID();
    return $this->srid;
  }

  public function isEmpty($g) {
    return $this->sql("ST_IsEmpty(%g)", array($g));
  }

  public function isSimple($g) {
    return $this->sql("ST_IsSimple(%g)", array($g));
  }

  public function boundary($g) {
    return $this->sql("ST_Boundary(%g)", array($g));
  }

  public function envelope($g) {
    return $this->sql("ST_Envelope(%g)", array($g));
  }

  public function x($g) {
    return $this->sql("ST_X(%g)", array($g));
  }

  public function y($g) {
    return $this->sql("ST_Y(%g)", array($g));
  }

  public function startPoint($g) {
    return $this->sql("ST_StartPoint(%g)", array($g));
  }

  public function endPoint($g) {
    return $this->sql("ST_EndPoint(%g)", array($g));
  }

  public function isClosed($g) {
    return $this->sql("ST_IsClosed(%g)", array($g));
  }

  public function isRing($g) {
    return $this->sql("ST_IsRing(%g)", array($g));
  }

  public function length($g) {
    return $this->sql("ST_Length(%g)", array($g));
  }

  public function numPoints($g) {
    return $this->sql("ST_NumPoints(%g)", array($g));
  }

  public function pointN($g, $n) {
    return $this->sql("ST_PointN(%g, %d)", array($g, $n));
  }

  public function centroid($g) {
    return $this->sql("ST_Centroid(%g)", array($g));
  }

  public function pointOnSurface($g) {
    return $this->sql("ST_PointOnSurface(%g)", array($g));
  }

  public function area($g) {
    return $this->sql("ST_Area(%g)", array($g));
  }

  public function exteriorRing($g) {
    return $this->sql("ST_ExteriorRing(%g)", array($g));
  }

  public function numInteriorRing($g) {
    return $this->sql("ST_NumInteriorRings(%g)", array($g));
  }

  public function interiorRingN($g, $n) {
    return $this->sql("ST_InteriorRingN(%g)", array($g, $n));
  }

  public function numGeometries($g) {
    return $this->sql("ST_NumGeometries(%g)", array($g));
  }

  public function geometryN($g, $n) {
    return $this->sql("ST_GeometryN(%g)", array($g, $n));
  }

  public function equals($g1, $g2) {
    return $this->sql("ST_Equals(%g, %g)", array($g1, $g2));
  }

  public function disjoint($g1, $g2) {
    return $this->sql("ST_Disjoint(%g, %g)", array($g1, $g2));
  }

  public function touches($g1, $g2) {
    return $this->sql("ST_Touches(%g, %g)", array($g1, $g2));
  }

  public function within($g1, $g2) {
    return $this->sql("ST_Within(%g, %g)", array($g1, $g2));
  }

  public function overlaps($g1, $g2) {
    return $this->sql("ST_Overlaps(%g, %g)", array($g1, $g2));
  }

  public function crosses($g1, $g2) {
    return $this->sql("ST_Crosses(%g, %g)", array($g1, $g2));
  }

  public function intersects($g1, $g2) {
    return $this->sql("ST_Intersects(%g, %g)", array($g1, $g2));
  }

  public function contains($g1, $g2) {
    return $this->sql("ST_Contains(%g, %g)", array($g1, $g2));
  }

  public function relate($g1, $g2, $pattern = NULL) {
    if ($pattern) {
      return $this->sql("ST_Relate(%g, %g, '%s')", array($g1, $g2, $pattern));
    }
    return $this->sql("ST_Relate(%g, %g)", array($g1, $g2));
  }

  public function distance($g1, $g2) {
    return $this->sql("ST_Distance_Sphere(%g, %g)", array($g1, $g2));
  }

  public function distanceSpheroid($g1, $g2) {
    return $this->sql("ST_Distance_Spheroid(%g, %g)", array($g1, $g2));
  }

  public function intersection($g1, $g2) {
    return $this->sql("ST_Intersection(%g, %g)", array($g1, $g2));
  }

  public function difference($g1, $g2) {
    return $this->sql("ST_Difference(%g, %g)", array($g1, $g2));
  }

  public function union($g1, $g2) {
    return $this->sql("ST_Union(%g, %g)", array($g1, $g2));
  }

  public function symDifference($g1, $g2) {
    return $this->sql("ST_SymDifference(%g, %g)", array($g1, $g2));
  }

  public function buffer($g1, $distance) {
    return $this->sql("ST_Buffer(%g, %d)", array($g1, $distance));
  }

  public function convexHull($g) {
    return $this->sql("ST_ConvexHull(%g)", array($g1));
  }
}
