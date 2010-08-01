<?php
// $Id: widget_platform.inc,v 1.13.2.2 2009/08/12 03:06:46 jtsnow Exp $

// Possible platforms: http://www.clearspring.com/docs/tech/distribution/destinations

/**
 * An object providing the member functions required for widget platforms.
 */
abstract class widget_platform {
  public $name;
  public $id;
  public $description;
  public $js_variables;
  
  protected $parent_widget;
  
  //public $allowed_formats = array();
   
  static public function check_format($format) {
    $info = $this->info();
    return (is_string($format) && in_array($format, $info['formats']));
  }
  
  
  abstract static public function info();
  abstract static public function live_preview($widget);
  
  static public function platform_file($widget) {
    return false;
  }
  
  static public function theme() {
    return array();
  }
  
  static public function settings_form() {
    return array();
  }
}
