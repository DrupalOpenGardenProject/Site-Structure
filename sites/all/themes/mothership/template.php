<?php
// $Id$
/**
 * @file
 * template includes + preprocess
 */

// Auto-rebuild the theme registry during theme development.
if (theme_get_setting('mothership_rebuild_registry')) {
  drupal_rebuild_theme_registry();
}

/**
 * include template overwrites
 */
  include_once './' . drupal_get_path('theme', 'mothership') . '/template/template.functions.php';
  include_once './' . drupal_get_path('theme', 'mothership') . '/template/template.form.php';
  include_once './' . drupal_get_path('theme', 'mothership') . '/template/template.cck.php';
  include_once './' . drupal_get_path('theme', 'mothership') . '/template/template.table.php';
  include_once './' . drupal_get_path('theme', 'mothership') . '/template/template.alternatives.php';
  include_once './' . drupal_get_path('theme', 'mothership') . '/template/template.menu.php';
  include_once './' . drupal_get_path('theme', 'mothership') . '/template/template.views.php';

/**
 * preprocess
 */
function mothership_preprocess(&$vars, $hook) {
  if ($hook == "page") {
  // =======================================| page |========================================
    
    // Add HTML tag name for title tag. so it can shift from a h1 to a div if its the frontpage
    $vars['site_name_element'] = $vars['is_front'] ? 'h1' : 'div';

    // ** ------------------------------------------------------------------------ **
    //  <body> classes
    // ** ------------------------------------------------------------------------ **

    //lets add some more template files 
    if (isset($vars['node'])){
      $vars['template_files'][] = 'page-' . $vars['node']->type;      
    }

    //BOdy classes
    $body_classes = array($vars['body_classes']);

    //do we wanna kill all the goodies that comes from drupal?
    if (theme_get_setting('mothership_cleanup_body_remove')) {
      //clean the body_classes
      $body_classes = " ";
      $body_classes = array(); 

      //front
      if (theme_get_setting('mothership_cleanup_body_front') ){
        $body_classes[] = $vars['is_front'] ? 'front' : '';    
      } 

      if (theme_get_setting('mothership_cleanup_body_front_not') ){
        $body_classes[] = $vars['is_front'] ? '' : 'not-front';    
      } 

      //logged-in
      if (theme_get_setting('mothership_cleanup_body_loggedin') ){
        $body_classes[] = $vars['logged_in'] ? 'logged-in' : '';
      }

      if (theme_get_setting('mothership_cleanup_body_loggedin_not') ){
        $body_classes[] = $vars['logged_in'] ? '' : 'not-logged-in';
      }


      //node-type-[TYPE]
      if (theme_get_setting('mothership_cleanup_body_nodetype') ){
        // If on an individual node page, add the node type.
        if (isset($vars['node']) && $vars['node']->type) {
          $body_classes[] = 'node-type-'. $vars['node']->type;
        }
      }  

      //layout
      if (theme_get_setting('mothership_cleanup_body_layout') ){
        // Add information about the number of sidebars.
        if ($vars['layout'] == 'both') {
          $body_classes[] = 'two-sidebars';
        }
        elseif ($vars['layout'] == 'none') {
          $body_classes[] = 'no-sidebars';
        }
        else {
          $body_classes[] = 'one-sidebar sidebar-'. $vars['layout'];
        }
      }

    }

    $path = drupal_get_path_alias($_GET['q']);
    if($path){
      // Add unique path classes for each page
      if (theme_get_setting('mothership_cleanup_body_add_path')) {
        $body_classes[] = mothership_id_safe('path-' . $path);          
      }
    }

    $path_requist = explode('/', $_SERVER['REQUEST_URI']);
    //pathlast
    if (theme_get_setting('mothership_cleanup_body_add_last') AND !$vars['is_front']) {
      $body_classes[] = mothership_id_safe('pathlast-' . end($path_requist) );
    }

    if (theme_get_setting('mothership_cleanup_body_pagearg_one') ){  
      $body_classes[] = mothership_id_safe('page-' . $path_requist['1']);
    }  
    
  
    //adds class user-foobar without user id
    if(arg(0) == "user"){
      $body_classes[] = mothership_id_safe( $path, 'remove-numbers');
    }

    //class action-node
    if (theme_get_setting('mothership_cleanup_body_actions')) {
      if (arg(0) == 'node') {
        if (arg(1) == 'add') {
          $body_classes[] = 'action-node-add';
        }
        elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
          $body_classes[] = 'action-node-' . arg(2); // Add 'action-node-edit' or 'action-node-delete'
        }
      }
    }
     

    //is the admin module active
    if (!empty($vars['admin']) AND theme_get_setting('mothership_cleanup_body_admin')){
      $body_classes[] = "adminmenu";
    }

    $vars['body_classes'] = implode(' ', $body_classes); // Concatenate with spaces
//    kpr($vars['body_classes']);
    // ** ------------------------------------------------------------------------ **
    // style sheets load order & ie fix
    // kudos to al-steffen for figuring this out :)
    // http://pingv.com/blog/al-steffen/2009/using-themes-info-file-add-order-conditions-stylesheets

    // conditional styles
    // xpressions documentation  -> http://msdn.microsoft.com/en-us/library/ms537512.aspx

    // syntax for .info
    // top stylesheets[all][] = style/reset.css
    // ie stylesheets[ condition ][all][] = ie6.css
    // ------------------------------------------------------------------------

    if (theme_get_setting('mothership_stylesheet_load_order') OR theme_get_setting('mothership_stylesheet_conditional')) {
      GLOBAL $theme_info;
      // Get the path to the theme to make the code more efficient and simple.
      $path = drupal_get_path('theme', $theme_info->name);
    }

    if (theme_get_setting('mothership_stylesheet_load_order')) {
      // Check if there are stylesheets to be placed at the top of the stack.
      if (isset($theme_info->info['top stylesheets'])) {
        $top_css = array();
        // Format the stylesheets to work with drupal_get_css().
        foreach ($theme_info->info['top stylesheets'] as $media => $styles) {
          foreach ($styles as $style) {
            $top_css[$media][$path . '/' . $style] = TRUE;
          }
          // Add the stylesheets to the top of the proper media type.
          array_unshift($vars['css'][$media], $top_css[$media]);
        }
        // Replace $styles with the new string.
        $vars['styles'] = drupal_get_css($vars['css']);
      }
    }

    // Check for IE conditional stylesheets.
    if (isset($theme_info->info['ie stylesheets']) AND theme_get_setting('mothership_stylesheet_conditional')) {
      $ie_css = array();

      // Format the array to be compatible with drupal_get_css().
      foreach ($theme_info->info['ie stylesheets'] as $condition => $media) {
        foreach ($media as $type => $styles) {
          foreach ($styles as $style) {
            $ie_css[$condition][$type]['theme'][$path . '/' . $style] = TRUE;
          }
        }
      }
      // Append the stylesheets to $styles, grouping by IE version and applying
      // the proper wrapper.
      foreach ($ie_css as $condition => $styles) {
        $vars['styles'] .= '<!--[' . $condition . ']>' . "\n" . drupal_get_css($styles) . '<![endif]-->' . "\n";
      }
    }


  // =======================================| /PAGE |========================================
  }
  elseif ($hook == "node") {
  // =======================================| NODE |========================================

    // create css classes for the node
    $classes =array();
    //sticky
    if (theme_get_setting('mothership_cleanup_node_sticky')) {
      if ($vars['sticky']) {
        $classes[] = 'sticky';
      }
    }
    //published
    if (theme_get_setting('mothership_cleanup_node_published')) {
      if (!$vars['status']) {
        $classes[] = 'node-unpublished';
        $vars['unpublished'] = TRUE;
      }
      else {
        $vars['unpublished'] = FALSE;
      }
    }
    //promoted
    if (theme_get_setting('mothership_cleanup_node_promoted')) {
      if ($vars['promote']) {
        $classes[] = 'promoted';
      }
    }

    //node or teaser Class for node type: "node-page", "node-story", "node-teaser-page","node-teaser-story",
    if ($vars['teaser']) {
      if (theme_get_setting('mothership_cleanup_node_node')) {
        $classes[] = 'node-teaser';
      //  $classes[] = 'node';
      }
      if (theme_get_setting('mothership_cleanup_node_content_type')) {
        $classes[] = 'node-teaser-' . $vars['type'];
        $classes[] = 'node-' . $vars['type'];
      }
    }
    else{
      if (theme_get_setting('mothership_cleanup_node_node')) {
        $classes[] = 'node';
      }
      if (theme_get_setting('mothership_cleanup_node_content_type')) {
        $classes[] = 'node-' . $vars['type'];
      }
    }
    //clearfix
    if (theme_get_setting('mothership_cleanup_node_clearfix')) {
        $classes[] = 'clearfix';
    }  

    //skinr
    if (module_exists('skinr') ) {
      $classes[] = $vars['skinr'];
    }
    
    $vars['classes'] = implode(' ', $classes);
    
    // css id for the node
    if (theme_get_setting('mothership_cleanup_node_id')) {
      $id_node = array();
      $id_node[] = 'node';
      $id_node[] =  $vars['nid'];
      if ($vars['nid']) {
        $vars['id_node'] = implode(' ', $id_node);
        $vars['id_node'] =  mothership_id_safe($vars['id_node']);
      }

    }

    //Add 2 regions to the node?
    if (theme_get_setting('mothership_cleanup_node_regions') AND $vars['page'] == TRUE) {
      if ($vars['page'] == TRUE) {
        $vars['node_region_one'] = theme('blocks', 'node_region_one');
        $vars['node_region_two'] = theme('blocks', 'node_region_two');
      }
    }

    //-----------------------------------------------------
    //lets grap $links array and throw em into some vars we actually can use
    //comments
    if ($vars['node']->links['comment_comments']) {
        $vars['link_comment'] =  l($vars['node']->links['comment_comments']['title'], $vars['node']->links['comment_comments']['href'],
          array(
            'attributes' => array('class' => 'comment', 'title' => $vars['node']->links['comment_comments']['attributes']['title']),
            'fragment' => $vars['node']->links['comment_comments']['fragment']
          )
      );
    }

    //comment_add
    if ($vars['node']->links['comment_add']) {
      $vars['link_comment_add'] =  l($vars['node']->links['comment_add']['title'], $vars['node']->links['comment_add']['href'],
      array(
          'attributes' => array('class' => 'comment-add', 'title' => $vars['node']->links['comment_add']['attributes']['title']),
          'fragment' => 'comment-form'
        )
      );
    }

    //attachments
    if ($vars['node']->links['upload_attachments']) {
      $vars['link_attachments'] =  l($vars['node']->links['upload_attachments']['title'], $vars['node']->links['upload_attachments']['href'], array('attributes' => array('class' => 'attachments','title' => $vars['node']->links['upload_attachments']['attributes']['title'] )));
    }

    //read more
    if ($vars['node']->links['node_read_more']) {
      $vars['link_read_more'] =  l($vars['node']->links['node_read_more']['title'], $vars['node']->links['node_read_more']['href'], array('attributes' => array('class' => 'read-more','title' => $vars['node']->links['node_read_more']['attributes']['title'] )));
    }

    //statistics_counter
    if ($vars['node']->links['statistics_counter']) {
      $vars['statistics_counter'] = $vars['node']->links['statistics_counter']['title'];
    }



    return $vars['template_files'];

  // =======================================| /NODE |========================================
  }
  elseif ($hook == "block") {
  // =======================================| BLOCK |========================================
    //  classes for blocks.
    $block = $vars['block'];
    $classes = array();

    if (theme_get_setting('mothership_cleanup_block_block')) {
      $classes[] = 'block';
    }

    if (theme_get_setting('mothership_cleanup_block_module')) {
      $classes[] = 'block-' . mothership_id_safe($block->module);
    }

    if (theme_get_setting('mothership_cleanup_block_region_zebra')) {
      $classes[] = 'region-' . $vars['block_zebra'];
    }

    if (theme_get_setting('mothership_cleanup_block_region_count')) {
      $classes[] = 'region-count-' . mothership_id_safe($vars['block_id']);
    }

    if (theme_get_setting('mothership_cleanup_block_zebra')) {
      $classes[] = $vars['zebra'];
    }

    if (theme_get_setting('mothership_cleanup_block_count')) {
      $classes[] = 'count-' . mothership_id_safe($vars['id']);
    }

    if (theme_get_setting('mothership_cleanup_block_front')) {
      if ($vars['is_front']) {
        $classes[] = 'block-front';
      }
    }

    if (theme_get_setting('mothership_cleanup_block_loggedin')) {
      if ($vars['logged_in']) {
        $classes[] = 'block-logged-in';
      }
    }

    //skinr
    if( module_exists(skinr) ) {
        $classes[] = $vars['skinr'];
    }

    // Render block classes.
    $vars['classes'] = implode(' ', $classes);
    // $vars['classes'] =  mothership_id_safe($vars['classes']);
    // id for block
    if (theme_get_setting('mothership_cleanup_block_id')) {
      $id_block = array();
      $id_block[] = 'block';
      $id_block[] =  $block->module ;

      if ($block->delta) {
        $id_block[] = $block->delta;
      }

      $vars['id_block'] = implode(' ', $id_block);
      $vars['id_block'] =  mothership_id_safe($vars['id_block']);
    }


  // =======================================| /BLOCK |========================================
  }
  elseif ($hook == "comment") {
  // =======================================| COMMENT |========================================
    //dsm($vars);
    // Add an "unpublished" flag.
    $vars['unpublished'] = ($vars['comment']->status == COMMENT_NOT_PUBLISHED);

    // If comment subjects are disabled, don't display them.
    if (variable_get('comment_subject_field_' . $vars['node']->type, 1) == 0) {
      $vars['title'] = '';
    }

    // Special classes for comments.
    $classes = array();

    if (theme_get_setting('mothership_cleanup_comment_comment')) {
      $classes[] = 'comment';
    }

    if ($vars['comment']->new AND theme_get_setting('mothership_cleanup_comment_new')) {
      $classes[] = 'comment-new';
    }

    if (theme_get_setting('mothership_cleanup_comment_status')) {
      $classes[] = $vars['status'];
    }

    if (theme_get_setting('mothership_cleanup_comment_zebra')) {
      $classes[] = $vars['zebra'];
    }
    //first last
    if (theme_get_setting('mothership_cleanup_comment_first')) {
      if ($vars['id'] == 1) {
        $classes[] = 'first';
      }
    }

    if (($vars['id'] == $vars['node']->comment_count) AND theme_get_setting('mothership_cleanup_comment_last')) {
      $classes[] = 'last';
    }

    if (theme_get_setting('mothership_cleanup_comment_user')) {
      if ($vars['comment']->uid == 0) {
        // Comment is by an anonymous user.
        $classes[] = 'by-anonymous';
      }
      else {
        if ($vars['comment']->uid == $vars['node']->uid) {
          // Comment is by the node author.
          $classes[] = 'by-author';
        }
        if ($vars['comment']->uid == $GLOBALS['user']->uid) {
          // Comment was posted by current user.
          $classes[] = 'by-me';
        }
      }
    }

    if (theme_get_setting('mothership_cleanup_comment_front')) {
      if ($vars['is_front']) {
        $classes[] = 'front';
      }
    }

    if (theme_get_setting('mothership_cleanup_comment_loggedin')) {
      if ($vars['logged_in']) {
        $classes[] = 'logged-in';
      }
    }

    $vars['classes'] = implode(' ', $classes);
    // =======================================| /COMMENT |========================================
  }
  elseif ($hook == "comment_wrapper"){
    // =======================================| COMMENTWRAPPER |========================================

    $id_commentwrap = array();
    $id_commentwrap[] = 'comments';
    $vars['id_commentwrap'] = implode(' ', $id_commentwrap);
    $vars['id_commentwrap'] =  mothership_id_safe($vars['id_commentwrap']);

    $classes = array();  
    //skinr
    if( module_exists(skinr) ) {
        $classes[] = $vars['skinr'];
    }

    $vars['classes'] = implode(' ', $classes);    
    // =======================================| COMMENTWRAPPER |========================================
  }


}
