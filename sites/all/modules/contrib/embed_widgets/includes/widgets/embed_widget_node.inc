<?php
// $Id: embed_widget_node.inc,v 1.1.2.4 2009/07/29 03:37:28 jtsnow Exp $

/**
 * An object containing all the data and member functions to provide node content to a widget.
 */
class embed_widget_node extends embed_widget {
  
  protected $node;
   
  static public function info() {
    return array(
      'title' => t('Node'),
      'description' => t('Allows any node to be embedded as a widget.'),
      'name' => 'node',
    );
  }
  
  protected function load_content() {
    if (!isset($this->source_id)) {
      return FALSE;
    }
    if (!isset($this->node)) {
      $node = node_load($this->source_id);
      if (isset($node) && $node->nid) {
        $this->node = $node;
        return TRUE;
      }
      
    }
    return FALSE;
  }
  
  protected function view_content() {
    if (!empty($this->node)) {
      return node_view($this->node, FALSE, TRUE);
    }
    return FALSE;
  }
  
  protected function get_title() {
    return isset($this->node->title) ? $this->node->title : FALSE;
  }
  
  public function check_access() {
    if (!empty($this->node)) {
      return node_access('view', $this->node);
    }
    return FALSE;
  }
  
  static public function admin_settings_form() {
    $form = array();
    $form['node'] = array(
      '#type' => 'fieldset',
      '#title' => t('Node Widgets'),
      '#collapsible' => TRUE,
    );
    $content_types = array();
    foreach (node_get_types() as $key => $type) {
      $content_types[$key] = $type->name;
    }
    $form['node']['embed_widgets_content_types'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Content Types'),
      '#description' => t('Check the box next to each type of content that you would like to be able to use as a widget.'),
      '#options' => $content_types,
      '#default_value' => variable_get('embed_widgets_content_types', array()),
    );
    return $form;
  }
  
  static public function path_load() {
    $arg = arg();
    if ($arg[0] == 'node' && is_numeric($arg[1])) {
      $node = menu_get_object();
      if (!empty($node)&& !empty($node->nid)) {
        $content_types = variable_get('embed_widgets_content_types', array());
        if (!empty($content_types[$node->type])) {
          $widget = embed_widgets_new('node', $arg[1]);
          if ($widget->status == TRUE) {
            return $widget;
          }
        }
        return FALSE;
      }
    }
    return NULL;
  }
  
}