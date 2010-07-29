<?php // $Id: geo.inc,v 1.3 2009/12/04 23:09:34 vauxia Exp $

interface GeoInterface {

  /**
   * Factory methods for different geometries.
   */
  public function point($x, $y);

  public function linestring();

  public function polygon();

  public function multiPoint();

  public function multiLinestring();

  public function multiPolygon();

  public function geometryCollection();

  /**
   *  Functions for constructing a geometric object given its Well-known Text
   *  Representation.
   */


  /**
   *  Construct a geometric object given its Well-known text Representation
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @param $type
   *  @return GeoGeometry
   *
   *  This function differs from the OGC specification by specifying an additional
   *  parameter for $type.
   *
   */
  public function geomFromText($wkt, $srid = GEO_SRID_DEFAULT, $type = NULL);

  /**
   *  Construct a Point
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoPoint
   */
  public function pointFromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a LineString
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoLinestring
   */
  public function lineFromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a Polygon
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoPolygon
   */
  public function polyfromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a MultiPoint
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoMultiPoint
   */
  public function mPointFromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a MultiLineString
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoMultiLineString
   */
  public function mLineFromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a MultiPolygon
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoMultiPolygon
   */
  public function mPolyFromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a GeometryCollection
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoGeometryCollection
   */
  public function geomCollFromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a Polygon given an arbitrary collection of closed linestrings
   *  as a MultiLineString text representation
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoPolygon
   */
  public function bdPolyFromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a MultiPolygon given an arbitrary collection of closed linestrings
   *  as a MultiLineString text representation
   *
   *  @param string $wkt Well Known Text
   *  @param integer $srid
   *  @return GeoMultiPolygon
   */
  public function bdMPolyFromText($wkt, $srid = GEO_SRID_DEFAULT);

  /**
   *  Functions for constructing a geometric object given its Well-known Binary
   *  Representation.
   */

  /**
   *  Construct a geometric object given its Well-known Binary Representation
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @param $type
   *  @return GeoGeometry
   *
   *  This function differs from the OGC specification by specifying an additional
   *  parameter for $type.
   */
  public function geomFromWKB($wkb, $srid = GEO_SRID_DEFAULT, $type = NULL);

  /**
   *  Construct a Point
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeoPoint
   */
  public function pointFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a LineString
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeoLinestring
   */
  public function lineFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a Polygon
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeoPolygon
   */
  public function polyFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a MultiPoint
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeoMultiPoint
   */
  public function mPointFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a MultiLineString
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeoMultiLineString
   */
  public function mLineFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a MultiPolygon
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeoMultiPolygon
   */
  public function mPolyFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a GeometryCollection
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeometryCollection
   */
  public function geomCollFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a Polygon given an arbitrary collection of closed linestrings as
   *  a MultiLineString binary representation
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeometryPolygon
   */
  public function bdPolyFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   *  Construct a MultiPolygon given an arbitrary collection of closed
   *  linestrings as a MultiLineString binary representation
   *
   *  @param string $wkb Well Known Binary
   *  @param integer $srid
   *  @return GeometryMultiPolygon
   */
  public function bdMPolyFromWKB($wkb, $srid = GEO_SRID_DEFAULT);

  /**
   * Get the Well-known Text representation of a Geometry object
   *
   * @param Geometry $g
   * @return string Well-known Text
   */
  public function asText($g);

  /**
   * Get the Well-known Binary representation of a Geometry object
   *
   * @param Geometry $g
   * @return binary Well-known Binary
   */
  public function asBinary($g);

  /**
   * Get the dimension of a geometric object, which is less than or equal
   * to the dimension of the coordinate space
   *
   * @param Geometry $g
   * @return integer
   */
  public function dimension($g);

  /**
   * Returns the name of the instantiable subtype of Geometry of which
   * this geometric object is a member, as a string
   *
   * @param Geometry $g
   * @return string
   *
   *  This function differs from the OGC specification by permitting the
   *  Geometry parameter to be NULL.  If this parameter is omitted, the
   *  function should return the default geometryType of the instance.
   */
  public function geometryType($g = NULL);

  /**
   * Returns the Spatial Reference System ID for this geometric object
   *
   * @param Geometry $g
   * @return integer
   *
   *  This function differs from the OGC specification by permitting the
   *  Geometry parameter to be NULL.  If this parameter is omitted, the
   *  function should return the default SRID of the instance.
   */
  public function SRID($g = NULL);

  public function isEmpty($g);

  public function isSimple($g);

  public function boundary($g);

  public function envelope($g);

  public function x($point);

  public function y($point);

  public function startPoint($curve);

  public function endPoint($curve);

  // also: multicurve.
  public function isClosed($curve);

  public function isRing($curve);

  // also: multicurve.
  public function length($curve);

  public function numPoints($linestring);

  public function pointN($linestring, $n);

  // also: multisurface.
  public function centroid($surface);

  // also: multisurface.
  public function pointOnSurface($surface);

  // also: multisurface.
  public function area($surface);

  public function exteriorRing($polygon);

  public function numInteriorRing($polygon);

  public function interiorRingN($polygon, $n);

  public function numGeometries($geomcollection);

  public function geometryN($geomCollection, $n);

  public function equals($g1, $g2);

  public function disjoint($g1, $g2);

  public function touches($g1, $g2);

  public function within($g1, $g2);

  public function overlaps($g1, $g2);

  public function crosses($g1, $g2);

  public function intersects($g1, $g2);

  public function contains($g1, $g2);

  public function relate($g1, $g2, $pattern = NULL);

  public function distance($g1, $g2);

  public function intersection($g1, $g2);

  public function difference($g1, $g2);

  public function union($g1, $g2);

  public function symDifference($g1, $g2);

  public function buffer($g1, $distance);

  public function convexHull($g1);

  // Common functions: not part of the OGC specfication per se, but frequently
  // implemented by the various backends.
  public function addPoint($linestring, $point, $position = NULL);

  // Implementation-specfic functions: useful primarily to the Geo API.
  public function geoCompatible($g);

  public function setGID($value = NULL);
  public function gid();

  public function setName($value);
  public function name();

  public function setTitle($value);
  public function title();

  public function setSRID($value = NULL);
  public function setGeoType($value = NULL);

  public function geoType();

  public function vars();
}

interface GeoGeometry {
  // Implementation-specfic functions.
  public function geoCompatible($g);

  // OGR functions.
  public function dimension();

  public function geometryType();

  public function asText();

  public function asBinary();

  public function SRID();

  public function isEmpty();

  public function isSimple();

  public function boundary();

  public function envelope();
}

Interface GeoGeometryPoint extends GeoGeometry {

  public function x();

  public function y();
}

interface GeoGeometryCurve extends GeoGeometry {

  // Implementation-specfic functions.
  public function addPoint($point, $position = NULL);

  // OGR functions.
  public function startPoint();

  public function endPoint();

  public function isClosed();

  public function isRing();

  public function length();
}

interface GeoGeometryLinestring extends GeoGeometryCurve {

  public function numPoints();

  public function pointN($n);
}

interface GeoGeometrySurface extends GeoGeometry {

  public function centroid ();

  public function pointOnSurface();

  public function area();
}

interface GeoGeometryPolygon extends GeoGeometrySurface {

  public function exteriorRing();

  public function numInteriorRing();

  public function interiorRingN($n);
}

interface GeoGeometryCollection extends GeoGeometry {

  public function numGeometries();

  public function geometryN($n);
}

interface GeoGeometryMultipoint extends GeoGeometryCollection {
}

interface GeoGeometryMultiCurve extends GeoGeometryCollection {

  public function isClosed();

  public function length();
}

interface GeoGeometryMultiLinestring extends GeoGeometry {
}

interface GeoGeometryMultiSurface extends GeoGeometry {

  public function centroid();

  public function pointOnSurface();

  public function area();
}

interface GeoGeometryMultiPolygon extends GeoGeometryMultiSurface {
}

/**
 * Implementations of specific geometry types.
 *
 * These should not need to be overridden,
 */
class Geometry implements GeoGeometry{

  protected $handler;

  // Determine whether another item's handler is compatible with this one.
  public function geoCompatible($g) {
    return $this->call('geoCompatible');
  }

  // Call my handler's version of the requested function, including additional args.
  // TODO! this is important and useful.
  protected function call() {
    $args = func_get_args();
    $function = array_shift($args);
    return $this->handler->$function($this, $args);
  }

  public function dimension() {
    return $this->call('dimension');
  }

  public function geometryType() {
    return $this->call('geometryType');
  }

  public function asText() {
    return $this->call('asText');
  }

  public function asBinary() {
    return $this->call('asBinary');
  }

  public function SRID() {
    return $this->call('SRID');
  }

  public function isEmpty() {
    return $this->call('isEmpty');
  }

  public function isSimple() {
    return $this->call('isSimple');
  }

  public function boundary() {
    return $this->call('boundary');
  }

  public function envelope() {
    return $this->call('envelope');
  }
}

class GeometryPoint extends Geometry implements GeoGeometryPoint{
  protected $geo_type = GEO_TYPE_POINT;
  protected $geo_dimension = 0;

  protected $x;
  protected $y;

  function __construct($x, $y) { // TODO is this kosher?
    $this->x = $x;
    $this->y = $y;
  }

  function x() {
    return $this->call('x');
  }

  function y() {
    return $this->call('y');
  }
}

class GeometryCurve extends Geometry implements GeoGeometryCurve {
  protected $geo_type = GEO_TYPE_CURVE;
  protected $geo_dimension = 1;

  protected $points = array();

  function addPoint($point, $position = NULL) {
    return $this->call('addPoint', $point);
  }

  function startPoint() {
    return $this->call('startPoint');
  }

  function endPoint() {
    return $this->call('endPoint');
  }

  function isClosed() {
    return $this->call('isClosed');
  }

  function isRing() {
    return $this->call('isRing');
  }

  function length() {
    return $this->call('length');
  }
}

class GeometryLinestring extends GeometryCurve implements GeoGeometryLinestring {
  protected $geo_type = GEO_TYPE_LINESTRING;
  protected $geo_dimension = 1;

  function numPoints() {
    return $this->call('numPoints');
  }

  function pointN($n) {
    return $this->call('pointN', $n);
  }
}

class GeometrySurface extends Geometry implements GeoGeometrySurface {
  protected $geo_type = GEO_TYPE_SURFACE;
  protected $geo_dimension = 2;

  function centroid() {
    return $this->call('centroid');
  }

  function pointOnSurface() {
    return $this->call('pointOnSurface');
  }

  function area() {
    return $this->call('area');
  }
}

class GeometryPolygon extends GeometrySurface implements GeoGeometryPolygon {
  protected $geo_type = GEO_TYPE_POLYGON;
  protected $geo_dimension = 2;

  function exteriorRing() {
    return $this->call('exteriorRing');
  }

  function numInteriorRing() {
    return $this->call('numInteriorRing');
  }

  function interiorRingN($n) {
    return $this->call('interiorRingN', $n);
  }
}

class GeometryCollection extends Geometry implements GeoGeometryCollection {
  protected $geo_type = GEO_TYPE_COLLECTION;

  public function numGeometries() {
    return $this->call('numGeometries');
  }

  public function geometryN($n) {
    return $this->call('geometryN', $n);
  }

}

class GeometryMultipoint extends GeometryCollection implements GeoGeometryMultipoint {
  protected $geo_type = GEO_TYPE_MULTIPOINT;
  protected $geo_dimension = 0;
}

class GeometryMulticurve extends GeometryCollection implements GeoGeometryMulticurve {
  protected $geo_type = GEO_TYPE_MULTICURVE;
  protected $geo_dimension = 1;

  function isClosed() {
    return $this->call('isClosed');
  }

  function length() {
    return $this->call('length');
  }
}

class GeometryMultiLinestring extends GeometryMulticurve implements GeoGeometryMultiLinestring {
  protected $geo_type = GEO_TYPE_MULTILINESTRING;
  protected $geo_dimension = 1;
}

class GeometryMultisurface extends GeometryCollection implements GeoGeometryMultisurface {
  protected $geo_type = GEO_TYPE_MULTISURFACE;
  protected $geo_dimension = 2;

  function centroid() {
    return $this->call('centroid');
  }

  function pointOnSurface() {
    return $this->call('pointOnSurface');
  }

  function area() {
    return $this->call('area');
  }
}

class GeometryMultiPolygon extends GeometryMultisurface implements GeoGeometryMultiPolygon {
  protected $geo_type = GEO_TYPE_MULTIPOLYGON;
}
