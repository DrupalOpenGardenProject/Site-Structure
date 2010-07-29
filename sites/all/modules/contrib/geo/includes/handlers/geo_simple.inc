<?php // $Id: geo_simple.inc,v 1.5 2009/12/21 17:29:55 vauxia Exp $

/**
 * @file
 * A simple implementation of the Geo API.
 *
 * This file contains a backend-agnostic PHP implementation of OGC's GIS
 * Specification.
 * It includes Basic parsing functions, constructors and other
 * calculations that are easy or necessary to handle in PHP, but a majority
 * of functions will remain unimplemented and left for other backends to handle.
 */

class GeoSimple implements GeoInterface {

  protected $gid;
  protected $name;
  protected $title;
  protected $srid = GEO_UNKNOWN;
  protected $geo_type;

  public function geometryTypes() {
    return array(
      GEO_TYPE_POINT => 'point',
      GEO_TYPE_CURVE => 'curve',
      GEO_TYPE_LINESTRING => 'linestring',
      GEO_TYPE_SURFACE => 'surface',
      GEO_TYPE_POLYGON => 'polygon',
      GEO_TYPE_COLLECTION => 'collection',
      GEO_TYPE_MULTIPOINT => 'multipoint',
      GEO_TYPE_MULTICURVE => 'multicurve',
      GEO_TYPE_MULTILINESTRING => 'multilinestring',
      GEO_TYPE_MULTISURFACE => 'multisurface',
      GEO_TYPE_MULTIPOLYGON => 'multipolygon',
    );
  }

  function geoCompatible($g) {
    return (get_class($g) == get_class($this));
  }

  private function unimplemented() {
    drupal_set_message(t('Attempt to call an unimplemented function'));
    return FALSE;
  }

  public function point($x, $y) {
    return new GeometryPoint($x, $y);
  }

  public function linestring() {
    $g = New GeometryLinestring();
    $g->handler = $this;
    $geometries = func_get_args();
    foreach ($geometries as $point) {
      $g->addPoint($point);
    }
    return $g;
  }

  public function polygon() {
    $g = New GeometryPolygon();
    $g->handler = $this;
    $geometries = func_get_args();
    foreach ($geometries as $linestring) {
      $g->addLine($point); // TODO This won't exist.
    }
    return $g;
  }

  public function multiPoint() {
    $g = New GeometryLinestring();
    $g->handler = $this;
    $geometries = func_get_args();
    foreach ($geometries as $point) {
      $g->addPoint($point); // TODO This won't exist.
    }
    return $g;
  }

  public function multiLinestring() {
    $g = New GeometryLinestring();
    $g->handler = $this;
    $geometries = func_get_args();
    foreach ($geometries as $linestring) {
      $g->addLinestring($point); // TODO This won't exist.
    }
    return $g;
  }

  public function multiPolygon() {
    $g = New GeometryLinestring();
    $g->handler = $this;
    $geometries = func_get_args();
    foreach ($geometries as $polygon) {
      $g->addPolygon($polygon); // TODO This won't exist.
    }
    return $g;
  }

  public function geometryCollection() {
    $g = New GeometryLinestring();
    $g->handler = $this;
    $geometries = func_get_args();
    foreach ($geometries as $geom) {
      $g->addGeometry($geom); // TODO This won't exist.
    }
    return $g;
  }

  // Implementation-specfic functions.
  public function addPoint($g, $point, $position = NULL) {
    if (isset($g->points)) {
      $g->points[] = $point;
    }
  }

  public function geomFromText($wkt, $srid = GEO_SRID_DEFAULT, $type = NULL) {
    // TODO NEED THIS
    return $this->unimplemented();
  }

  public function pointFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function lineFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function polyfromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function mPointFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function mLineFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function mPolyFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function geomCollFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function bdPolyFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function bdMPolyFromText($wkt, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromText($wkt, $srid);
  }

  public function geomFromWKB($wkb, $srid = GEO_SRID_DEFAULT, $type = NULL) {
    // TODO NEED THIS
    return $this->unimplemented();
  }

  public function pointFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
  }

  public function lineFromWKB($wkb, $srid = GEO_SRID_DEFAULT) {
    return $this->geomFromWKB($wkb, $srid);
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
    if (isset($g->wkt)) return $g->wkt;
    // TODO make the WKT
    switch (GeoSimple::geometryType($g)) {
      case 'point':
    }
    return $this->unimplemented();
  }

  public function asBinary($g) {
    if (isset($g->wkb)) return $g->wkb;
    // TODO make the WKB

    return $this->unimplemented();
  }

  public function dimension($g) {
    return $this->unimplemented();
  }

  public function geometryType($g = NULL) {
    $types = GeoSimple::geometryTypes();
    return $types[$g->geoType()];
  }

  public function SRID($g = NULL) {
    if (isset($g->srid)) return $g->srid;
    return GEO_UNKNOWN;
  }

  public function isEmpty($g) {
    switch ($this->geometryType($g)) {

      case 'point':
        return (int) ($g->x() == NULL || $g->y() == NULL);

      case 'curve':
      case 'linestring':
        return (int) (count($g->points) == 0);

      case 'surface':
      case 'polygon':
        return (int) (count($g->rings) == 0); // TODO

      case 'collection':
      case 'multipoint':
      case 'multicurve':
      case 'multilinestring':
      case 'multisurface':
      case 'multipolygon':
        return (int) (count($g->geometries) == 0); // TODO

      default:
        return GEO_UNKNOWN;
    }
  }

  public function isSimple($g) {
    return $this->unimplemented();
  }

  public function boundary($g) {
    return $this->unimplemented();
  }

  public function envelope($g) {
    // TODO this was copped from geo.inc and may not be fully functional.
    $x = $g->x;
    $y = $g->y;

    $offset_x = $limit / (GEO_DEGREE_M * cos($y));
    $offset_y = $limit / GEO_DEGREE_M;
    $offset_x = $limit / GEO_DEGREE_M; // TODO Miles
    $offset_y = $limit / round(GEO_DEGREE_M * cos($x / 92215));

    // Create a linestring that represents a closed box around the envelope.
    $line = $this->linestring();
    $line->addPoint($x - $offset_x, $y + $offset_y);
    $line->addPoint($x + $offset_x, $y + $offset_y);
    $line->addPoint($x + $offset_x, $y - $offset_y);
    $line->addPoint($x - $offset_x, $y - $offset_y);
    $line->addPoint($x - $offset_x, $y + $offset_y);

    // Return a polygon constructed from the envelope linestring.
    return $this->polygon($line);
  }

  public function x($point) {
    return (float) $point->x;
  }

  public function y($point) {
    return (float) $point->y;
  }

  public function startPoint($curve) {
    return $this->unimplemented();
  }

  public function endPoint($curve) {
    return $this->unimplemented();
  }

  public function isClosed($curve) {
    return $this->unimplemented();
  }

  public function isRing($curve) {
    return $this->unimplemented();
  }

  public function length($curve) {
    return $this->unimplemented();
  }

  public function numPoints($linestring) {
    if (isset($linestring->points)) {
      return count($linestring->points);
    }
    return 0;
  }

  public function pointN($linestring, $n) {
    if (isset($linestring->points)) {
      return $linestring->points[$n - 1];
    }
  }

  public function centroid($surface) {
    return $this->unimplemented();
  }

  public function pointOnSurface($surface) {
    return $this->unimplemented();
  }

  public function area($surface) {
    return $this->unimplemented();
  }

  public function exteriorRing($polygon) {
    return $this->unimplemented();
  }

  public function numInteriorRing($polygon) {
    return $this->unimplemented();
  }

  public function interiorRingN($polygon, $n) {
    return $this->unimplemented();
  }

  public function numGeometries($geomcollection) {
    return $this->unimplemented();
  }

  public function geometryN($geomCollection, $n) {
    return $this->unimplemented();
  }

  public function equals($g1, $g2) {
    return $this->unimplemented();
  }

  public function disjoint($g1, $g2) {
    return $this->unimplemented();
  }

  public function touches($g1, $g2) {
    return $this->unimplemented();
  }

  public function within($g1, $g2) {
    return $this->unimplemented();
  }

  public function overlaps($g1, $g2) {
    return $this->unimplemented();
  }

  public function crosses($g1, $g2) {
    return $this->unimplemented();
  }

  public function intersects($g1, $g2) {
    return $this->unimplemented();
  }

  public function contains($g1, $g2) {
    return $this->unimplemented();
  }

  public function relate($g1, $g2, $pattern = NULL) {
    return $this->unimplemented();
  }

  public function distance($g1, $g2) {
    return $this->unimplemented();
  }

  public function intersection($g1, $g2) {
    return $this->unimplemented();
  }

  public function difference($g1, $g2) {
    return $this->unimplemented();
  }

  public function union($g1, $g2) {
    return $this->unimplemented();
  }

  public function symDifference($g1, $g2) {
    return $this->unimplemented();
  }

  public function buffer($g1, $distance) {
    return $this->unimplemented();
  }

  public function convexHull($g1) {
    return $this->unimplemented();
  }

  // Implementation-specfic functions: useful primarily to this application.
  function setGID($value = NULL) {
    $this->gid = (int) $value;
  }

  public function gid() {
    return NULL;
  }

  function setName($value) {
    $this->name = preg_replace('/[^a-z0-9_]/', '', strtolower($value));
  }

  function name() {
    return $this->name;
  }

  function setTitle($value) {
    $this->title = filter_xss($value);
  }

  public function title() {
    return NULL;
  }

  function setSRID($value = NULL) {
    if (is_int($value)) {
      $this->srid = $value;
    }
    else {
      $this->srid = GEO_SRID_DEFAULT;
    }
  }

  function setGeoType($value = NULL) {
    if (is_int($value)) {
      $this->geo_type = $value;
    }
    else {
      $this->geo_type = GEO_UNKNOWN;
    }
  }

  function geoType() {
    return $this->geo_type;
  }

  public function vars() {
    return get_object_vars($this);
  }
}
