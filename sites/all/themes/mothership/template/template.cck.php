<?php
// $Id$
/**
 * @file
 * CCK mothership overwrites
 */


/**
 * Theme function for the 'generic' single file formatter.
 */
function mothership_filefield_file($file) {
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file['fid'])) {
    return '';
  }

  $path = $file['filepath'];
  $url = file_create_url($path);
  $icon = theme('filefield_icon', $file);

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  // TODO: Possibly move to until I move to the more complex format described
  // at http://darrelopry.com/story/microformats-and-media-rfc-if-you-js-or-css
  $options = array(
    'attributes' => array(
      'type' => $file['filemime'],
      'length' => $file['filesize'],
    ),
  );

  // Use the description as the link text if available.
  if (empty($file['data']['description'])) {
    $link_text = $file['filename'];
  }
  else {
    $link_text = $file['data']['description'];
    $options['attributes']['title'] = $file['filename'];
  }

//  return '<div class="filefield-file clear-block">'. $icon . l($link_text, $url, $options) .'</div>';

  return l($icon . '<span>' . $link_text . '</span>', $url, $options= array('html' => TRUE));
}


//icon
function mothership_filefield_icon($file) {
  if (is_object($file)) {
    $file = (array) $file;
  }
  $mime = check_plain($file['filemime']);

  $dashed_mime = strtr($mime, array('/' => '-'));

  if ($icon_url = filefield_icon_url($file)) {
//    $icon = '<img class="field-icon-'. $dashed_mime .'"  alt="'. $mime .' icon" src="'. $icon_url .'" />';
    $icon = '<img "  alt="'. $mime .' icon" src="'. $icon_url .'" />';
  }
//  return '<div class="filefield-icon field-icon-'. $dashed_mime .'">'. $icon .'</div>';
  return $icon;
}
