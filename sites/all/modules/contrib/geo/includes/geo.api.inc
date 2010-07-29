<?php // $Id: geo.api.inc,v 1.5 2009/12/21 17:29:55 vauxia Exp $


define('GEO_SRID_DEFAULT', 4326);
define('GEO_DEGREE_M', 111206);

define('GEO_TYPE_POINT', 0);
define('GEO_TYPE_CURVE', 2);
define('GEO_TYPE_LINESTRING', 3);
define('GEO_TYPE_SURFACE', 4);
define('GEO_TYPE_POLYGON', 5);
define('GEO_TYPE_COLLECTION', 6);
define('GEO_TYPE_MULTIPOINT', 7);
define('GEO_TYPE_MULTICURVE', 8);
define('GEO_TYPE_MULTILINESTRING', 9);
define('GEO_TYPE_MULTISURFACE', 10);
define('GEO_TYPE_MULTIPOLYGON', 11);

define('GEO_UNKNOWN', -1);

/**
 * Call an API function from the geo backend databases.
 * This function will find and load the database backend files, and call
 * the requested op from the backend or the default library, as needed.
 *
 * @return mixed
 *  The result of the database operation execution.
 *
 *  TODO THERE IS A VERY GOOD CHANCE THIS WILL BE DEPRECATED!
 */
function geo($op = NULL) {
  static $backend;

  // Load common functions.
  module_load_include('inc', 'geo');

  // Load database-specific functions.
  if (!isset($backend)) {
    $backend = geo_backend_type();
    module_load_include('inc', 'geo', 'db/'. $backend);
  }

  // Call the appropriate API function: If geo_$backend_$op exists, call that.
  // Otherwise, resort to geo_$op.  This creates a sort of inheritence system.
  $args = func_get_args();
  if($args) {
    $op = array_shift($args);
    if (!function_exists($func = 'geo_'. $backend .'_'. $op)) {
      $func = 'geo_'. $op;
    }
    if (!function_exists($func)) {
      drupal_set_message(t('Call to undefined geo operation %op', array('%op' => $op)), 'error');
      return FALSE;
    }
    return call_user_func_array($func, $args);
  }
}

/**
 * API Function: Return a type constant for named
 */
function geo_type($name) {
  $name = strtoupper($name);
  if (defined('GEO_TYPE_'. $name)) {
    return constant('GEO_TYPE_'. $name);
  }
}

/**
 * API Function: Return any field types that may contain geospatial data.
 */
function geo_field_types() {
  static $field_types;
  if (!isset($field_types)) {
    $field_types = array('geo' => array(), 'geo_data' => array());
    drupal_alter('geo_field_types', $field_types);
  }
  return $field_types;
}

/**
 * API Function: Return a flat array list of field types that may contain
 * geospatial data.
 */
function geo_field_type_names() {
  return array_keys(geo_field_types());
}

/**
 * API Function: Return a list of CCK fields that contain geospatial data.
 */
function geo_fields($reset = FALSE) {
  static $fields;
  if (!$reset || !isset($fields)) {
    $field_types = geo_field_types();
    $fields = array();
    if (function_exists('content_fields')) {
      foreach (content_fields() as $field) {
        if (in_array($field['type'], array_keys($field_types))) {
          $fields[$field['field_name']] = array(
            'label' => $field['widget']['label'],
            'gis type' => $field['geo_type'],
            'srid' => $field['srid'] ? $field['srid'] : GEO_SRID_DEFAULT,
            'module' => $field['module'],
            'field' => $field,
            'gis format' => 'wkb', // TODO hard-coded.
          );
        }
      }
    }
  }
  return $fields;
}

/**
 * API Function: Return a flat array list of CCK fields that contain
 * geospatial data.
 */
function geo_field_names($reset = FALSE) {
  return array_keys(geo_fields($reset));
}

/**
 * API function: List geo datasets.
 */
function geo_list($reset = FALSE) {
  static $list;
  if ($reset || !isset($list)) {
    $list = array();
    $res = db_query("SELECT * FROM {geo} ORDER BY title");
    while ($row = db_fetch_array($res)) {
      $list[$row['gid']] = geo_load($row);
    }
  }
  return $list;
}

/**
 * API function: Load a geometry dataset.
 */
function geo_load($values) {
  // Already loaded, simply return it.
  if (is_object($values) && method_exists($values, 'gid')) {
    return $values;
  }

  if (is_scalar($values)) {
    if (is_numeric($values)) {
      // It's the gid of a known geometry dataset.
      $values = db_fetch_array(db_query("SELECT * FROM {geo}
        WHERE gid = %d", $values));
    }
    else {
      // It's the name of a handler. Load it with defaults.
      $handler = $values;
      unset($values);
    }
  }
  else {
    $values = (array) $values;
    if (!isset($values['handler'])) {
      if (isset($values['gid'])) {
        $values = array_merge($values, db_fetch_array(db_query("SELECT *
          FROM {geo} WHERE gid = %d", $values['gid'])));
      }
      elseif (isset($values['name'])) {
        if ($handler_values = db_fetch_array(db_query("SELECT *
          FROM {geo} WHERE name = '%s'", $values['name']))) {

          $values = array_merge($values, $handler_values);
          }
      }
    }
    $handler = $values['handler'];
  }
  if (geo_handler_load($handler)) {
    return New $handler($values);
  }
}

/**
 * API function: Create a new dataset using the default SQL handler.
 */
function geo_create_dataset($values = array(), $create = TRUE) {
  global $db_type;
  $values['handler'] = ($db_type == 'pgsql') ? 'GeoSQLPostGIS' : 'GeoSQLMySQL';

  // Save and return a new geo object.
  $geo = geo_save($values);

  if ($create && is_array($schema = $geo->schema())) {
    foreach ($schema as $table => $info) {
      db_create_table($ret, $table, $info);
    }
    $geo->setIndexed($geo->indexed(), TRUE);
    drupal_get_schema(NULL, TRUE);
  }

  return $geo;
}

/**
 * API function: Save a geometry dataset.
 */
function geo_save($geo) {
  $geo = geo_load($geo);

  $schema = drupal_get_schema('geo');
  $fields = array_keys($schema['fields']);

  $row = array('data' => array());
  foreach ($geo->vars() as $name => $val) {
    if (in_array($name, $fields)) {
      $row[$name] = $val;
    }
    else {
      $row['data'][$name] = $val;
    }
  }
  $row['handler'] = get_class($geo);

  // Store the reference to this datasource in our geo tables.
  $update = isset($row['gid']) ? 'gid' : NULL;
  drupal_write_record('geo', $row, $update);

  // Allow the handler do its own saving tasks.
  $geo->setGID($row['gid']);
  if (method_exists($geo, 'save')) {
    $geo->save();
  }

  // Reset the geo_list static cache.
  geo_list(TRUE);

  return $geo;
}

/**
 * API function: Delete a geometry dataset.
 */
function geo_delete($geo) {
  if (method_exists($geo, 'delete')) {
    $geo->delete();
  }
  if (isset($geo->gid)) {
    db_query("DELETE FROM {geo} WHERE gid = %d", $geo->gid);
  }
}

/**
 * API function: List all available geo handlers.
 */
function geo_handlers() {
  static $handlers;
  if (!isset($handlers)) {
    $handlers = module_invoke_all('geo_handler_info');
    drupal_alter('geo_handler', $handlers);
  }
  return $handlers;
}

/**
 * API function: Load a geo backend.
 */
function geo_handler_load($name) {
  static $cache;

  if (!isset($cache)) {
    $cache = array();
    // Include the geo interface class, geometries, and simple handling.
    module_load_include('inc', 'geo', 'includes/handlers/geo');
    module_load_include('inc', 'geo', 'includes/handlers/geo_simple');
  }

  // Already loaded.
  if (isset($cache[$name])) return $cache[$name];

  $handlers = geo_handlers();
  if ($name && $handler = $handlers[$name]) {
    // Ensure the parent is loaded.
    if (isset($handler['parent'])) geo_handler_load($handler['parent']);

    // Respect the 'path' element that may have been specified.
    $file = isset($handler['path']) ? $handler['path'] .'/' : '';
    $file .= $handler['file'];

    $cache[$name] = require_once $file;
    return $cache[$name];
  }
}

/**
 * API Function: Format WKB data
 */
function geo_wkb_get_data($wkb = NULL, $format = 'text', $fp = NULL, $type = NULL) {
  module_load_include('inc', 'geo', 'includes/geo.wkb');
  return _geo_wkb_get_data($wkb, $format, $fp, $type);
}

/**
 * API Function: List of available units.
 */
function geo_units($unit = NULL) {
  $units = array(
    'mi' => t('Miles'),
    'km' => t('Kilometers'),
    'm'  => t('Meters'),
  );

  return $unit ? $units[$unit] : $units;
}

/**
 * API Function: Convert between units.
 */
function geo_unit_convert($val, $from_unit, $to_unit) {
  switch ($from_unit) {

    case 'm': // Meters
      switch ($to_unit) {
        case 'km':
          $val = $val / 1000;
          break;
        case 'mi':
          $val = $val / 1609.344;
          break;
      }
      break;

    case 'km': // Kilometers
      switch ($to_unit) {
        case 'm':
          $val = $val * 1000;
          break;
        case 'mi':
          $val = $val * 0.62137;
          break;
      }
      break;

    case 'mi': // Miles
      switch ($to_unit) {
        case 'm':
          $val = $val * 1609.344;
          break;
        case 'km':
          $val = $val * 1.609344;
          break;
      }
      break;
  }

  return $val;
}

// TODO We are taking the element's requested input and output formats, and
// making the necessary adjustments.  This needs to be refactored and set up
// in some kind of a handler model.  For now it's a proof-of-concept that
// gets the UI & existing inputs up and running.
function geo_value($input, $output_format, $input_format = 'wkb') {

  // Nothing to do here.
  if ($output_format == $input_format) return $input;

  switch ($input_format) {
    case 'wkb':
      $value = geo_wkb_get_data($input, $output_format);
      return $value['value'];

    case 'wkt':
      break;

    case 'array':
      if ($output_format == 'wkt') {
        return geo('wkt_from_point', $input['lat'], $input['lon']);
      }
      break;
  }
}

/**
 * Determine which gis input formats are supported by a theme function.
 */
function geo_theme_input($theme) {
  static $registry;
  if (!isset($registry)) {
    init_theme();
    $registry = theme_get_registry();
  }
  return $registry[$theme]['gis input'];
}

/**
 * Determine which gis input formats are supported by a formatter.
 */
function geo_formatter_input($name, $field_type) {
  $formatter = _content_get_formatter($name, $field_type);

  // The formatter has defined a 'gis input' value.
  if (isset($formatter['gis input'])) return $formatter['gis input'];

  // Perhaps the theme has defined a 'gis input' value.  Let's check!
  return geo_theme_input($formatter['module'] .'_formatter_'. $name);
}

/**
 * Return a list of possible inputs.
 */
function geo_inputs() {
  static $inputs;
  if (!isset($inputs)) {
    $inputs = module_invoke_all('gis_input_info') ;
    foreach ($inputs as $name => $info) {
      // Ignore nonexistent element types.
      if (!$element = _element_info($info['element']['#type'])) continue;

      // Build out the element from its system defaults and from the hook.
      $element = array_merge($element, $info['element']);
      $element['#gis_input'] = $info['gis input'];

      unset($element['#parents']);
      if (!$element['#tree']) unset($element['#tree']);

      $inputs[$name]['element'] = $element;
    }
  }
  return $inputs;
}

function geo_input_info($name) {
  $inputs = geo_inputs();
  return $inputs[$name];
}

function geo_input_element_info($name) {
  $inputs = geo_inputs();
  return $inputs[$name]['element'];
}
