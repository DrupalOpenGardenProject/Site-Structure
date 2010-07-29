<?php
// $Id: openlayers_behavior_geotaxonomy.inc,v 1.1.2.1 2010/02/04 19:14:02 tmcw Exp $

/**
 * @file
 * Implementation of OpenLayers behavior.
 */

/**
 * Map Form Values Behavior
 */
class openlayers_behavior_geotaxonomy extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'centerpoint' => array(
        'lat' => '#edit-lat',
        'lon' => '#edit-lon',
      ),
      'bounds' => array(
        '#edit-bound-left',
        '#edit-bound-bottom',
        '#edit-bound-right',
        '#edit-bound-top'
      )
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'geotaxonomy') .'/includes/behaviors/js/openlayers_behavior_geotaxonomy.js');
    return $this->options;
  }
}
