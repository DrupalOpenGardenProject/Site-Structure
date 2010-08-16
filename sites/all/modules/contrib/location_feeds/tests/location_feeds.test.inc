<?php
// $Id: location_feeds.test.inc,v 1.1.2.2 2010/06/07 17:09:57 elliottf Exp $

/**
 * @file
 *
 * Test functions for the location_feeds module
 *
 * @author: Elliott Foster
 */

require_once(drupal_get_path('module', 'feeds') . '/tests/feeds_mapper_test.inc');

/**
 * Class for testing Feeds <em>location</em> mapper.
 */
class FeedsMapperLocationTestCase extends FeedsMapperTestCase {

  protected function _location_defaults() {
    // Get the (settable) defaults.
    $defaults = array();
    $hide = array();
    $d = location_invoke_locationapi($location, 'defaults');
    $fields = location_field_names();
    foreach ($fields as $k => $v) {
      $defaults[$k] = $d[$k];
      $hide[$k] = 0;
    }

    foreach ($defaults as $k => $v) {
      // Change collection to allow.
      $defaults[$k]['collect'] = 1;
    }

    $settings = array(
      'location_settings' => array(
        'multiple' => array(
          'min' => 1,
          'max' => 1,
          'add' => 1,
        ),
        'form' => array(
          'weight' => 0,
          'collapsible' => 0,
          'collapsed' => 0,
          'fields' => $defaults,
        ),
        'display' => array(
          'weight' => 0,
          'hide' => $hide,
          'teaser' => 1,
          'full' => 1,
        ),
        'rss' => array(
          'mode' => 'simple',
        ),
      ),
    );

    return $settings;
  }

}

