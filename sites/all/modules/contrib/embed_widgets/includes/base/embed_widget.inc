<?php
// $Id: embed_widget.inc,v 1.30.2.23 2009/09/09 03:08:02 jtsnow Exp $

/**
 * An object containing all the data and member functions required for a widget.
 */
class embed_widget {
  public $wid;
  public $title;
  public $description;
  public $status = TRUE;
  
  public $format = 'iframe';
  public $platform = 'html';
  
  public $settings = array();
  public $params = array();
  
  public $source_type = NULL;
  public $source_id = NULL;
  public $source_delta = NULL;
  
  public $module = NULL;
  
  public $cache_id;
  
  protected $default = FALSE;
  
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
  function __construct($type = NULL, $id = NULL, $delta = NULL, $platform = 'html', $format = 'iframe', $cache_id = NULL) {
    //if (!isset($type)) {
      // Set default widget
    //}
    if (empty($id)) {
      $decoded = $this->decode($type);
      $type = $decoded['type'];
      $id = $decoded['id'];
      $delta = $decoded['delta'];
      $format = $decoded['format'];
      $platform = $decoded['platform'];
      $cache_id = $decoded['cache_id'];
    }

    $this->format = isset($format) ? $format : $this->format;
    $this->platform = isset($platform) ? $platform : $this->platform;
    $this->source_type = $type;
    $this->source_id = $id;
    $this->source_delta = $delta;
    $this->cache_id = $cache_id;
    
    $enabled_types = variable_get('embed_widgets_widget_types', array_fill_keys(array('node', 'block', 'view'), 1));
    if (!empty($enabled_types[$this->source_type])) {
      $this->load();  // Don't load on construct?
    }
    else {
      $this->default = TRUE;
    }
    
    if (empty($this->settings)) {
      $this->settings = embed_widget::default_settings();
    }
    
    $this->get_args();
  }
  
  /**
   * Saves widget to the database.
   *
   * @return
   *   Either SAVED_UPDATED or SAVED_NEW.
   */
  public function save() {
    if ((isset($this->wid) && is_numeric($this->wid)) || $this->lookup_hash() !== FALSE) {
      $result = db_query("UPDATE {embed_widgets} SET type = '%s', foreign_id = '%s', delta = '%s',  title = '%s', description = '%s', status = %d, settings = '%s' WHERE hash = '%s'", $this->source_type, $this->source_id, $this->source_delta, $this->title, $this->description, $this->status, serialize($this->settings), $this->encode());
      if (db_affected_rows() > 0) {
        $return = SAVED_UPDATED;
        $this->widget_list($this, 'update'); // Update cache.
      }
    }
    else {
      db_query("INSERT INTO {embed_widgets} (hash, type, foreign_id, delta, title, description, status, settings) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', %d, '%s')", $this->encode(), $this->source_type, $this->source_id, $this->source_delta, $this->title, $this->description, $this->status, serialize($this->settings));
      $this->wid = db_last_insert_id("embed_widgets", "wid");

      if (db_affected_rows() > 0) {
        $return = SAVED_NEW;
        $this->widget_list($this, 'update'); // Update cache.
      }
    }
    return isset($return)? $return : FALSE;
  }
  
  /**
   * Loads a widget object.
   *
   * @param $wid
   *   Numeric widget ID.
   * @return
   *   TRUE on success; FALSE on failure.
   */
  public function load() {
    $wid = $this->encode();
    if (!is_string($wid) || !$this->decode($wid)) {
      return FALSE;
    }
    if (isset($this->cache_id) && $this->cache_load()) {
      return TRUE;
    }
    
    $embed_widget = $this->widget_list($wid);
    if (empty($embed_widget)) {
      $embed_widget = embed_widget::db_load($wid);
    }
    
    if (isset($embed_widget->wid)) {
      $this->wid = $embed_widget->wid;
      $this->source_type = $embed_widget->type;
      $this->source_id = $embed_widget->foreign_id;
      $this->source_delta = $embed_widget->delta;
      $this->title = $embed_widget->title;
      $this->description = $embed_widget->description;
      $this->status = $embed_widget->status;
      $this->settings = $embed_widget->settings;

      return TRUE;
    }
    else {
      // TODO: Load widget default values.
      $this->settings = embed_widget::default_settings();
      return FALSE;
    }
  }
  
  /**
   * Loads widget information from the database.
   *
   * @param $wid
   *   Numeric widget ID to be loaded or widget object to be cached.
   * @param $refresh
   *   If TRUE, refreshes cache of loaded widgets.
   * @return
   *   A widget object from the database.
   */
  protected static function db_load($hash) {
    if (is_string($hash)) {
      $result = db_query("SELECT * FROM {embed_widgets} WHERE hash = '%s'", $hash);
      if ($result) {
        $embed_widget = db_fetch_object($result);
      }
      if (isset($embed_widget->wid)) {
        $embed_widget->settings = unserialize($embed_widget->settings);
        return $embed_widget;
      }
    }
    return FALSE;
  }
  
  /**
   * Loads widget information from the cache.
   *
   * @param $cache_id
   *   A cache id.
   */
  protected function cache_load() {
    $cache = cache_get('embed_widgets_' . $this->cache_id);
    //$embed_widget = isset($cache->data) ? $cache->data : NULL;
    if (!empty($cache->data)) {
      foreach ($cache->data as $attribute => $value) {
        $this->{$attribute} = $value;
      }
      return TRUE;
    }
    return FALSE;
  }
  
  /**
   * Save a widget to the persistent cache.
   *
   * @param $cache_id
   *   A Form API form build ID.
   */
  public function cache($cache_id) {
    $this->cache_id = $cache_id;
    cache_set('embed_widgets_' . $cache_id, $this, 'cache', CACHE_TEMPORARY);
  }
  
  /**
   * Deletes widget from the database.
   *
   * @return
   *   TRUE on success; FALSE on failure.
   */
  public function delete() {
    db_query("DELETE FROM {embed_widgets} WHERE hash = '%s'", $this->encode());
    $this->widget_list($this->encode(), 'delete');
    return (db_affected_rows() > 0);
  }

  /**
   * Maintains a static cache of widgets that have been loaded from the
   * database.
   *
   * @param $hash
   *   An encoded widget hash string.
   * @param $action
   *   Possible values are 'get', 'update', and 'delete'.
   * @param $refresh
   *   Set to TRUE if the static cache should be wiped.
   * @return
   *   If 'get' or 'update', the widget object corresponding to the hash will
   *   be returned.
   */
  protected static function widget_list($hash, $action = 'get', $refresh = FALSE) {
    static $widgets = array();
    if ($refresh) {
      $widgets = array();
    }
    
    if ($action == 'get') {
      return $widgets['hash'];
    }
    elseif ($action == 'update' && is_object($hash)) {
      $widgets[$hash->encoded] = $hash;
      return $widgets[$hash->encoded] = $hash;
    }
    elseif ($action == 'delete') {
      unset($widgets[$hash]);
    }
  }
  
  protected function lookup_hash() {
    if ($this->source_delta == NULL) {
      $result = db_query("SELECT hash FROM {embed_widgets} WHERE type = '%s' AND foreign_id = '%s'", $this->source_type, $this->source_id);
    }
    else {
      $result = db_query("SELECT hash FROM {embed_widgets} WHERE type = '%s' AND foreign_id = '%s' AND delta = '%s'", $this->source_type, $this->source_id, $this->source_delta);
    }
    $hash = db_result($result);
    if ($hash) {
      return $hash;
    }
    return FALSE;
  }
  
  static public function lookup($type, $id, $delta = NULL) {
    if ($type == 'node' && is_object($id)) {
      $id = $id->nid;
    }
    if ($delta == NULL) {
      $result = db_query("SELECT hash FROM {embed_widgets} WHERE type = '%s' AND foreign_id = '%s'", $type, $id);
    }
    else {
      $result = db_query("SELECT hash FROM {embed_widgets} WHERE type = '%s' AND foreign_id = '%s' AND delta = '%s'", $type, $id, $delta);
    }
    $hash = db_result($result);
    if ($hash) {
      return embed_widgets_load($hash);
    }
    return FALSE;
  }

   
  /**
   * Encrypts widget information to be placed securely in a URL.
   *
   * @return
   *   The encoded widget as a string.
   */
  public function encode() {
    $this->encoded = $this->hash($this->source_type . $this->format . $this->platform) . '-' . $this->source_id;
    
    if (isset($this->source_delta) && $this->source_delta != '') {
      $this->encoded .= '-' . $this->source_delta;
    }
    if (isset($this->cache_id)) {
      $this->encoded .= '_._' . $this->cache_id;
    }
    return $this->encoded;
  }
  
  /**
   * Decrypt an encrypted widget and loads the widget object.
   *
   * @param $encoded_widget
   *   Encrypted widget information as a string.
   * @return
   *   TRUE on success; FALSE on failure.
   */
  public static function decode($encoded_widget) {
    // Decode widget.
    list($encoded_widget, $cache_id) = explode("_._", $encoded_widget, 3);
    list($hash, $id, $delta) = explode("-", $encoded_widget, 3);
    
    $info = embed_widgets_get_info();
    $hashes = $info['hashes'];

    if (isset($hashes[$hash]) && $id) {
      $hashes[$hash]['id'] = $id;
      $hashes[$hash]['delta'] = $delta;
      $hashes[$hash]['cache_id'] = $cache_id;
      return $hashes[$hash];
    }
    return FALSE;
  }
  
  /**
   * Helper function used for encoding and decoding widgets.
   *
   * @param $source_type
   *   The type of widget. i.e. 'node', 'block', etc.
   * @return
   *   A hash string.
   */
  public static function hash($source_type) {
    global $cookie_domain, $base_path;
    $hash = md5($source_type . $base_path . $cookie_domain);
    return $hash;
  }
  
 /**
   * Generate the content for this widget.
   *
   * @return
   *   The HTML content to be displayed in the widget.
   */
  public function build() {
    $content = array();
    
    if (!empty($this->default) || $this->status == FALSE || !$this->load_content()) {
      $content['title'] = $this->default_title();
      $content['content'] = $this->default_content();
      drupal_set_title($content['title']);
      return $content;
    }
    else {
      $this->title = empty($this->title) ? $this->get_title() : $this->title;
      $content['title'] = $this->title;
      $content['content'] = $this->view_content();
    }
    
    if (!$this->check_access()) {
      // Permission denied. Display login form if user is not logged in.
      $logged_in = user_is_logged_in();
      $content['title'] = 'Log in';
      $content['content'] = $logged_in ? t('You do not have permission to view this content.') : t('You must login to view this content.');
      if (!$logged_in) {
        $login_block = module_invoke('user', 'block', 'view', 0);
        $content['content'] .= $login_block['content'];
      }
    }
    drupal_set_title($content['title']);
    
    return $content;
  }
  
  protected function view_content() {
    return "none";
  }
  
  protected function load_content() {
    return true;
  }
  
  protected function get_title() {
    return "Widget Title";
  }
  
  public function check_access() {
    return true;
  }
  
  /**
   * Get a widget corresponding to a path.
   *
   * @return
   *   Returns a widget object if the path corresponds to the widget type.
   *   Returns FALSE if the path corresponds to the widget type, but no widget exists for that path.
   *   Returns NULL if the current path does not correspond to the widget type.
   */
  static public function path_load() {
    return NULL;
  }

    
  /**
   * Get the URL to a widget's embed file.
   *
   * @param $filename
   *   The filename to attach to the end of the URL.
   * @param $params
   *   Additional parameters to add to the URL.
   * @return
   *   The URL to a widget's embed file as a string.
   */
  public function get_embed_url() {
    $path = 'embed-widgets/' . $cache . $this->encode() . '/embed/' . implode('/', $this->params);
    return url($path, array('absolute' => TRUE));
  }
  
  /**
   * Get the URL to a widget's content.
   *
   * @return
   *   The URL to a widget's content as a string.
   */
  public function get_content_url() {
    $path = 'embed-widgets/' . $cache . $this->encode() . '/content/' . implode('/', $this->params);
    return url($path, array('absolute' => TRUE));
  }
  
  /**
   * Get the URL to a widget's platform-specific file.
   *
   * @return
   *   The URL to a widget's platform-specific file.
   */
  public function get_platform_url() {
    $path = 'embed-widgets/' . $this->encode() . '/platform/' . implode('/', $this->params);
    return url($path, array('absolute' => TRUE));
  }
  
  /**
   * Get the URL to a widget's share page.
   *
   * @return
   *   The URL to a widget's share page.
   */
  public function get_share_url() {
    global $widgets_mode;
    $path = 'embed-widgets/' . $this->encode() . '/share/' . implode('/', $this->params);
    if (empty($widgets_mode)) {
      return url($path, array('absolute' => TRUE));
    }
    return url($path, array('absolute' => TRUE, 'query' => array('widgets_mode' => $widgets_mode)));
  }
  
  /**
   * Get the embed code for this widget.
   *
   * @return
   *   The HTML code required to embed this widget.
   */
  public function get_code($no_script = FALSE) {
    return call_user_func($this->platform . '::code', $this, $no_script);
  }
  
  /**
   * Get the link for this widget.
   *
   * @return
   *   The link necessary to embed the widget in its platform..
   */
  public function get_link($no_script = FALSE) {
    $info = call_user_func($this->platform . '::info');
    $url = call_user_func($this->platform . '::link', $this);
    return l($info['title'], $url);
  }
  
  /**
   * Get the URL to a widget's platform-specific file.
   *
   * @return
   *   The URL to a widget's platform-specific file.
   */
  public function get_platform_file() {
    $this->build();
    return call_user_func($this->platform . '::platform_file', $this);
  }
  
  /**
   * Add CSS specific to widget's format.
   */
  public function add_css() {
    $info = call_user_func($this->format . '::info');
    foreach ($info['css'] as $css_file) {
      drupal_add_css($info['path'] . '/' . $css_file);
    }
  }
  
  /**
   * Set a persistent variable for this widget.
   *
   * @param $name
   *   The name of the variable being set.
   * @param $value
   *   The value of the variable being set.
   */
  public function set_variable($name, $value) {
      $this->settings[$name] = $value;
  }
  
  /**
   * Get a persistent variable for this widget.
   *
   * @param $name
   *   The name of the variable to return.
   * @return
   *   The value of the requested variable.
   */
  public function get_variable($name) {
      return $this->settings[$name];
  }
  
  /**
   * Get settings for this widget.
   *
   * @return
   *   The value of the requested variable.
   */
  public function get_settings() {
      return $this->settings;
  }
  
  protected function get_args() {
    global $widgets_mode;
    
    if (isset($widgets_mode)) {
      $args = arg();
      if ($args[0] == 'embed-widgets') {
        if (count($args) > 3) {
          array_shift($args);
          array_shift($args);
          array_shift($args);
          $this->params = $args;
        }
      }
    }
  }
  
  public function default_title() {
    return check_plain(variable_get('embed_widgets_default_title', t('Content unavailable')));
  }
  
  public function default_content() {
    $filter = variable_get('embed_widgets_default_content_filter', FILTER_FORMAT_DEFAULT);
    return check_markup(variable_get('embed_widgets_default_content', t('The content for this widget is no longer available.')), $format);
  }
  
  static public function default_settings($settings = NULL, $refresh = FALSE) {
    if ($refresh) {
      variable_del('embed_widgets_widget_defaults');
    }
    else if ($settings && is_array($settings)) {
      return variable_set('embed_widgets_widget_defaults', $settings);
    }
    return variable_get('embed_widgets_widget_defaults', array('width' => 300, 'height' => 300));
  }
  
  static public function widget_attributes_form(embed_widget $widget = NULL) {
    $form['status'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enabled'),
      '#default_value' => is_object($widget) ? $widget->status : NULL,
      '#description' => t('Uncheck this box to disable the widget for this @type.', array('@type' => $widget->source_type)),
    );
    $form['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => is_object($widget) ? $widget->title : NULL,
      '#size' => 30,
      '#maxlength' => 255,
      //'#required' => TRUE,
      '#description' => t('The widget title.'),
    );
    $form['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#default_value' => is_object($widget) ? $widget->description : NULL,
      '#size' => 50,
      '#maxlength' => 255,
      '#description' => t('A description of the widget, its content, and/or its purpose.'),
    );
    return $form;
  }
  
  static public function widget_settings_form($settings = NULL) {
    if (!$settings) {
      $settings = embed_widget::default_settings();
    }
    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $settings['width'],
      '#size' => 4,
      '#maxlength' => 4,
      '#field_suffix' => 'pixels',
      '#required' => TRUE,
      '#description' => t('The width of the widget in pixels.'),
    );
    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => $settings['height'],
      '#size' => 4,
      '#maxlength' => 5,
      '#field_suffix' => 'pixels',
      '#required' => TRUE,
      '#description' => t('The height of the widget in pixels.'),
    );
    return $form;
  }
}
