<?php
// $Id: widget_format.inc,v 1.17.2.1 2009/06/19 13:30:43 jtsnow Exp $


/**
 * An abstract object providing the member functions required for widget formats.
 */
abstract class widget_format {
  public $name;
  public $id;
  public $description;
  public $filename;
   
  abstract static public function info();
  abstract static public function embed_file(embed_widget $widget);
  abstract static public function embed_code(embed_widget $widget);
  static public function theme() {
    return array();
  }
  
//  function __construct() {
//    $this->id = get_class($this);
//    $info = call_user_func($this->id . '::info');
//    if (!isset($info)) {
//      drupal_set_message("Could not load info for format %name.", array('%name' => $this->id));
//      return;
//    }
//    $this->name = $info['title'];
//    $this->description = $info['description'];
//    //$this->filename = $info['filename'];
//  }
  
  static public function settings_form() {
    return array();
  }
  
  static public function admin_settings() {
    return array();
  }
}
