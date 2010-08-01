<?php
// $Id: embed_widget_callback.inc,v 1.1.2.3 2009/08/02 02:30:07 jtsnow Exp $

/**
 * An object containing all the data and member functions to allow a user function to provide widget content.
 */
class embed_widget_callback extends embed_widget {
    
  protected $content = NULL;
  protected $callback = NULL;
  protected $access_callback = NULL;
  protected $file = NULL;
  
  static public function info() {
    return array(
      'title' => t('Callback'),
      'description' => t('Allows modules to define content to be embedded in widgets.'),
      'name' => 'callback',
    );
  }
  
  /**
   * Constructor. Accepts either a numeric or encrypted widget ID.
   *
   * @param $type
   *   The type of content being embedded (node, block, view, etc.)
   * @param $id
   *   The id of the content being embedded.
   * @param $delta
   *   An extra identifier for the content being embedded. Optional.
   */
  function __construct($type, $module, $delta, $platform = 'html', $format = 'iframe', $cache_id = NULL) {
    parent::__construct($type, $module, $delta, $platform, $format, $cache_id = NULL);
    
    $info = embed_widgets_module_widget($module, $delta);
    $this->callback = is_string($info['callback']) ? $info['callback'] : NULL;
    $this->access_callback = is_string($info['access_callback']) ? $info['access_callback'] : NULL;
    $this->file = is_string($info['file']) ? $info['file'] : NULL;
    $this->title = is_string($info['title']) ? $info['title'] : NULL;

  }
  
  protected function load_content() {
//    if (isset($this->file)) {
//      include $this->file;
//    }
    if (isset($this->callback) && function_exists($this->callback)) {
      if (!isset($this->params) || !is_array($this->params)) {
        $this->params = array();
      }
      $this->content = call_user_func_array($this->callback, $this->params);
      if (!empty($this->content)) {
        return TRUE;
      }
    }
    return FALSE;
  }
  
  protected function view_content() {
    if (!empty($this->content)) {
      return $this->content;
    }
    return FALSE;
  }
  
  protected function get_title() {
    return $this->title;
  }
  
  public function check_access() {
//    if (isset($this->file)) {
//      include $this->file;
//    }
    if (isset($this->access_callback) && function_exists($this->access_callback)) {
      if (!isset($this->params) || !is_array($this->params)) {
        $this->params = array();
      }
      return call_user_func_array($this->access_callback, $this->params);
    }
    return TRUE;
  }
}