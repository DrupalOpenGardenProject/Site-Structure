<?php
// $Id: html.inc,v 1.11.2.3 2009/08/01 19:45:26 jtsnow Exp $

class html extends widget_platform {
    
  static public function info() {
    return array(
      'title' => t('HTML'),
      'description' => t('Embed on your website or blog.'),
      'formats' => array('iframe'),
      'share_method' => 'code',
    );
  }
  
  static public function theme() {
    return array();
  }
  
  static public function code($widget, $no_script = FALSE) {
    //$format_info = call_user_func($this->format . '::info');
    switch($widget->format) {
      case 'iframe':
        $code = call_user_func($widget->format . '::embed_code', $widget, $no_script);
        break;
      case 'flash':
        $code = '';
        break;
    }
    
    return $code;
  }
  
  static public function live_preview($widget) {
    switch($widget->format) {
      case 'iframe':
        if (function_exists($widget->format . '::embed_code_noscript')) {
          $code = call_user_func($widget->format . '::embed_code_noscript', $widget);
        }
        break;
      case 'flash':
        $code = '';
        break;
    }
    
    return $code;
  }
    
//  public function settings_form() {  }
//  public function admin_settings() {  }
  
}

