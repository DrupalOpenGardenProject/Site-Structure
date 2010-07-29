<?php // $Id: views_plugin_display_geo_xml.inc,v 1.1 2009/03/02 06:25:50 vauxia Exp $

/**
 * @file
 * Geo XML display plugin for Views.
 */

class views_plugin_display_geo_xml extends views_plugin_display_feed {
  function get_style_type() { return 'geo_xml'; }

  function option_definition() {
    $options = parent::option_definition();

    // Overrides for feed plugin:
    $options['style_plugin']['default'] = 'geo_kml';

    return $options;
  }
}
