<?php // $Id: views_plugin_style_geo_xml.inc,v 1.1 2009/03/02 06:25:50 vauxia Exp $
/**
 * @file
 * Contains the Geo XML style plugin.
 */

/**
 * Default style plugin to render an XML feed.
 *
 * @ingroup views_style_plugins
 */
class views_plugin_style_geo_xml extends views_plugin_style {
  var $xml;
  var $doc;

  /**
   * Permit "normal" items here, which may be rendered into XML.
   */
  function get_style_type() { return 'normal'; }

  /**
   * The XML mime type for this type of output.
   */
  function xml_type() { return 'text/xml'; }

  /**
   * The DOM Document type for this type of output.
   */
  function xml_dom_type() { }

  /**
   * Override this to provide a root element.
   */
  function xml_root() {
  }

  function attach_to($display_id, $path, $title) {
    $display = $this->view->display[$display_id]->handler;
    $url_options = array();
    $input = $this->view->get_exposed_input();
    if ($input) {
      $url_options['query'] = $input;
    }

    $url = url($this->view->get_url(NULL, $path), $url_options);
    if ($display->has_path()) {
      if (empty($this->preview)) {
        drupal_add_feed($url, $title);
      }
    }
    else {
      if (empty($this->view->feed_icon)) {
        $this->view->feed_icon = '';
      }

      $this->view->feed_icon .= theme('feed_icon', $url, $title);
      drupal_add_link(array(
        'rel' => 'alternate',
        'type' => $this->xml_type(),
        'title' => $title,
        'href' => $url
      ));
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['description'] = array('default' => '', 'translatable' => TRUE);
    $options['mission_description'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['mission_description'] = array(
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['mission_description']),
      '#title' => t('Use the site mission for the description'),
    );
    $form['description'] = array(
      '#type' => 'textfield',
      '#title' => t('RSS description'),
      '#default_value' => $this->options['description'],
      '#description' => t('This will appear in the RSS feed itself.'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-style-options-override' => array(FALSE)),
    );
  }

  function add_row($doc, $row) {
    $xml_row = $this->xml->createElement('row');
    $doc->appendChild($xml_row);
    foreach ($row as $key => $val) {
      $item = $this->xml->createElement($key, $val);
      $xml_row->appendChild($item);
    }
  }

  function pre_render() {
    if ($type = $this->xml_dom_type()) {
      $impl = new DomImplementation;
      $dtd = $impl->createDocumentType($type['name'], $type['public_id'], $type['system_id']);
      $this->xml = $impl->createDocument('', '', $dtd);
      $this->xml->encoding = 'UTF-8';
      $this->xml->standalone = 'no';
    }
    else {
      $this->xml = new DOMDocument('1.0', 'UTF-8');
    }

    if ($type = $this->xml_root()) {
      $this->doc = $this->xml->appendChild($this->xml->createElement($type['name']));
      if (isset($type['attributes'])) {
        foreach ($type['attributes'] as $name => $value) {
          $this->doc->setAttribute($name, $value);
        }
      }
    }
    else {
      $this->doc = $this->xml;
    }
  }

  function render() {
    foreach ($this->view->result as $row) {
      $this->add_row($this->doc, $row);
    }
   
    // Handle any last-minute modifications.
    $this->xml_post_render();

    drupal_set_header('Content-Type: '. $this->xml_type());
    return $this->xml->saveXML();
  }

  function xml_post_render() {
  }
}
