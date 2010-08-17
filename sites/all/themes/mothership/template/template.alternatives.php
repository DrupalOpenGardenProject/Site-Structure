<?php
// $Id$
/**
 * @file
 * template alternative functions
 */

/**
 * removes the  <div> around  the list and add the item-list class into the ul/ol
 * if it has a $title added then the surrounding div will be
 * zebra stribes are added to the item list if the settings are set
 * besides of having ul/ol list
 * its now possible to  create liste based on
 * span
 * div-span
 */
function mothership_item_list($items = array(), $title = NULL, $type = 'ul', $attributes = NULL) {
  //fix if the type is div-span
  if ($type == "div-span") {
    $type = "div";
    $item_type = "div-span";
  }
  else{
    $item_type = $type;
  }

  $attributes['class'] .= " item-list";
  //test if we have an title then add the div.item-list around the list
  if (isset($title)) {
    $output = '<div class="item-list">';
    if ($item_type == "span") {
      $output .= '<span class="title">'. $title .'</span>';
    }
    else{
      $output .= '<h3>'. $title .'</h3>';
    }

  }


  if (!empty($items)) {
    $output .= "<$type". drupal_attributes($attributes) .'>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }

      if (count($children) > 0) {
        $data .= theme_item_list($children, NULL, $type, $attributes); // Render nested list
      }

//      $mothership_cleanup_itemlist = theme_get_setting('mothership_cleanup_itemlist');
    // zebra stribes
      if (theme_get_setting('mothership_item_list_zebra')) {
        if ($i & 1) {
          $attributes['class'] = empty($attributes['class']) ? 'odd' : ($attributes['class'] .' odd');
        }
        else {
          $attributes['class'] = empty($attributes['class']) ? 'even' : ($attributes['class'] .' even');
        }
      }
      //removed first / last fromt the item list?
      if (theme_get_setting('mothership_item_list_first_last')) {
        if ($i == 0) {
          $attributes['class'] .= ' first';
        }
        if ($i == $num_items - 1) {
          $attributes['class'] .= ' last';
        }
      }

      //is it a li or a span or a div ?
      if ($item_type == "ul" OR $item_type == "ol") {
        $output .= '<li'. drupal_attributes($attributes) .'>'. $data ."</li>\n";
      }
      elseif ($item_type == "span" OR $item_type == "div-span" ) {
        $output .= '<span'. drupal_attributes($attributes) .'>'. $data ."</span>\n";
      }
      elseif ($item_type == "div") {
        $output .= '<div'. drupal_attributes($attributes) .'>'. $data ."</div>\n";
      }
      else{
        $output .= '<li'. drupal_attributes($attributes) .'>'. $data ."</li>\n";
      }

    }
    $output .= "</$type>";
  }
  if (isset($title)) {
    $output .= '</div>';
  }
  return $output;
}


/**
 * username
 * lets get rid of tht not verified
 */
function mothership_username($object) {

  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    if (drupal_strlen($object->name) > 20) {
      $name = drupal_substr($object->name, 0, 15) .'...';
    }
    else {
      $name = $object->name;
    }

    if (user_access('access user profiles')) {
      $output = l($name, 'user/'. $object->uid, array('attributes' => array('title' => t('View user profile.'))));
    }
    else {
      $output = check_plain($name);
    }
  }
  elseif ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if (!empty($object->homepage)) {
      $output = l($object->name, $object->homepage, array('attributes' => array('rel' => 'nofollow')));
    }
    else {
      $output = check_plain($object->name);
    }
    if (theme_get_setting('mothership_cleanup_user_verified')) {
      $output .= '<span class="not-verified">('. t('not verified') .'</span>)';
    }
  }
  else {
    $output = check_plain(variable_get('anonymous', t('Anonymous')));
  }

  return $output;
}


function mothership_box($title, $content, $region = 'main') {
  $output = '';
  if($title){
    $output = '<h2>'. $title .'</h2>';  
  }
  
  $output .= '<div class="box">'. $content .'</div>';
  return $output;
}

/**
 * Override of theme('admin_menu_item_link').
 */
function mothership_admin_icon_classes($path) {
  $classes = array();
  $args = explode('/', $path);
  if ($args[0] === 'admin' || $args[0] === 'node' && $args[1] === 'add') {
    while (count($args)) {
      $classes[] = 'path-'. str_replace('/', '-', implode('/', $args));
      array_pop($args);
    }
    return implode(' ', $classes);
  }
  return '';
} 
 
function mothership_admin_menu_item_link($link) {
  $link['localized_options'] = empty($link['localized_options']) ? array() : $link['localized_options'];
  $link['localized_options']['html'] = TRUE;
  if (isset($link['localized_options']['attributes']['class'])) {
    $link['localized_options']['attributes']['class'] = mothership_admin_icon_classes($link['href']);
  }
  else {
    $link['localized_options']['attributes']['class'] .= ' '. mothership_admin_icon_classes($link['href']);
  }
  $link['description'] = check_plain(truncate_utf8(strip_tags($link['description']), 150, TRUE, TRUE));
  $link['description'] = "<span class='icon'></span>" . $link['description'];
  $link['title'] .= !empty($link['description']) ? "<span class='menu-description'>{$link['description']}</span>" : '';
  return l($link['title'], $link['href'], $link['localized_options']);
}
