<?php
// $Id: matrix.inc,v 1.1.2.2 2009/01/13 07:13:46 aaron1234nz Exp $ 
/**
 * @file
 * Matrix field used with Fusion Charts Nodes.
 * In time it is planned to remove this module in favor of
 * the CCK matrixfield module.
 */
 
/*
 * Implementation of hook_elements
 */
function fusioncharts_elements() {
  $type['matrixfield'] = array(
    '#attributes' => array('class' => 'matrixfield'), 
    '#input' => TRUE,
    '#default_value' => array()
  );
  return $type;
}

function theme_matrixfield($element) {
  $header = array();
  $header[0] = '';
  $first_col = array();
  $rows_count = count($element['#rows']);
  $cols_count = count($element['#cols']);
  array_unshift($element['#rows'], '');
  array_unshift($element['#cols'], '');
  for ($i=0; $i< $rows_count; $i++) {
    $first_col[$i] = $element['#rows'][$i+1];
    for ($j=0; $j< $cols_count; $j++) {
      $header[$j+1] = $element['#cols'][$j+1];
      $form['matrix'][$i][$j] = array(
        '#type' => 'textfield',
        '#size' => 5,
        '#parents' => array(
          0 => $element['#name'],
          1 => 'matrix',
          2 => $i,
          3 => $j,
        ),
        '#name' => "{$element['#name']}[matrix][$i][$j]",
        '#id' => "edit-field-{$element['#name']}-matrix-$i-$j",
        '#value' => isset($element['#default_value'][$i][$j]) ? $element['#default_value'][$i][$j] : '',
      );
    }
  }
  $form['header'] = array('#type' => 'hidden',
                          '#value' => $header,
                          '#parents' => array(0 => $element['#name']),
                          '#name' => "{$element['#name']}[matrix_header]",
                          '#id' => "{$element['#name']}-header",
                         );
  $form['first_col'] = array('#type' => 'hidden',
                             '#value' => $first_col,
                             '#parents' => array(0 => $element['#name']),
                             '#name' => "{$element['#name']}[matrix_first_col]",
                             '#id' => "{$element['#name']}-first-col",
                            ); 
  $output = theme('fusioncharts_matrix_table_form', $form);
  return theme('form_element', $element, $output);
}

// function borrowed from the matrix module
function theme_fusioncharts_matrix_table_form($form) {
  $header = $form['header']['#value'];
  foreach ($form['matrix'] as $row_key => $fields) {
    if (isset($form['first_col']['#value'][$row_key])) {
      unset($row);
      $row[] = $form['first_col']['#value'][$row_key];
      foreach ($fields as $col_key => $field) {
        if ($field['#type'] == 'textfield') { 
          $row[] = drupal_render($form['matrix'][$row_key][$col_key]);
        }
      }
      $rows[] = $row;
    }
  }
  $form['header']['#value'] = serialize($form['header']['#value']);
  $form['first_col']['#value'] = serialize($form['first_col']['#value']);
  $output .= theme('table', $header, $rows, array('style' => 'width:auto')) . drupal_render($form['header']) . drupal_render($form['first_col']);
  return $output;
}