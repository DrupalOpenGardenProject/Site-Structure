<?php
// $Id: embed_widget_page.inc,v 1.1.2.6 2009/08/02 02:30:07 jtsnow Exp $

/**
 * An object containing all the data and member functions to provide node content to a widget.
 */
class embed_widget_page extends embed_widget {
  
  protected $page;
  protected $path;
   
  static public function info() {
    return array(
      'title' => t('Page'),
      'description' => t('Allows the content of any drupal path to be embedded as a widget.'),
      'name' => 'page',
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
  function __construct($type, $id = NULL, $delta = NULL, $platform = 'html', $format = 'iframe', $cache_id = NULL) {
    parent::__construct($type, $id, $delta, $platform, $format, $cache_id);
    $this->path = base64_decode($this->source_id);
  }
  
  protected function load_content() {
    // Display a page
    // Adapted from print.module.
    //$path = implode('/', $this->params);
    $path = $this->path;

    $path = drupal_get_normal_path($path);

    menu_set_active_item($path);
    $node = new stdClass();
    $node->body = menu_execute_active_handler($path);
    $node->title = $this->title;
    $node->path = $path;
        
    // It may happen that a drupal_not_found is called in the above call
    if (preg_match('/404 Not Found/', drupal_get_headers()) == 1) {
      return FALSE;
    }
    
    // Delete any links area
    $node->body = preg_replace("/\s*<div class=\"links\">.*?<\/div>/sim", "", $node->body);

    $path = empty($node->nid) ? $node->path : "node/$node->nid";
  
    if (isset($node->type)) {
      $node_type = $node->type;
  
      $by_author = ($node->name ? $node->name : variable_get('anonymous', t('Anonymous')));
      $by = t('By %author', array('%author' => $by_author));
      $page["submitted"] = theme_get_setting("toggle_node_info_$node_type") ? $by : "";
  
      $created_datetime = format_date($node->created, 'small');
      $created = t('Created %date', array('%date' => $created_datetime));
      $page["created"] = theme_get_setting("toggle_node_info_$node_type") ? $created : "";
  
      $page["type"] = $node->type;
    }
    else {
      $page["submitted"] = "";
      $page["created"] = "";
      $page["type"] = '';
    }
  
    menu_set_active_item($path);
    $breadcrumb = drupal_get_breadcrumb();
    if (!empty($breadcrumb)) {
      $breadcrumb[] = menu_get_active_title();
      $page["breadcrumb"] = implode(" > ", $breadcrumb);
    }
    else {
      $page["breadcrumb"] = "";
    }
  
    if (module_exists('taxonomy')) {
      $terms = taxonomy_link('taxonomy terms', $node);
      $page["taxonomy"] = theme('links', $terms);
    }
  
    $page["content"] = $node->body;
    
    if ($node->body == MENU_NOT_FOUND || $node->body == MENU_ACCESS_DENIED) {
      return FALSE;
    }
    
    $this->page = $page;
    return TRUE;
  }
  
  protected function view_content() {
    return $this->page['content'];
  }
  
  protected function get_title() {
    return isset($this->page['title']) ? $this->page['title'] : FALSE;
  }
  
  public function check_access() {
    $path = drupal_get_normal_path($this->path);
    $router_item = menu_get_item($path);
    if (!empty($router_item)) {
      return $router_item['access'];
    }
    return FALSE;
  }
  
  static public function path_load() {
    $path = $_GET['q'];
    $widget = embed_widgets_new('page', base64_encode($path));
    if ($widget->status == TRUE) {
      return $widget;
    }
    return FALSE;
  }
  
    
}
