<?php
// $Id$
/**
 * @file
 * menu mothership overwrites
 */

function mothership_menu_tree($tree) {
  if (theme_get_setting('mothership_cleanup_menu_baseclass')) {
    return '<!--menu-->' . "\n" . '  <ul class="menu">' . "\n" . $tree . '  </ul>' . "\n  <!--/menu-->\n" ;
  }
  else{
    return '<!--menu-->  <ul>' . "\n" . $tree . "\n" . "  </ul>\n";
  }

}

function mothership_menu_item($link, $has_children, $menu = '', $in_active_trail = FALSE, $extra_class = NULL) {

    if (theme_get_setting('mothership_cleanup_menu_leafs')) {
      $class = ($menu ? 'expanded' : ($has_children ? 'collapsed' : 'leaf'));
    }

    if (!empty($extra_class) AND theme_get_setting('mothership_cleanup_menu_classes_first_last')) {
      if ($class) {
        $class .= ' '. $extra_class;
      }
      else{
        $class .= $extra_class;
      }

    }

    if ($in_active_trail AND theme_get_setting('mothership_cleanup_menu_classes_active')) {
      $class .= ' active-trail';
    }

    if ($class) {
      return '    <li class="'. $class .'">'. $link . $menu ."</li>\n";
    }
    else{
      return '    <li>'. $link . $menu ."</li>\n";
    }


}

function mothership_menu_local_task($link, $active = FALSE) {
  if (theme_get_setting('mothership_cleanup_menu_classes_active')) {
    return '  <li '. ($active ? 'class="active" ' : '') .'>'. $link ."</li>\n";
  }
  else{
    return '  <li>'. $link ."</li>\n";
  }
}


/*  TODO remove the menu-xxx classes from primary /secundary */
function mothership_links($links, $attributes = array('class' => 'links')) {
// dsm($links);
  $output = '';

  if (count($links) > 0) {
    if (theme_get_setting('mothership_cleanup_links_baseclass')) {
      $output = '  <ul'. drupal_attributes($attributes) .'>';
    }
    else{
      $output = '  <ul>';
    }
    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = $key;
      if (theme_get_setting('mothership_cleanup_menu_classes_first_last')) {
        // Add first, last and active classes to the list of links to help out themers.
        if ($i == 1) {
          $class .= ' first';
        }
        if ($i == $num_links) {
          $class .= ' last';
        }
      }

      if (theme_get_setting('mothership_cleanup_menu_classes_active')) {
        if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))) {
          $class .= ' active';
        }
      }

      if (isset($link['href'])) {
        // add active class for containing <li> and <a> if active-trail is set on the link itself
        if (theme_get_setting('mothership_menu_classes_active')) {
          if (strpos($link['attributes']['class'], 'active-trail') !== FALSE && strpos($class, 'active') === FALSE) {
            $class .= ' active';
            $link['attributes']['class'] .= ' active';
          }
        }
        // Pass in $link as $options, they share the same keys.
        $link = l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $link = '<span'. $span_attributes .'>'. $link['title'] .'</span>';
      }

      $i++;

//      array_search($class) ;
      $output .= '  <li'. drupal_attributes(array('class' => $class)) .'>';
      $output .= $link;
      $output .= "</li>\n";
    }

    $output .= '</ul>' . "\n";
  }
  return $output;
}