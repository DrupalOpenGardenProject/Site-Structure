<?php
// $Id$
/**
 * @file
 * views mothership overwrites
 */
function mothership_preprocess_views_view_list(&$vars) {
  mothership_preprocess_views_view_unformatted($vars);
}

function mothership_preprocess_views_view_unformatted(&$vars) {

  $view     = $vars['view'];
  $rows     = $vars['rows'];

  $vars['classes'] = array();
  // Set up striping values.
  foreach ($rows as $id => $row) {

    if (theme_get_setting(mothership_cleanup_views_row_count)) {
      if (theme_get_setting(mothership_cleanup_views_row_identify)) {
        $vars['classes'][$id] = 'views-row-' . ($id + 1);            
      }
      else{
        $vars['classes'][$id] = 'row-' . ($id + 1);  
      }
    }

    if (theme_get_setting(mothership_cleanup_views_zebra)) {
      if (theme_get_setting(mothership_cleanup_views_row_identify)) {
        $vars['classes'][$id] .= ' views-row-' . ($id % 2 ? 'even' : 'odd');        
      }
      else{
        $vars['classes'][$id] .=  ($id % 2 ? ' even ' : ' odd ');        
      } 
    }

    if ($id == 0 AND theme_get_setting(mothership_cleanup_views_first_last)) {
      if (theme_get_setting(mothership_cleanup_views_row_identify)) {
        $vars['classes'][$id] .= ' views-row-first';
      }
      else{
        $vars['classes'][$id] .= 'first';  
      }  
      
    }
  }

  if (theme_get_setting(mothership_cleanup_views_first_last)) {
    if (theme_get_setting(mothership_cleanup_views_row_identify)) {
      $vars['classes'][$id] .= ' views-row-last';
    }
    else{
      $vars['classes'][$id] .= ' last';
    }
  }

}

/**
 * Display a view as a table style.
 */
function mothership_preprocess_views_view_table(&$vars) {
  $view     = $vars['view'];

  // We need the raw data for this grouping, which is passed in as $vars['rows'].
  // However, the template also needs to use for the rendered fields.  We
  // therefore swap the raw data out to a new variable and reset $vars['rows']
  // so that it can get rebuilt.
 // $result   = $vars['rows']; http://drupal.org/node/348190#comment-1451822
  $result = $view->result;
  $vars['rows'] = array();

  $options  = $view->style_plugin->options;
  $handler  = $view->style_plugin;

  $fields   = &$view->field;
  $columns  = $handler->sanitize_columns($options['columns'], $fields);

  $active   = !empty($handler->active) ? $handler->active : '';
  $order    = !empty($handler->order) ? $handler->order : 'asc';

  $query    = tablesort_get_querystring();
  if ($query) {
    $query = '&' . $query;
  }

  // Fields must be rendered in order as of Views 2.3, so we will pre-render
  // everything.
  $renders = array();
  $keys = array_keys($view->field);
  foreach ($result as $count => $row) {
    foreach ($keys as $id) {
      $renders[$count][$id] = $view->field[$id]->theme($row);
    }
  }

  foreach ($columns as $field => $column) {
    // render the header labels
    if ($field == $column && empty($fields[$field]->options['exclude'])) {
      $label = check_plain(!empty($fields[$field]) ? $fields[$field]->label() : '');
      if (empty($options['info'][$field]['sortable']) || !$fields[$field]->click_sortable()) {
        $vars['header'][$field] = $label;
      }
      else {
        // @todo -- make this a setting
        $initial = 'asc';

        if ($active == $field && $order == 'asc') {
          $initial = 'desc';
        }

        $title = t('sort by @s', array('@s' => $label));
        if ($active == $field) {
          $label .= theme('tablesort_indicator', $initial);
        }
        $link_options = array(
          'html' => true,
          'attributes' => array('title' => $title),
          'query' => 'order=' . urlencode($field) . '&sort=' . $initial . $query,
        );
        $vars['header'][$field] = l($label, $_GET['q'], $link_options);
      }
    }

    // Create a second variable so we can easily find what fields we have and what the
    // CSS classes should be.
    $vars['fields'][$field] = views_css_safe($field);
    if ($active == $field) {
      $vars['fields'][$field] .= ' active';
    }

    // Render each field into its appropriate column.
    foreach ($result as $num => $row) {
      if (!empty($fields[$field]) && empty($fields[$field]->options['exclude'])) {
        $field_output = $renders[$num][$field];

        // Don't bother with separators and stuff if the field does not show up.
        if (empty($field_output) && !empty($vars['rows'][$num][$column])) {
          continue;
        }

        // Place the field into the column, along with an optional separator.
        if (!empty($vars['rows'][$num][$column])) {
          if (!empty($options['info'][$column]['separator'])) {
            $vars['rows'][$num][$column] .= filter_xss_admin($options['info'][$column]['separator']);
          }
        }
        else {
          $vars['rows'][$num][$column] = '';
        }

        $vars['rows'][$num][$column] .= $field_output;
      }
    }
  }
  //rows classes

  foreach ($vars['rows'] as $num => $row) {
    if ( $num == 0 AND theme_get_setting(mothership_cleanup_views_table_first_last) ) {
        $vars['row_classes'][$num]['first'] = "first";      
    }
    if (theme_get_setting(mothership_cleanup_views_table_row_count)) { 
      $vars['row_classes'][$num]['count'] = "row-" .$num; 
    }
 
    if (theme_get_setting(mothership_cleanup_views_table_zebra)) { 
      $vars['row_classes'][$num]['zebra'] = ($num % 2 == 0) ? 'odd' : 'even';
    }
  }
  if (theme_get_setting(mothership_cleanup_views_table_first_last)) { 
    $vars['row_classes'][$num][] = "last";
  }
  
  $vars['class'] = 'views-table';
  if (!empty($options['sticky'])) {
    drupal_add_js('misc/tableheader.js');
    $vars['class'] .= " sticky-enabled";
  }
}



function mothership_content_view_multiple_field($items, $field, $values) {
  $output = '';
  foreach ($items as $item) {
    if (!empty($item) || $item == '0') {
      $output .= '<div>'. $item .'</div>';
    }
  }
  return $output;
}

