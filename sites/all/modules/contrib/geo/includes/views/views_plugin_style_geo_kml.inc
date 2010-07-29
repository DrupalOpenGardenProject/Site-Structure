<?php // $Id: views_plugin_style_geo_kml.inc,v 1.2 2009/05/19 18:29:13 vauxia Exp $
/**
 * @file
 * Contains the Geo XML style plugin.
 */

/**
 * Default style plugin to render an XML feed.
 *
 * @ingroup views_style_plugins
 */
class views_plugin_style_geo_kml extends views_plugin_style_geo_xml {
  function xml_type() {
    return 'application/vnd.google-earth.kml+xml';
  }

  function xml_root() {
    return array(
      'name' => 'kml',
      'attributes' => array('xmlns' => 'http://www.opengis.net/kml/2.2'),
    );
  }

  function pre_render() {
    parent::pre_render();

    $doc = $this->doc->appendChild($this->xml->createElement('Document'));

    $title = $this->xml->createElement('Name', $this->view->get_title());
    $doc->appendChild($title);
    //$desc = $this->xml->createElement('Description', $this->view->render_textarea('header'));
    //$doc->appendChild($desc);

    $style = $this->xml->createElement('Style');
    $style->setAttribute('id', 'randomColor');
    $doc->appendChild($style);

    $poly = $style->appendChild($this->xml->createElement('PolyStyle'));
    $poly->appendChild($this->xml->createElement('color', '7f7faaaa'));
    $poly->appendChild($this->xml->createElement('colorMode', 'random'));

    $this->doc = $doc;
  }

  function add_row($doc, $row) {
    $xml_row = $this->xml->createElement('Placemark');
    $doc->appendChild($xml_row);
    $xml_row->appendChild($this->xml->createElement('name', rand()));
    foreach ($row as $key => $val) {
      // TODO this is for proof-of-concept.  Make sure my wkb's are added right.
      if (substr($key, -4) == '_wkb' && $val) {
        $data = geo_wkb_get_data($val, 'kml');

        if (in_array($data['type'], array('linestring', 'point'))) {
          $type = $data['type'] == 'point' ? 'Point' : 'LineString';

          $item = $this->xml->createElement($type);
          $geo = $this->xml->createElement('coordinates', $data['value']);

          $item->appendChild($geo);
          $xml_row->appendChild($item);
        }
        elseif ($data['type'] == 'polygon') {
          $item = $this->xml->createElement('Polygon');
          $xml_row->appendChild($item);
          $outer = $this->xml->createElement('outerBoundaryIs');
          $item->appendChild($outer);
          $line = $this->xml->createElement('LinearRing');
          $outer->appendChild($line);
          $geo = $this->xml->createElement('coordinates', $data['value']);
          $line->appendChild($geo);

          $xml_row->appendChild($this->xml->createElement('styleUrl', '#randomColor'));
        }
      }
    }
  }

  function xml_post_render() {
  }
}
