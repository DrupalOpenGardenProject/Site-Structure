<?php
// $Id: gd_image_chart.inc,v 1.1.2.1 2010/07/01 07:10:58 brmassa Exp $
/**
 * @author Mads Peter Henderson http://drupal.org/user/421971
 * @file
 * Use GD library to draw chart on your site
 * this is heavily inspired by http://www.phpbuilder.com/columns/wiesendanger20001218.php3?page=6 - So thanks!
 */

/**
 * Implementation of hook_charts_render().
 *
 * Its a Charts module hook. It transform the data into a HTML chart.
 *
 * @param &$data
 *   Array. The
 */
function _gd_image_chart_charts_render(&$data) {
  $path = "gd_image_chart";
  $file_name = uniqid(session_id()  ."_", TRUE) .".png";
  gd_image_chart_image($data, $path, $file_name);
  return '<div><img alt="Chart created with GD Library" src="'. file_create_url($path ."/". $file_name) .'"/></div>';
}

function gd_image_chart_image($data, $path, $file_name) {
  // create image
  $width = $data['#width'];
  $height = $data['#height'];
  $image = imagecreate($width, $height);

  // colors
  $background_color_html = empty($data['#color']['background']) ? '#FFFFFF' : $data['#color']['background'];
  $background_color_rgb = _gd_image_chart_html2rgb($background_color_html);
  //The first color to be allocated is the background!!!
  $background_color = imagecolorallocate($image, $background_color_rgb[0], $background_color_rgb[1], $background_color_rgb[2]);
  $white = imagecolorallocate($image, 0xFF, 0xFF, 0xFF);
  $black = imagecolorallocate($image, 0x00, 0x00, 0x00);
  $gray = imagecolorallocate($image, 0xC0, 0xC0, 0xC0);
  $text_color_html = empty($data['#color']['text']) ? '#000000' : $data['#color']['text'];
  $text_color_rgb = _gd_image_chart_html2rgb($text_color_html);
  $text_color = imagecolorallocate($image, $text_color_rgb[0], $text_color_rgb[1], $text_color_rgb[2]);
  // layout
  $maxval = 0;
  $nval = 0;
  $series_count = 0;
  foreach (element_children($data) as $series) {
    $series_data = _charts_series_values($data[$series]);
    $maxval = max($series_data) > $maxval ? max($series_data) : $maxval;
    $nval = sizeof($series_data) > $nval ? sizeof($series_data) : $nval;
    $series_count +=1;
  }
  if ($data['#type'] == 'vbar2D') {
    //For vbar2d the number of x values equals max count of series times the number of series to display
    $nval = $nval * $series_count;
  }
  $vmargin = 20; // top (bottom) vertical margin for title (x-labels)
  $hmargin = 38; // left horizontal margin for y-labels

  $base = floor(($width - $hmargin) / $nval); // distance between columns

  $ysize = $height - 2 * $vmargin; // y-size of plot
  $xsize = $nval * $base; // x-size of plot

  // title
  $titlefont = 3;
  $title = $data['#title'];

  $txtsz = imagefontwidth($titlefont) * drupal_strlen($title); // pixel-width of title

  $xpos = (int)($hmargin + ($xsize - $txtsz)/2); // center the title
  $xpos = max(1, $xpos); // force positive coordinates
  $ypos = 3; // distance from top

  imagestring($image, $titlefont, $xpos, $ypos, $title , $text_color);

  // y labels and grid lines
  $labelfont = 2;
  $ngrid = 4; // number of grid lines

  $dydat = $maxval / $ngrid; // data units between grid lines
  $dypix = $ysize / ($ngrid + 1); // pixels between grid lines

  for ($i = 0; $i <= ($ngrid + 1); $i++) {
      // iterate over y ticks

      // height of grid line in units of data
      $ydat = (int)($i * $dydat);

      // height of grid line in pixels
      $ypos = $vmargin + $ysize - (int)($i*$dypix);

      $txtsz = imagefontwidth($labelfont) * drupal_strlen($ydat); // pixel-width of label
      $txtht = imagefontheight($labelfont); // pixel-height of label

      $xpos = (int)(($hmargin - $txtsz) / 2);
      $xpos = max(1, $xpos);

      imagestring($image, $labelfont, $xpos,
          $ypos - (int)($txtht/2), $ydat, $text_color);

      if (!($i == 0) && !($i > $ngrid)) { // don't draw at Y=0 and top
        imageline($image, $hmargin - 3, $ypos, $hmargin + $xsize, $ypos, $gray);
      }
  }

  switch ($data['#type']) {
    case 'line2D':
      $yscale = $ysize / (($ngrid+1) * $dydat); // pixels per data unit
      _gd_image_chart_line2d($image, $data, $series_count, $base, $padding, $vmargin, $hmargin, $ysize, $yscale, $xsize, $labelfont, $text_color);
      break;

    case 'vbar2D':
      $yscale = $ysize / (($ngrid+1) * $dydat); // pixels per data unit
      _gd_image_chart_vbar2d($image, $data, $series_count, $base, $padding, $vmargin, $hmargin, $ysize, $yscale, $xsize, $labelfont, $text_color);
      break;

    default:
      return t('Type %type is not possible using %chartplugin',
        array('%type' => $data['#type'],
              '%chartplugin' => 'GD image Chart'));
  }

  // plot frame
  imagerectangle($image, $hmargin, $vmargin, $hmargin + $xsize, $vmargin + $ysize, $black);

  // write image to file system
  $directory = file_directory_path() ."/". $path;
  if (file_check_directory($directory, TRUE)) {
    imagepng($image, $directory ."/". $file_name);
  }
  else {
    drupal_set_message(t("Unable to cereate image at location: %directory/%filename", array('%directory' => $directory, '%filename' => $file_name)), TRUE);
  }
  imagedestroy($image);
}

function _gd_image_chart_line2d($image, $data, $series_count, $base, $padding, $vmargin, $hmargin, $ysize, $yscale, $xsize, $labelfont, $text_color) {
  $series_handled = 0;
  foreach (element_children($data) as $series) {
    $color_html = empty($data[$series]['#color']) ? '#000000' : $data[$series]['#color'];
    $color_rgb = _gd_image_chart_html2rgb($color_html);
    $color = imagecolorallocate($image, $color_rgb[0], $color_rgb[1], $color_rgb[2]);
    $series_data = _charts_series_values($data[$series]);
    $y0_pos = $vmargin + $ysize;
    $xpos_prev = FALSE;
    $ypos_prev = FALSE;
    foreach ($series_data as $xval => $yval) {
        $xpos = $hmargin + ($xval + 1) * $base - $padding;
        $ypos = $y0_pos - (int)($yval*$yscale);
        if ($xpos_prev && $ypos_prev) {
          imageline($image, $xpos_prev, $ypos_prev, $xpos, $ypos, $color);
        }
        $xpos_prev = $xpos;
        $ypos_prev = $ypos;
        // x labels
        if ($series_handled == 0) { //Only print labels for first series - avoid duplicates
          if (empty($data[$series][$xval]['#label'])) {
            $value_label = '';
          }
          else {
            $value_label = $data[$series][$xval]['#label'];
          }
          $txtsz = imagefontwidth($labelfont) * drupal_strlen($value_label);

          $xpos = $xpos - ($txtsz/ 2);
          $ypos = $y0_pos + 3; // distance from x axis

          imagestring($image, $labelfont, $xpos, $ypos, $value_label, $text_color);
        }
    }
    $series_handled += 1;
  }
}

function _gd_image_chart_vbar2d($image, $data, $series_count, $base, $padding, $vmargin, $hmargin, $ysize, $yscale, $xsize, $labelfont, $text_color) {
  // columns and x labels
  $padding = 3; // half of spacing between columns
  $series_handled = 0;
  foreach (element_children($data) as $series) {
    $color_html = empty($data[$series]['#color']) ? '#000000' : $data[$series]['#color'];
    $color_rgb = _gd_image_chart_html2rgb($color_html);
    $color = imagecolorallocate($image, $color_rgb[0], $color_rgb[1], $color_rgb[2]);
    $series_data = _charts_series_values($data[$series]);
    foreach ($series_data as $xval => $yval) {

        // vertical columns
        $ymax = $vmargin + $ysize;
        $ymin = $ymax - (int)($yval*$yscale);
        $xmax = $hmargin + ($xval+1)*$base - $padding;
        $xmin = $hmargin + $xval*$base + $padding;
        $xdelta = $xmax - $xmin;
        $xmax += $xdelta * ($series_handled + ($series_count - 1) * $xval);
        $xmin += $xdelta * ($series_handled + ($series_count - 1) * $xval);

        imagefilledrectangle($image, $xmin, $ymin, $xmax, $ymax, $color);

        // x labels
        if ($series_handled == 0) { //Only print labels for first series - avoid duplicates
          if (empty($data[$series][$xval]['#label'])) {
            $value_label = '';
          }
          else {
            $value_label = $data[$series][$xval]['#label'];
          }
          $txtsz = imagefontwidth($labelfont) * drupal_strlen($value_label);

          $xpos = $xmin + (int)((($xdelta * $series_count) - $txtsz)/ 2);
          $xpos = max($xmin, $xpos);
          $ypos = $ymax + 3; // distance from x axis

          imagestring($image, $labelfont, $xpos, $ypos, $value_label, $text_color);
        }
    }
    $series_handled += 1;
  }
}

function _gd_image_chart_html2rgb($color) {
  if ($color[0] == '#') {
    $color = substr($color, 1);
  }

  if (strlen($color) == 6) {
    list($r, $g, $b) = array(
      $color[0] . $color[1],
      $color[2] . $color[3],
      $color[4] . $color[5]);
  }
  elseif (strlen($color) == 3) {
    list($r, $g, $b) = array(
      $color[0] . $color[0],
      $color[1] . $color[1],
      $color[2] . $color[2]);
  }
  else {
    return FALSE;
  }

  $r = hexdec($r); $g = hexdec($g); $b = hexdec($b);

  return array($r, $g, $b);
}
