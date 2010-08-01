<?php
// $Id: iframe.inc,v 1.8.2.2 2009/08/01 19:45:26 jtsnow Exp $

class iframe extends widget_format {

  static public function info() {
    return array(
      'title' => t('iFrame'),
      'description' => t('Can be embedded on any website, blog, or social network that allows &lt;script&gt; tags.'),
      'path' => drupal_get_path('module', 'embed_widgets') . '/includes/format/iframe',
      //'embed_path' => drupal_get_path('module', 'embed_widgets'),
      'embed_file' => 'iframe.js',
      'embed_header' => 'Content-type: text/javascript; charset=utf-8',
      'css' => array('iframe.css'),
    );
  }
  
  static public function theme() {
    $path = drupal_get_path('module', 'embed_widgets');
    return array(
      'iframe' => array(
        'template' => 'widgets-iframe',
        'arguments' => array('content' => NULL, 'show_blocks' => TRUE, 'show_messages' => TRUE),
        //'path' => "$path/includes/format/iframe"
        'path' => drupal_get_path('module', 'embed_widgets') . "/includes/format/iframe"
      ),
    );
  }
  
  static public function settings_form(embed_widget $widget) {
    $form = array();
    $form['format']['iframe']['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $defaults['width'] ? $defaults['width'] : 450,
      '#size' => 6,
      '#maxlength' => 6,
      '#field_suffix' => 'pixels',
      '#required' => TRUE,
    );
    $form['format']['iframe']['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => $defaults['height'] ? $defaults['height'] : 300,
      '#size' => 6,
      '#maxlength' => 6,
      '#field_suffix' => 'pixels',
      '#required' => TRUE,
    );
    return $form;
  }
  
  static public function admin_settings() {
    $form = array();
    $form['iframe'] = array(
      '#type' => 'fieldset',
      '#title' => t('iFrame Settings'),
      '#collapsible' => FALSE,
    );
  
    $form = system_settings_form($form);
    return $form;
  }

  static public function embed_file(embed_widget $widget) {
    $format_info = iframe::info();
    
    // Make variables available to JavaScript.
    $widget_context = new stdClass();
    $widget_context->wid = $widget->encode();
    $widget_context->url = $widget->get_content_url();
    $widget_context->width = $widget->get_variable('width');
    $widget_context->height = $widget->get_variable('height');
    $widget_context->jquery = url('misc/jquery.js', array('absolute' => TRUE));
    $widget_context->new_placement = url('embed-widgets/js/get-code/' . $widget->wid . '/' . $widget->iid, array('absolute' => TRUE));
    $widget_context->base_url = url('', array('absolute' => TRUE));
    
    $file = 'widgetContext = ' . drupal_to_js($widget_context) . "\n";
    
    $file .= file_get_contents('./' . $format_info['path'] . '/' . $format_info['embed_file']);
    drupal_set_header($format_info['embed_header']);
    $path = $format_info['path'] . '/' . $format_info['embed_file'];
    
    return $file;
  }
  
  static public function embed_code(embed_widget $widget, $noscript = FALSE) {
    $format_info = iframe::info();
    
    if (!empty($noscript)) {
      $output = '<div id="widget-embed-wrapper">';
      $output .= '<iframe frameborder="0" width="'. $widget->get_variable('width') . '" height="'. $widget->get_variable('height') . '" id="drupal-embed" src="' . $widget->get_content_url() . '"></iframe>';
      $output .= '</div>';
      return $output;
    }
    
    return '<script id="widget-embed-script-' . $widget->encode() . '" src="' . $widget->get_embed_url($format_info['embed_file']) . '"></script>';
  }
  

  
}
