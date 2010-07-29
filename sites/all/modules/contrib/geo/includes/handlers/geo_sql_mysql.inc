<?php // $Id: geo_sql_mysql.inc,v 1.4 2009/12/09 17:34:02 vauxia Exp $

class GeoSQLMySQL extends GeoSQL {

  public function point($x, $y) {
    return $this->sql("Point(%f, %f)", array($x, $y));
  }

  private function mysqlExpandedInput($geometries, $function) {
    $args = $sql = array();
    foreach ($geometries as $g) {
      $sql[] = '%g';
      $args[] = $g;
    }

    return $this->sql($function ."(", join(', ', $sql) .")", $args);
  }

  public function setSRID($value = NULL) {
    if ($value && is_numeric($value)) {
      $this->srid = $value;
    }
    // Attempt to retreive the the SRID from one of the data values.
    // note that this only works when the column has data.
    elseif (($table = $this->tableName()) && ($column = $this->columnName())) {
      if ($srid = db_result(db_query("SELECT SRID(%s)
          FROM {". $table ."} LIMIT 1", $column))) {

        $this->srid = $srid;
      }
    }
  }

  public function setGeoType($value = NULL) {
    if (!is_null($value) && is_numeric($value)) {
      $this->geo_type = $value;
    }
    // Attempt to retreive the the geo_type from one of the data values.
    // note that this only works when the column has data.
    elseif (($table = $this->tableName()) && ($column = $this->columnName())) {
      $type = db_result(db_query("SELECT GeometryType(%s)
        FROM {". $table ."} LIMIT 1", $column));

      // MySQL returns a named type (POINT, POLYGON, etc.)  Convert it.
      if (defined('GEO_TYPE_'. $type)) {
        $this->geo_type = constant('GEO_TYPE_'. $type);
      }
    }
  }

  protected function addIndex() {
    if (!$this->indexed) return;

    $name = $this->tableName() .'__'. $this->columnName(). '_idx';
    if (strlen($name) > 6) {
      db_query("CREATE SPATIAL INDEX $name ON  {". $this->tableName() ."} (%s)", $this->columnName());
    }
  }

  protected function dropIndex() {
    if ($this->indexed) return;

    $name = $this->tableName() .'__'. $this->columnName(). '_idx';
    if (strlen($name) > 6) {
      db_query("DROP INDEX $name ON  {". $this->tableName() ."}");
    }
  }

  public function linestring() {
    $args = func_get_args();
    return $this->mysqlExpandedInput($args, 'Linestring');
  }

  public function polygon() {
    $args = func_get_args();
    return $this->mysqlExpandedInput($args, 'Polygon');
  }

  public function multiPoint() {
    $args = func_get_args();
    return $this->mysqlExpandedInput($args, 'MultiPoint');
  }

  public function multiLinestring() {
    $args = func_get_args();
    return $this->mysqlExpandedInput($args, 'MultiLinestring');
  }

  public function multiPolygon() {
    $args = func_get_args();
    return $this->mysqlExpandedInput($args, 'MultiPolygon');
  }

  public function geometryCollection() {
    return $this->unimplemented();
  }

  public function geomFromText($wkt, $srid = GEO_SRID_DEFAULT, $type = NULL) {
    return $this->sql("GeomFromText('%s', %d)", array($wkt, $srid));
  }

  public function pointFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("PointFromText('%s', %d)", array($wkt, $srid));
  }

  public function lineFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("LineFromText('%s', %d)", array($wkt, $srid));
  }

  public function polyFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("PolygonFromText('%s', %d)", array($wkt, $srid));
  }

  public function mPointFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("MPointFromText('%s', %d)", array($wkt, $srid));
  }

  public function mLineFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("MLineFromText('%s', %d)", array($wkt, $srid));
  }

  public function mPolyFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("MPolyFromText('%s', %d)", array($wkt, $srid));
  }

  public function geomCollFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("GeomCollFromText('%s', %d)", array($wkt, $srid));
  }

  public function geomFromWKB($wkb, $srid = GEO_SRID_DEFAULT, $type = NULL) {
    return $this->sql("GeomFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function pointFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("PointFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function lineFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("LineFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function polyFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("LineFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function mPointFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("MPointFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function mLineFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("MPointFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function mPolyFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("MPolyFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function geomCollFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->sql("GeomCollFromWKB(%b, %d)", array($wkb, $srid));
  }

  public function asText($g) {
    return $this->sql("AsText(%g)", array($g));
  }

  public function asBinary($g) {
    return $this->sql("AsBinary(%g)", array($g));
  }

  public function dimension($g) {
    if ($g) return $this->sql("Dimension(%g)", array($g));
    return $this->geo_dimension;
  }

  public function geometryType($g = NULL) {
    if ($g) return $this->sql("GeometryType(%g)", array($g));

    // If the geometry is NULL, derive the geometrytype for this instance.
    $this->setGeoType();
    $types = GeoSimple::geometryTypes();
    return $types[$this->geo_type];
  }

  public function SRID($g = NULL) {
    if ($g) return $this->sql("SRID(%g)", array($g));

    // If the geometry is NULL, derive the SRID for this instance.
    $this->setSRID();
    return $this->srid;
  }

  public function envelope($g) {
    return $this->sql("Envelope(%g)", array($g));
  }

  public function x($g) {
    return $this->sql("X(%g)", array($g));
  }

  public function y($g) {
    return $this->sql("Y(%g)", array($g));
  }

  public function startPoint($g) {
    return $this->sql("StartPoint(%g)", array($g));
  }

  public function endPoint($g) {
    return $this->sql("EndPoint(%g)", array($g));
  }

  public function isClosed($g) {
    return $this->sql("IsClosed(%g)", array($g));
  }

  public function length($g) {
    return $this->sql("GLength(%g)", array($g));
  }

  public function numPoints($g) {
    return $this->sql("NumPoints(%g)", array($g));
  }

  public function pointN($g, $n) {
    return $this->sql("PointN(%g, %d)", array($g, $n));
  }

  public function centroid($g) {
    return $this->sql("Centroid(%g)", array($g));
  }

  public function area($g) {
    return $this->sql("Area(%g)", array($g));
  }

  public function exteriorRing($g) {
    return $this->sql("ExteriorRing(%g)", array($g));
  }

  public function numInteriorRing($g) {
    return $this->sql("NumInteriorRings(%g)", array($g));
  }

  public function interiorRingN($g, $n) {
    return $this->sql("InteriorRingN(%g)", array($g, $n));
  }

  public function numGeometries($g) {
    return $this->sql("NumGeometries(%g)", array($g));
  }

  public function geometryN($g, $n) {
    return $this->sql("GeometryN(%g)", array($g, $n));
  }

  public function equals($g1, $g2) {
    return $this->sql("MBREqual(%g, %g)", array($g1, $g2));
  }

  public function disjoint($g1, $g2) {
    return $this->sql("MBRDisjoint(%g, %g)", array($g1, $g2));
  }

  public function touches($g1, $g2) {
    return $this->sql("MBRTouches(%g, %g)", array($g1, $g2));
  }

  public function within($g1, $g2) {
    return $this->sql("MBRWithin(%g, %g)", array($g1, $g2));
  }

  public function overlaps($g1, $g2) {
    return $this->sql("MBROverlaps(%g, %g)", array($g1, $g2));
  }

  public function crosses($g1, $g2) {
    return $this->sql("Crosses(%g, %g)", array($g1, $g2));
  }

  public function intersects($g1, $g2) {
    return $this->sql("MBRIntersects(%g, %g)", array($g1, $g2));
  }

  public function contains($g1, $g2) {
    return $this->sql("MBRContains(%g, %g)", array($g1, $g2));
  }

  /**
   * MySQL has no native support for the extent function.
   * Construct one manually.
   */
  public function extent($g) {
    // TODO this is incorrect!  It's returning coordinates rather than an
    // actual geometry (box)
    return $this->sql("MIN(X(PointN(ExteriorRing(Envelope(%g)), 1))) AS minx,
      MAX(X(PointN(ExteriorRing(Envelope(%g)), 3))) AS maxx,
      MIN(Y(PointN(ExteriorRing(Envelope(%g)), 1))) AS miny,
      MAX(Y(PointN(ExteriorRing(Envelope(%g)), 3))) AS maxy",
      array($g, $g, $g, $g));
  }

  /**
   * MySQL has no native support for distance calculations between geometries
   * Approximate this using the Pythagorean function.
   *
   * NOTE: As we can only support points, the distance measured will be from
   * Centroid to centroid.  This means that geometries such as Polygons and
   * Linestrings will have an artificially-high distance result.
   *
   * Imagine two 10x10 squares that are adjacent to each other.  In reality,
   * The distance between these objects is 0.  But this calculation would
   * return 10. (radius of 5 + radius of 5)
   *
   * Still, it's better than nothing.
   */
  public function distance($g1, $g2) {
    // Convert $g2 to a point and get its x and y coordinates.
    list($x, $y) = array_values(db_fetch_array(db_query("SELECT ".
      $this->sql("X(%g), Y(%g)", array($g2, $g2)))));

    // Perhaps it wasn't a point.  Try with a centroid.
    if (!$x && !$y) {
      list ($x, $y) = array_values(db_fetch_array(db_query("SELECT ".
        $this->sql("X(Centroid(%g)), Y(Centroid(%g))", array($g2, $g2)))));
    }

    // Offsets, in meters.
    $mod_x = GEO_DEGREE_M * cos($y / 57.2958);
    $mod_y = GEO_DEGREE_M;

    $g = ($g1->geoType() == GEO_TYPE_POINT ) ? '%g' : 'Centroid(%g)';

    // Let MySQL take it from here with the pythagorean function.
    $sql = "SQRT(POW(($mod_x * (X($g) - $x)), 2)
      + POW(($mod_y * (Y($g) - $y)), 2))";

    return $this->sql($sql, array($g1, $g1));
  }

  /**
   * Calculate distance using the Great Circle Distance Formula.
   * This is more accurate than the distance() function over large distances,
   * but less efficient.
   *
   * NOTE: As we can only support points, the distance measured will be from
   * Centroid to centroid.  This means that geometries such as Polygons and
   * Linestrings will have an artificially-high distance result.
   */
  public function distanceSpheroid($g1, $g2) {
    // Convert $g2 to a point and get its x and y coordinates.
    list($x, $y) = array_values(db_fetch_array(db_query("SELECT ".
      $this->sql("X(%g), Y(%g)", array($g2, $g2)))));

    // Perhaps it wasn't a point.  Try with a centroid.
    if (!$x && !$y) {
      list ($x, $y) = array_values(db_fetch_array(db_query("SELECT ".
        $this->sql("X(Centroid(%g)), Y(Centroid(%g))", array($g2, $g2)))));
    }

    // Radius of the earth in meters.
    $r = 6370986;

    // Degree offset.
    $d = 57.2958;

    // Offsets, in meters.
    $ysin = sin($y / $d);
    $ycos = cos($y / $d);
    $xd   = $x/$d;

    $g = ($g1->geoType() == GEO_TYPE_POINT ) ? '%g' : 'Centroid(%g)';

    $sql = "($r * ACOS($ysin * SIN(Y($g)/$d) + $ycos
      * COS(Y($g)/$d)
      * COS(X($g)/$d - $xd)))";

    return $this->sql($sql, array($g1, $g1, $g1));
  }
}
