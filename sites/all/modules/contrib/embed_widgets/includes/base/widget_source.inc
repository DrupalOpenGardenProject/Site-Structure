<?php
// $Id: widget_source.inc,v 1.9.2.2 2009/06/20 22:13:58 jtsnow Exp $

/**
 * An abstract object providing the member functions required for widget source objects.
 */
abstract class widget_source {
  public $type;
  public $id;
  public $delta;
  public $content;
  public $params;
  protected $settings = array();
  
  public function __construct($id = NULL, $delta = NULL) {
    list($this->type) = explode("_", get_class($this));
    if (is_array($id)) {
      $settings = $id;    // TODO: This needs to be deprecated.
    }
    else {
      $this->id = $id;
      $this->delta = $delta;
    }
  }
  
  public function set_variable($name, $value) {
      $this->settings[$name] = $value;
  }
  public function get_variable($name) {
      return $this->settings[$name];
  }

  abstract static public function info();
  abstract public function check_access();
  abstract protected function build();
  
  public function save($wid, $query_type) {
    return TRUE;
  }
  
  public function get_content() {
    if (!isset($content)) {
      $this->content = $this->build();
    }
    return $this->content;
  }
  
  static public function admin_settings_form() {
    return array();
  }
  
  public function parameters_form() {
    $form = array();
    return $form;
    
    // Generate in-widget form for configuration and sharing.
    /*  http://www.clearspring.com/docs/website/widget-console#parameters
     *  User editable: When the widget is shared, the user will have the option of changing the value of this parameter for their new installation (see image above).
        Hidden: A Hidden parameter will be managed by the server and passed as usual, but the end user will not be able to see or edit it.
        For user-editable parameters, you then have several other options:
        Required: Whether or not the end user is actually required to enter a value for this parameter when grabbing the widget.
        User Facing Label: The user-friendly name of the parameter, which end users will see when getting their own instance of the widget.
        Type: The data type of the variable, which is used to control the type of input the user is allowed to specify. You can use this parameter to, for example, offer a list of choices to the end user, or to allow them to type text freely.
     */
    
  }
}