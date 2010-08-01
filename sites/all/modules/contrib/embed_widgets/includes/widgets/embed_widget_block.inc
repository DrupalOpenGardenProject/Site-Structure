<?php
// $Id: embed_widget_block.inc,v 1.1.2.3 2009/07/25 06:29:31 jtsnow Exp $

require_once drupal_get_path('module', 'embed_widgets') ."/embed_widgets.module";
spl_autoload_register('embed_widgets_autoload');

/**
 * An object containing all the data and member functions to provide block content to a widget.
 */
class embed_widget_block extends embed_widget {
  
  protected $block = NULL;
  
  static public function info() {
    return array(
      'title' => t('Block'),
      'description' => t('Allows any block to be embedded as a widget.'),
      'name' => 'block',
    );
  }
  
  protected function load_content() {
    if (empty($this->block)) {
      $this->block = module_invoke($this->source_id, 'block', 'view', $this->source_delta);
    }
    return isset($this->block['content']);
  }
  
  protected function view_content() {
    return isset($this->block['content']) ? $this->block['content'] : FALSE;
  }
  
  protected function get_title() {
    return isset($this->block['subject']) ? $this->block['subject'] : FALSE;
  }
  
  public function check_access() {
    global $user;
    $rids = array_keys($user->roles);
    return db_result(db_query(db_rewrite_sql("SELECT DISTINCT b.status FROM {blocks} b LEFT JOIN {blocks_roles} r ON b.module = r.module AND b.delta = r.delta WHERE b.module = '%s' AND b.delta = '%s' AND (r.rid IN (". db_placeholders($rids) .") OR r.rid IS NULL) ORDER BY b.region, b.weight, b.module", 'b', 'bid'), $this->source_id, $this->source_delta, $rids));
  }
  
  static public function admin_settings_form() {
    $form = array();
    $form['block'] = array(
      '#type' => 'fieldset',
      '#title' => t('Block Widgets'),
      '#collapsible' => TRUE,
    );
    $form['block']['embed_widgets_block_append_link'] = array(
      '#type' => 'checkbox',
      '#title' => t('Append widget link to blocks.'),
      '#description' => t('If this box is checked the "Share this widget" link will be appended to block content. Otherwise, you may add the link variable to your block template file(s) manually.'),
      '#default_value' => variable_get('embed_widgets_block_append_link', FALSE),
    );
    return $form;
  }
  
}
