<?php
// $Id: placemaker.inc,v 1.1 2010/03/01 16:31:36 rsoden Exp $

/**
 * Tags a single item.
 */
function placemaker_extract($text, $config) {
  // TODO: ALLOW PER EXTRACTOR VOCABS?
  $vid = variable_get('extractor_simple_vid', 1);
  $term = _placemaker_send_text($text, $vid, $config);
  $tags = array();
  if ($term) {
    $tags[$term['tid']] = $term;
  }
  return $tags;
}

/**
 * Sends items to Placemaker API.
 */
function _placemaker_send_text($text, $vid, $config) {
  // Make placemaker request.
  $apiendpoint = 'http://wherein.yahooapis.com/v1/document';
  $inputType = 'text/html';

  $outputType = 'xml';
  $post = 'appid='. $config['placemaker_key'] .'&documentContent='. $text .'&documentType='. $inputType .'&inputLanguage='. $config['language'] .'&outputType='. $outputType .'&autoDisambiguate=true';
  $ch = curl_init($apiendpoint);

  curl_setopt($ch, CURLOPT_POST, 1);
  curl_setopt($ch, CURLOPT_POSTFIELDS, $post);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  $results = curl_exec($ch);
  curl_close($ch);

  // Parse results of placemaker request.
  $xml = simplexml_load_string($results);
  $item['vid'] = $vid;
  $item['name'] = (string)$xml->document->placeDetails->place->name;
  $item['external_id'] = (string)$xml->document->placeDetails->place->woeId;
  $item['lat'] = (string)$xml->document->placeDetails->place->centroid->latitude;
  $item['lon'] = (string)$xml->document->placeDetails->place->centroid->longitude;
  $item['description'] = NULL;

  if ($item['name']) {
    $tags = _placemaker_tag_text($item, $config);
  }

  return $tags;
}

/**
 * Helper function for tagging a text.
 */
function _placemaker_tag_text($item, $config) {
  // Check to see if the term already exists.
  $result = db_query('SELECT tid, external_id FROM {term_geo} WHERE external_id = "%s"', $item['external_id']);
  if ($term = db_fetch_object($result)) {
    $item['tid'] = $term->tid;
    $item['name'] = $term->name;
    return $item;
  }
  // Otherwise create new term and add geotaxonomy info.
  else {
    // Separate call to Yahoo GeoPlanet API to return placename in language of choice if not US English.
    if (!empty($config['language']) && $config['language'] != 'en_US') {
      $apiendpoint = 'http://where.yahooapis.com/v1/place/'. $item['external_id'] .'?appid='. $config['placemaker_key'] .'&lang='. $config['language'] .'&select=short';
      $ch = curl_init($apiendpoint);
      $headers = array('Accept: application/xml');
      curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
      $results = curl_exec($ch);
      curl_close($ch);
      $xml = simplexml_load_string($results);
      $item['name'] = (string)$xml->name;
    }
    taxonomy_save_term($item);
    return $item;
  }
}