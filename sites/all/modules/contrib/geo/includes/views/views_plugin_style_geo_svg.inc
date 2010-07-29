<?php // $Id: views_plugin_style_geo_svg.inc,v 1.3 2009/05/19 18:29:13 vauxia Exp $
/**
 * @file
 * Contains the Geo XML style plugin.
 */

/**
 * Default style plugin to render an XML feed.
 *
 * @ingroup views_style_plugins
 */
class views_plugin_style_geo_svg extends views_plugin_style_geo_xml {

  // Keep track of our bounding box entries.
  var $min_x = 0;
  var $min_y = 0;
  var $max_x = 0;
  var $max_y = 0;

  function xml_type() { return 'image/svg+xml'; }

  /**
   * The SVG DOMDOCUMENT type.
   */
  function xml_dom_type() {
    return array(
      'name' => 'svg',
      'public_id' => '-//W3C//DTD SVG 1.1//EN',
      'system_id' => 'http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd',
    );
  }

  /**
   * The root XML element.
   */
  function xml_root() {
    return array(
      'name' => 'svg',
      'attributes' => array(
        'id' => 'geo_svg',
        'xmlns' => 'http://www.w3.org/2000/svg',
        'xmlns:attrib' => 'http://www.carto.net/attrib',
        'xmlns:xlink' => 'http://www.w3.org/1999/xlink',
      ),
    );
  }

  /**
   * Rather than the usual act of displaying a feed icon, embed the SVG graphic
   */
  function attach_to($display_id, $path, $title) {
    $display = $this->view->display[$display_id]->handler;
    $url_options = array();
    $input = $this->view->get_exposed_input();
    if ($input) {
      $url_options['query'] = $input;
    }

    $url = url($this->view->get_url(NULL, $path), $url_options);

    $attachment = '<embed width="500" height="300" src="'. $url .'"
        pluginspage="http://www.adobe.com/svg/viewer/install/" />';

    $this->view->attachment_before .= $attachment;
  }

  function viewBox($bbox = NULL) {
    // Line, Polygon data that has a bounding box.
    if (isset($bbox)) {
      $data = geo_wkb_get_data($bbox, 'text');
      $bbox = explode(' ', $data['value']);
      if($bbox[0] < $this->min_y || !$this->min_y) $this->min_y = $bbox[0];
      if($bbox[1] < $this->min_x || !$this->min_x) $this->min_x = $bbox[1];
      if($bbox[4] > $this->max_y || !$this->max_y) $this->max_y = $bbox[4];
      if($bbox[5] > $this->max_x || !$this->max_x) $this->max_x = $bbox[5];
    }
    else {
      return $this->min_y .' '. $this->min_x .' '.
        ($this->max_y - $this->min_y) .' ' . ($this->max_x - $this->min_x);
    }
  }

  function pre_render() {
    parent::pre_render();

    $width = 500; $height = 300;  // TODO options.

    $this->doc->setAttribute('width', $width .'px');
    $this->doc->setAttribute('height', $height .'px');

    // Set a transformation to correctly orient the results.
    $g = $this->doc->appendChild($this->xml->createElement('g'));
    $g->setAttribute('transform', 'rotate(-90,'.(($width)/2) .','.(($height)/2).')');
    
    // Set the viewbox for the output.  We may need to modify this later.
    $this->svg = $g->appendChild($this->xml->createElement('svg'));
    $this->svg->setAttribute('id', 'geo_box');
    $this->svg->setAttribute('width', '95%');
    $this->svg->setAttribute('height', '95%');
    $this->svg->setAttribute('viewBox', $this->viewBox());
    $this->svg->setAttribute('preserveAspectRatio', 'xMidYMid meet');

    $this->doc = $this->svg->appendChild($this->xml->createElement('g'));
    $this->doc->setAttribute('id', 'geo_shape');
  }

  function add_row($doc, $fields) {
    foreach ($fields as $key => $val) {
      // TODO this is for proof-of-concept.  Make sure my wkb's are added right.
      if (substr($key, -5) == '_bbox' && $val) {
        $this->viewBox($val);
      }
      if (substr($key, -4) == '_wkb' && $val) {
        $data = geo_wkb_get_data($val, 'text');

        switch ($data['type']) {
          case 'point':
            $item = $this->xml->createElement('circle');
            $item->setAttribute('cx', $data['y']);
            $item->setAttribute('cy', $data['x']);
            $item->setAttribute('r', '.5%');

            $item->setAttribute('fill', 'black');
  
            $this->doc->appendChild($item);
            break;
 
          case 'linestring':
            $item = $this->xml->createElement('polyline');
            $item->setAttribute('points', $data['value']);

            $item->setAttribute('stroke', 'green');
            $item->setAttribute('stroke-width', '1%');
            $item->setAttribute('fill', 'none');

            $this->doc->appendChild($item);
            break;

          case 'polygon':
            $item = $this->xml->createElement('path');
            $item->setAttribute('d', 'M'. $data['value'] .'z');
            $item->setAttribute('fill', 'red');

            $item->setAttribute('stroke', 'blue');
            $item->setAttribute('stroke-width', '.5%');

            $this->doc->appendChild($item);
            break;
        }
      }
    }
  }

  function xml_post_render() {
    // Reset the viewbox to the correct dimensions.
    $this->svg->setAttribute('viewBox', $this->viewBox());
  }
}
