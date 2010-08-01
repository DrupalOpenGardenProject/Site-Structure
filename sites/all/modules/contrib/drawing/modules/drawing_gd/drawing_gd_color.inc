<?php
// $Id: drawing_gd_color.inc,v 1.1.2.1 2009/05/09 05:56:28 danielb Exp $

/**
 * @file
 * The color functions for the GD module.
 */

/**
 * Returns RGB values from the color functions.
 *
 *  @param $color
 *    Can be english HTML/X11 color, hex color, array(r, g, b), or 
 *    "rgb(r, g, b)" string.
 *  @return
 *    Array with keys 'r', 'g', & 'b', and corresponding 0-255 values.
 */
function drawing_gd_color($color, $default = array('r' => 0, 'g' => 0, 'b' => 0)) {
  static $functions, $known_colors;
  // if it's already in the correct format, just return it
  if (is_array($color) && $color['r'] && $color['g'] && $color['b']) {
    return $color;
  }
  // we need to deal with strings, so serialize if it's not a string or number
  if (!is_string($color) && !is_numeric($color)) {
    $color = serialize($color);
  }
  $color = trim((string)$color);
  // If we've already checked this color return it now
  if (isset($known_colors[$color])) {
    return $known_colors[$color];
  }
  // Get the functions to check the color against
  if (empty($functions)) {
    $functions = array(
      'drawing_gd_color_rgb',
      'drawing_gd_color_eng',
      'drawing_gd_color_hex',
    );
    // Allow modules to add their own color parsing
    drupal_alter('drawing_gd_color_functions', $functions);
  }
  // Search the functions for the first one that returns a good value
  foreach ($functions as $func) {
    $result = $func($color);
    if ($result) {
      break;
    }
  }
  // use default color
  if (!$result) {
    $result = $default;
  }
  // store result statically for reuse in this request
  $known_colors[$color] = $result;
  // return the value
  return $result;
}

/**
 * Returns RGB values for hex colors
 *
 *  @param $color
 *    String in the format rgb(r, g, b) representing a color.
 *  @return
 *    Array with keys 'r', 'g', & 'b', and corresponding 0-255 values, or
 *    FALSE on failing to identify the color.
 */
function drawing_gd_color_rgb($color) {
  if (substr($color, 0, 3) == 'rgb') {
    $color = str_replace('(', '', str_replace(')', '', $color));
    $color_array = explode(',', $color);
    if (count($color_array) == 3) {
      return array(
        'r' => (int)trim($color_array[0]),
        'g' => (int)trim($color_array[1]),
        'b' => (int)trim($color_array[2]),
      );
    }
  }
  return FALSE;
}

/**
 * Returns RGB values for HTML and X11 english colors.
 * Note that the colors Gray, Green, Maroon, and Purple use the HTML color and
 * the X11 variants are also available as GrayX11, GreenX11, MaroonX11, and
 * PurpleX11.
 *
 *  @param $color
 *    English HTML/X11 color.
 *  @return
 *    Array with keys 'r', 'g', & 'b', and corresponding 0-255 values, FALSE on
 *    failing to identify the color, or the entire array of handled colors if 
 *    the $color param is not supplied.
 */
function drawing_gd_color_eng($color = NULL) {
  static $colors;
  if (empty($colors)) {
    $colors = array(
      'aliceblue' => array(240, 248, 255),
      'antiquewhite' => array(250, 235, 215),
      'aqua' => array(0, 255, 255),
      'aquamarine' => array(127, 255, 212),
      'azure' => array(240, 255, 255),
      'beige' => array(245, 245, 220),
      'bisque' => array(255, 228, 196),
      'black' => array(0, 0, 0),
      'blanchedalmond' => array(255, 235, 205),
      'blue' => array(0, 0, 255),
      'blueviolet' => array(138, 43, 226),
      'brown' => array(165, 42, 42),
      'burlywood' => array(222, 184, 135),
      'cadetblue' => array(95, 158, 160),
      'chartreuse' => array(127, 255, 0),
      'chocolate' => array(210, 105, 30),
      'coral' => array(255, 127, 80),
      'cornflower' => array(100, 149, 237),
      'cornsilk' => array(255, 248, 220),
      'crimson' => array(220, 20, 60),
      'cyan' => array(0, 255, 255),
      'darkblue' => array(0, 0, 139),
      'darkcyan' => array(0, 139, 139),
      'darkgoldenrod' => array(184, 134, 11),
      'darkgray' => array(169, 169, 169),
      'darkgreen' => array(0, 100, 0),
      'darkkhaki' => array(189, 183, 107),
      'darkmagenta' => array(139, 0, 139),
      'darkolivegreen' => array(85, 107, 47),
      'darkorange' => array(255, 140, 0),
      'darkorchid' => array(153, 50, 204),
      'darkred' => array(139, 0, 0),
      'darksalmon' => array(233, 150, 122),
      'darkseagreen' => array(143, 188, 143),
      'darkslateblue' => array(72, 61, 139),
      'darkslategray' => array(47, 79, 79),
      'darkturquoise' => array(0, 206, 209),
      'darkviolet' => array(148, 0, 211),
      'deeppink' => array(255, 20, 147),
      'deepskyblue' => array(0, 191, 255),
      'dimgray' => array(105, 105, 105),
      'dodgerblue' => array(30, 144, 255),
      'firebrick' => array(178, 34, 34),
      'floralwhite' => array(255, 250, 240),
      'forestgreen' => array(34, 139, 34),
      'fuchsia' => array(255, 0, 255),
      'gainsboro' => array(220, 220, 220),
      'ghostwhite' => array(248, 248, 255),
      'gold' => array(255, 215, 0),
      'goldenrod' => array(218, 165, 32),
      'gray' => array(128, 128, 128),
      'grayx11' => array(190, 190, 190),
      'green' => array(0, 128, 0),
      'greenx11' => array(0, 255, 0),
      'greenyellow' => array(173, 255, 47),
      'honeydew' => array(240, 255, 240),
      'hotpink' => array(255, 105, 180),
      'indianred' => array(205, 92, 92),
      'indigo' => array(75, 0, 130),
      'ivory' => array(255, 255, 240),
      'khaki' => array(240, 230, 140),
      'lavender' => array(230, 230, 250),
      'lavenderblush' => array(255, 240, 245),
      'lawngreen' => array(124, 252, 0),
      'lemonchiffon' => array(255, 250, 205),
      'lightblue' => array(173, 216, 230),
      'lightcoral' => array(240, 128, 128),
      'lightcyan' => array(224, 255, 255),
      'lightgoldenrod' => array(250, 250, 210),
      'lightgreen' => array(144, 238, 144),
      'lightgrey' => array(211, 211, 211),
      'lightpink' => array(255, 182, 193),
      'lightsalmon' => array(255, 160, 122),
      'lightseagreen' => array(32, 178, 170),
      'lightskyblue' => array(135, 206, 250),
      'lightslategray' => array(119, 136, 153),
      'lightsteelblue' => array(176, 196, 222),
      'lightyellow' => array(255, 255, 224),
      'lime' => array(0, 255, 0),
      'limegreen' => array(50, 205, 50),
      'linen' => array(250, 240, 230),
      'magenta' => array(255, 0, 255),
      'maroon' => array(128, 0, 0),
      'maroonx11' => array(176, 48, 96),
      'mediumaquamarine' => array(102, 205, 170),
      'mediumblue' => array(0, 0, 205),
      'mediumorchid' => array(186, 85, 211),
      'mediumpurple' => array(147, 112, 219),
      'mediumseagreen' => array(60, 179, 113),
      'mediumslateblue' => array(123, 104, 238),
      'mediumspringgreen' => array(0, 250, 154),
      'mediumturquoise' => array(72, 209, 204),
      'mediumvioletred' => array(199, 21, 133),
      'midnightblue' => array(25, 25, 112),
      'mintcream' => array(245, 255, 250),
      'mistyrose' => array(255, 228, 225),
      'moccasin' => array(255, 228, 181),
      'navajowhite' => array(255, 222, 173),
      'navy' => array(0, 0, 128),
      'oldlace' => array(253, 245, 230),
      'olive' => array(128, 128, 0),
      'olivedrab' => array(107, 142, 35),
      'orange' => array(255, 165, 0),
      'orangered' => array(255, 69, 0),
      'orchid' => array(218, 112, 214),
      'palegoldenrod' => array(238, 232, 170),
      'palegreen' => array(152, 251, 152),
      'paleturquoise' => array(175, 238, 238),
      'palevioletred' => array(219, 112, 147),
      'papayawhip' => array(255, 239, 213),
      'peachpuff' => array(255, 218, 185),
      'peru' => array(205, 133, 63),
      'pink' => array(255, 192, 203),
      'plum' => array(221, 160, 221),
      'powderblue' => array(176, 224, 230),
      'purple' => array(128, 0, 128),
      'purplex11' => array(160, 32, 240),
      'red' => array(255, 0, 0),
      'rosybrown' => array(188, 143, 143),
      'royalblue' => array(65, 105, 225),
      'saddlebrown' => array(139, 69, 19),
      'salmon' => array(250, 128, 114),
      'sandybrown' => array(244, 164, 96),
      'seagreen' => array(46, 139, 87),
      'seashell' => array(255, 245, 238),
      'sienna' => array(160, 82, 45),
      'silver' => array(192, 192, 192),
      'skyblue' => array(135, 206, 235),
      'slateblue' => array(106, 90, 205),
      'slategray' => array(112, 128, 144),
      'snow' => array(255, 250, 250),
      'springgreen' => array(0, 255, 127),
      'steelblue' => array(70, 130, 180),
      'tan' => array(210, 180, 140),
      'teal' => array(0, 128, 128),
      'thistle' => array(216, 191, 216),
      'tomato' => array(255, 99, 71),
      'turquoise' => array(64, 224, 208),
      'violet' => array(238, 130, 238),
      'wheat' => array(245, 222, 179),
      'white' => array(255, 255, 255),
      'whitesmoke' => array(245, 245, 245),
      'yellow' => array(255, 255, 0),
      'yellowgreen' => array(154, 205, 50),
    );
    drupal_alter('drawing_gd_color_eng', $colors);
  }
  if (!is_null($color)) {
    $color = str_replace(' ', '', strtolower($color));
    if (array_key_exists($color, $colors)) {
      return array(
        'r' => $colors[$color][0],
        'g' => $colors[$color][1],
        'b' => $colors[$color][2],
      );
    }
    return FALSE;
  }
  return $colors;
}

/**
 * Returns RGB values for hex colors.
 *
 *  @param $color
 *    Hex color.
 *  @return
 *    Array with keys 'r', 'g', & 'b', and corresponding 0-255 values,
 *    or FALSE on failing to identify the color.
 */
function drawing_gd_color_hex($color) {
  if ($color[0] == '#') {
      $color = substr($color, 1);
  }
  if (strlen($color) == 6) {
    list($r, $g, $b) = array(
      $color[0] . $color[1],
      $color[2] . $color[3],
      $color[4] . $color[5],
    );
  }
  elseif (strlen($color) == 3) {
    list($r, $g, $b) = array(
      $color[0] . $color[0], 
      $color[1] . $color[1], 
      $color[2] . $color[2],
    );
  }
  else {
    return FALSE;
  }
  return array(
    'r' => hexdec($r), 
    'g' => hexdec($g), 
    'b' => hexdec($b),
  );
}