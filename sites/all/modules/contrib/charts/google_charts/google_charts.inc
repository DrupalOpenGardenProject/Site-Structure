<?php
// $Id: google_charts.inc,v 1.18.4.5 2010/07/02 01:04:23 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Use Google Charts on your site.
 */

function _google_charts($type) {
  $types = array(
    'line2D'  => array('typecode' => 'lc', 'attributes_per_value' => FALSE),
    'hbar2D'  => array('typecode' => 'bhg', 'attributes_per_value' => FALSE),
    'vbar2D'  => array('typecode' => 'bvg', 'attributes_per_value' => FALSE),
    'hbar2Ds' => array('typecode' => 'bhs', 'attributes_per_value' => FALSE),
    'vbar2Ds' => array('typecode' => 'bvs', 'attributes_per_value' => FALSE),
    'pie2D'   => array('typecode' => 'p', 'attributes_per_value' => TRUE),
    'pie3D'   => array('typecode' => 'p3', 'attributes_per_value' => TRUE),
    'venn'    => array('typecode' => 'v', 'attributes_per_value' => FALSE),
    'scatter' => array('typecode' => 's', 'attributes_per_value' => FALSE),
  );
  return $types[$type];
}

/**
 * Convert all Chart-level data.
 *
 * @param &$chart
 *   Array. The array that will be converted into a string for Google Charts
 * @param &$data
 *   Array. The raw data.
 * @return
 *   String. The string presentation of series data
 */
function _google_charts_chart(&$chart, &$data) {
  // Convert the chat TYPE into the Google Chart way.
  // Since its a requirement to build the chart on Google, if the value
  // was not found, return nothing and stop the execution.
  $options = _google_charts($data['#type']);
  if (empty($options['typecode'])) {
    return t('This type is not possible using %chartplugin',
      array('%chartplugin' => 'Google Chart'));
  }
  if ($data['#type'] == 'pie2D' and count(element_children($data)) > 1) {
    $chart[] = 'cht=pc';
  }
  else {
    $chart[] = 'cht='. $options['typecode'];
  }

  // Convert the chat SIZE into the Google Chart way.
  // Since its a requirement to build the chart on Google, if the value
  // was not found, return nothing and stop the execution.
  if (empty($data['#width']) or empty($data['#height'])) {
    return t('Height and Width are required');
  }
  $chart[] = 'chs='. $data['#width'] .'x'. $data['#height'];

  // Add Title and Description to the chart
  if (!empty($data['#title'])) {
    $chart[] = 'chtt='. $data['#title'];
  }

  // Chart background color. Since the default color
  // is white (#ffffff), only different colors are considered
  if (!empty($data['#color']['background']) and $data['#color']['background'] != '#ffffff') {
    $chart[] = 'chf=bg,s,'. substr($data['#color']['background'], 1);
  }

  return;
}

/**
 * Encode the Chart data into a Alphanumeric code, follwing the
 * Google Chart API instruction. Its needed because there is a
 * size limmit to URL strings. So we reduce the amount of characters.
 *
 * It basicly uses a scale of 61 levels to represent each chart
 * value. If a more precise scale is needed, see
 * _google_charts_codingextended(), which produces a 4000 levels,
 * but also a bigger URL string.
 *
 * @param $data
 *   Array. A series of numeric data values
 * @return
 *   String. The string presentation of series data
 */
function _google_charts_data_codingsimple($value, $max) {
  // Set the list of characters and the size of the list
  $simple = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
  $simple_len = drupal_strlen($simple) - 1;

  if ($value >= 0) {
    return $simple[round($simple_len * $value / $max)];
  }
  else {
    return  '_';
  }
}

/**
 * Implementation of hook_charts_render().
 *
 * Its a Charts module hook. It transform the data into a HTML chart.
 *
 * @param &$data
 *   Array. The
 */
function _google_charts_render(&$data) {
  $chart = array();
  if ($message = _google_charts_chart($chart, $data)) {
    return $message;
  }

  // Convert the chat DATA into the Google Chart way.
  // Since its a requirement to build the chart on Google, if the value
  // was not found, return nothing and stop the execution.
  if ($message = _google_charts_series($chart, $data)) {
    return $message;
  }

  // Browsers tend to load images in sequence, so Google allow users to put a
  // number before the chart.apis.google.com so browsers think they can download
  // in simultaneously
  // @TODO
//   static $count = 1;
//   $count++;
//   if ($count == 10)
//   {
//     $count = 0;
//   }

  // If its all ok, build the HTML img tag
  return '<img src="http://chart.apis.google.com/chart?'. implode('&amp;', $chart) .'" alt= ""/>';
}

/**
 * Convert all Series-level data.
 *
 * @param &$chart
 *   Array. The array that will be converted into a string for Google Charts
 * @param &$data
 *   Array. The raw data.
 * @return
 *   String. The string presentation of series data
 */
function _google_charts_series(&$chart, &$data) {
  $options = _google_charts($data['#type']);

  // The final output is going to be build
  $chart_data = '';

  $value_labels = array();

  // For each chart value, encode it
  // Note: Underscore represents a missing value
  $serie_index = 0;
  foreach (element_children($data) as $series) {
    if ($serie_index and $data['#type'] == 'pie3D') {
      break;
    }
    // Include a series separator
    if (!empty($chart_data)) {
      $chart_data .= ',';
    }

    // Get only the numeric values from the series
    $series_data = _charts_series_values($data[$series]);

    // Get the highest value on the series, to be a reference point
    $max = max($series_data);

    // Value labels: temporary array.
    $value_labels_temp = array();

    // For each series of data, scan it
    $value_index = 0;
    foreach (array_keys($series_data) as $value) {

      $svalue = &$data[$series][$value];
      $chart_data .= _google_charts_data_codingsimple($series_data[$value], $max);

      $value_labels_temp[] = empty($svalue['#label']) ? NULL : $svalue['#label'];

      // Get the highlight points
      if (!empty($svalue['#highlight'])
          or ($data['#type'] == 'scatter' and ($series % 2 == 0))) {
        $highlight[] = 't'. $svalue['#label'] .','.
          (empty($svalue['#color']) ? substr($data[$series]['#color'], 1) : substr($svalue['#color'], 1)) .','.
          $series .','.
          $value .','.
          (empty($svalue['#size']) ? 10 : $svalue['#size']);
      }

      // If the chart type uses data in a way each value has its own attributes
      // (instead the series), put the values there
      if ($options['attributes_per_value']
          or ($data['#type'] == 'scatter' and ($series % 2 == 0))) {
        // Series legends
        $value_labels[] = empty($svalue['#label']) ? NULL : $svalue['#label'];

        // Series legends
        $legends[] = empty($svalue['#label']) ? NULL : $svalue['#label'];

        // Series colors
        $colors[] = empty($data['#color'][$value_index]) ? NULL : substr($data['#color'][$value_index], 1);

        $value_index++;
      }
    }

    // Value labels
    if (!empty($value_labels_temp)) {
      $value_labels += $value_labels_temp;
    }

    if (empty($options['attributes_per_value'])) {
      // Series legends
      $legends[] = empty($data[$series]['#legend']) ? NULL : $data[$series]['#legend'];

      // Series colors
      $colors[] = empty($data[$series]['#color']) ? NULL : substr($data[$series]['#color'], 1);
    }

    $serie_index++;
  }

  // Return the series of data
  if (empty($chart_data)) {
    return t('No enough data to create a chabvgrt.');
  }

   // Insert data
  $chart[] = 'chd=s:'. $chart_data;

  // Insert series color
  foreach ($colors as $color) {
    if (!empty($color)) {
      $chart[] = 'chco='. implode(',', $colors);
      break;
    }
  }

  // Insert values labels
  if ($data['#label'] and !empty($value_labels)) {
    foreach ($value_labels as $label) {
      if (!empty($label)) {
        $chart[] = 'chl='. implode('|', $value_labels);
        break;
      }
    }
  }

  // Insert multiple series tag
  if ($data['#legend'] and !empty($legends)) {
    foreach ($legends as $legend) {
      if (!empty($legend)) {
        $chart[] = 'chdl='. implode('|', $legends);
        break;
      }
    }
  }

  // Insert the highlighted values
  if (!empty($highlight)) {
    $chart[] = 'chm='. implode('|', $highlight);
  }

  return;
}
