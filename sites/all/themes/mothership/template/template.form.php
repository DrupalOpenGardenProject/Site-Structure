<?php
// $Id$
/**
 * @file
 * form mothership overwrites
 */

function mothership_form_element($element, $value) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  //add a more specific form-item-$type
  $output = "<div class=\"form-item form-item-" . $element['#type'] . " \" ";
  // TODO cant this be dublicated on a page?
  //and then its not unique
  if (!empty($element['#id'])) {
    $output .= ' id="'. $element['#id'] .'-wrapper"';
  }
  $output .= ">\n";
  $required = !empty($element['#required']) ? '<span class="form-required" title="'. $t('This field is required.') .'">*</span>' : '';

  if (!empty($element['#title'])) {
    $title = $element['#title'];
    if (!empty($element['#id'])) {
      $output .= ' <label for="'. $element['#id'] .'">'. $t('!title: !required', array('!title' => filter_xss_admin($title), '!required' => $required)) ."</label>\n";
    }
    else {
      $output .= ' <label>'. $t('!title: !required', array('!title' => filter_xss_admin($title), '!required' => $required)) ."</label>\n";
    }
  }
  //TODO test to see if this is clean text - then we might need a <span>
  //if we need to catch the content with
  $output .= "$value\n";

  if (!empty($element['#description'])) {
    $output .= '<div class="form-description">'. $element['#description'] ."</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/* and size is not set to 20 so we might have a chance to style the it */
function mothership_file($element) {
  _form_set_class($element, array('file'));
  return theme('form_element', $element, '<input type="file" name="'. $element['#name'] .'"'. ($element['#attributes'] ? ' '. drupal_attributes($element['#attributes']) : '') .' id="'. $element['#id'] .'"  />');
/* size="20" */
}

function mothership_checkbox($element) {
  _form_set_class($element, array('checkbox'));
  $checkbox = '<input ';
  $checkbox .= 'type="checkbox" ';
  $checkbox .= 'name="'. $element['#name'] .'" ';
  $checkbox .= 'id="'. $element['#id'] .'" ' ;
  $checkbox .= 'value="'. $element['#return_value'] .'" ';
  $checkbox .= $element['#value'] ? ' checked="checked" ' : ' ';
  $checkbox .= drupal_attributes($element['#attributes']) .' />';

  if (!is_null($element['#title'])) {
    $checkbox = '<label class="form-option" for="'. $element['#id'] .'">'. $checkbox .' '. $element['#title'] .'</label>';
  }

  unset($element['#title']);
  return theme('form_element', $element, $checkbox);
}

/*adds a span tag inside the legend so we can control the legend width*/
function mothership_fieldset($element) {

  if (!empty($element['#collapsible'])) {
    drupal_add_js('misc/collapse.js');

    if (!isset($element['#attributes']['class'])) {
      $element['#attributes']['class'] = '';
    }

    $element['#attributes']['class'] .= ' collapsible';
    if (!empty($element['#collapsed'])) {
      $element['#attributes']['class'] .= ' collapsed';
    }
  }

  return '<fieldset'. drupal_attributes($element['#attributes']) .'>'. ($element['#title'] ? '<legend><span>'. $element['#title'] .'</span></legend>' : '') . (isset($element['#description']) && $element['#description'] ? '<div class="description">'. $element['#description'] .'</div>' : '') . (!empty($element['#children']) ? $element['#children'] : '') . (isset($element['#value']) ? $element['#value'] : '') ."</fieldset>\n";
}


function mothership_button($element) {
  // Override theme_button ads spans around it so we can tweak the shit out it
  //http://teddy.fr/blog/beautify-your-drupal-forms
  // Make sure not to overwrite classes.
  if (isset($element['#attributes']['class'])) {
    $element['#attributes']['class'] = 'form-' . $element['#button_type'] .' '. $element['#attributes']['class'];
  }
  else {
    $element['#attributes']['class'] = 'form-' . $element['#button_type'];
  }

  // We here wrap the output with a div + span tag
  return '<div class="form-button ' . $element['#id'] .'"><span><input type="submit" ' . (empty($element['#name']) ? '' : 'name="'. $element['#name'] .'" ')  . 'id="' . $element['#id'] . '" value="'. check_plain($element['#value']) .'" ' . drupal_attributes($element['#attributes']) ." /></span></div>\n";
}

function mothership_image_button($element) {
  // Make sure not to overwrite classes.
  if (isset($element['#attributes']['class'])) {
    $element['#attributes']['class'] = 'form-'. $element['#button_type'] .' '. $element['#attributes']['class'];
  }
  else {
    $element['#attributes']['class'] = 'form-'. $element['#button_type'];
  }

  return '<div class="form-image-button"><input type="image" name="'. $element['#name'] .'" '.
    (!empty($element['#value']) ? ('value="'. check_plain($element['#value']) .'" ') : '') .
    'id="'. $element['#id'] .'" '.
    drupal_attributes($element['#attributes']) .
    ' src="'. base_path() . $element['#src'] .'" '.
    (!empty($element['#title']) ? 'alt="'. check_plain($element['#title']) .'" title="'. check_plain($element['#title']) .'" ' : '' ) .
    "/></div>\n";
}

