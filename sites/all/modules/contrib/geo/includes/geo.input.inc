<?php // $Id: geo.input.inc,v 1.4 2009/12/09 18:00:49 vauxia Exp $

/**
 * Implementation of hook_elements().
 */
function geo_elements() {
  return array(
    'geo_latlon' => array(
      '#input' => TRUE,
      '#process' => array('geo_latlon_process'),
    ),
  );
}

/**
 * A #process handler for the latlon element.
 */
function geo_latlon_process($element, $edit, $form_state, $form) {
  $element['lat'] = array(
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#default_value' => $element['#value']['lat'],
    '#required' => $element['#required'],
    '#size' => 12,
    '#maxlength' => 15,
  );
  $element['lon'] = array(
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#default_value' => $element['#value']['lon'],
    '#required' => $element['#required'],
    '#size' => 12,
    '#maxlength' => 15,
  );
  return $element;
}

function geo_field_convert_value(&$element) {
  foreach (element_children($element) as $key) {
    if (isset($element[$key]['field']) && $element[$key]['field']['#access']) {
      $field = $element[$key]['field'];
      $theme = $field['#single'] ? $field['items'][0]['#theme'] : $field['items']['#theme'];
      $format = geo_theme_input($theme);
      foreach ($field['items'] as $i => $item) {
        if ($format && is_array($item) && isset($item['#item'])) {
          $element[$key]['field']['items'][$i]['#item'][$format] = geo_value($item['#item']['wkb'], $format);
        }
      }
    }
  }
  return $element;
}
