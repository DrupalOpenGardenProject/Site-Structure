<?php
// $Id: embed_widget_view.inc,v 1.1.2.3 2009/07/24 04:19:33 jtsnow Exp $

/**
 * An object containing all the data and member functions to provide view content to a widget.
 */
class embed_widget_view extends embed_widget {
  
  protected $view = NULL;
  
  static public function info() {
    if (module_exists('views')) {
      return array(
        'title' => t('View'),
        'description' => t('Allows Views to be used in embed widgets.'),
        'name' => 'view',
      );
    }
  }
  
  protected function load_content() {
    if (module_exists('views')) {
      if (empty($this->view)) {
        $this->view = views_get_view($this->source_id);
        if ($this->view == NULL) {
          return FALSE;
        }
      }
      return TRUE;
    }
  }
  
  protected function view_content() {
    if (module_exists('views')) {
      $view = $this->view;
      if (!empty($view)) {
        $args = is_array($this->params) ? $this->params : array();
        return $view->preview($this->source_delta, $args);
      }
      return t('The view could not be loaded.');
    }
    drupal_set_message(t('Views module must be enabled to display views in widgets.'), 'warning');
    return t('Error loading content.');;
  }
  
  protected function get_title() {
    return "test";
    return isset($this->view) ? $this->node->title : FALSE;
  }
  
  public function check_access() {
    if (!module_exists('views')) {
      return FALSE;
    }
    $view = $this->view;
    return $view->access($this->source_delta);
  }
  
  static public function path_load() {
    $item = menu_get_item();
    if ($item['page_callback'] == 'views_page') {
      return embed_widgets_new('view', $item['page_arguments'][0]);
    }
    return NULL;
  }
  
}
