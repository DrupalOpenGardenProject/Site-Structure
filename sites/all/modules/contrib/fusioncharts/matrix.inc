<?php
// $Id: matrix.inc,v 1.3.2.2 2009/03/15 03:17:39 aaron1234nz Exp $ 

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
  $type['fc_matrixfield'] = array(
    '#attributes' => array('class' => 'fc_matrixfield'), 
    '#input' => TRUE,
    '#process' => array('fc_matrix_process'),
  );
  return $type;
}

/**
 * Process the matrix type element before displaying the field.
 *
 * Build the form element. When creating a form using FAPI #process,
 * note that $element['#value'] is already set.
 *
 */
function fc_matrix_process($element, $edit, $form_state, $form) {
  $form = array();
  $header = array();
  $header[0] = '';
  $first_col = array();
  $rows_count = count($element['#rows']);
  $cols_count = count($element['#cols']);
  array_unshift($element['#rows'], '');
  array_unshift($element['#cols'], '');
  $form = array(
    '#tree' => TRUE,
    '#theme' => 'fusioncharts_matrix_table_form', 
    '#prefix' => '<div class="form-item matrix_field">'. $element['#prefix'],
    '#suffix' => $element['#suffix']. '</div>',
    '#parents' => $element['#parents'],
    '#title' => $element['#title'],
    '#description' => $element['#description'],
  );
      
  for ($i=0; $i< $rows_count; $i++) {
    $first_col[$i] = $element['#rows'][$i+1];
    for ($j=0; $j< $cols_count; $j++) {
      $header[$j+1] = $element['#cols'][$j+1];
      $form['matrix'][$i][$j] = array(
        '#type' => 'textfield',
        '#size' => 5,
        '#default_value' => isset($edit['matrix'][$i][$j]) ? $edit['matrix'][$i][$j] : $element['#default_value'][$i][$j],
      );
    }
  }
  $form['header'] = array('#type' => 'value',
                          '#value' => $header,
                         );
  $form['first_col'] = array('#type' => 'value',
                             '#value' => $first_col,
                            );
  return $form;
}

/**
 * Format the field into a table
 * @param $form The form definition
 * @return HTML (rendered form)
 */
function theme_fusioncharts_matrix_table_form($form) {
  $output = '';
  $header = $form['header']['#value'];
  if ($form['matrix']) {
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
  }
  $form['header']['#value'] = serialize($form['header']['#value']);
  $form['header']['#type'] = 'hidden';
  $form['first_col']['#value'] = serialize($form['first_col']['#value']);
  $form['first_col']['#type'] = 'hidden';
  
  $output .= '<div><b>'. t($form['#title']) .':</b></div>';
  $output .= theme('table', $header, $rows, array('style' => 'width:auto')) . drupal_render($form['header']) . drupal_render($form['first_col']);
  $output .= '<div>'. $form['#description'] .'</div>';
  return $output;
}
