<?php
// $Id: extractor.feeds.inc,v 1.1 2010/03/01 16:31:36 rsoden Exp $

/**
 * @file
 * Feeds integration for extractor.
 *
 * @see ExtractorSimplePieParser class
 * @see ExtractorSyndicationParser class
 */

/**
 * Form for feeds integration.
 */
function extractor_feeds_form($config) {
  drupal_add_js(drupal_get_path('module', 'extractor') .'/extractor.js');
  $form = array();
  $form['extractors'] = array(
    '#type' => 'radios',
    '#title' => t('Extractor libraries'),
    '#description' => t('Select the library to use for term extraction.'),
    '#default_value' => $config['extractors'],
    '#options' => array(
      'extractor_simple' => t('Simple Extractor'),
      'placemaker' => t('Yahoo Placemaker')
    ),
  );
  $form['placemaker_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Yahoo API Key'),
    '#description' => t('Supply an !api_key for connecting to the Yahoo Placemaker API.', array('!api_key' => l(t('API key'), 'http://developer.yahoo.com/geo/placemaker/'))),
    '#default_value' => $config['placemaker_key'],
  );
  $form['language'] = array(
    '#type' => 'textfield',
    '#title' => t('Language'),
    '#description' => t('Use specified language (RFC 4646) for place name recognition return of place names.'),
    '#default_value' => $config['language'],
  );
  return $form;
}

/**
 * Defaults for feeds integration.
 */
function extractor_feeds_defaults() {
  return array(
    'extractors' => 'extractor_simple',
    'language' => 'en-US',
    'placemaker_key' => '',
  );
}

/**
 * Return a list of available mapping sources.
 */
function extractor_feeds_get_mapping_sources() {
  return array(
    'extracted_terms' => array(
      'name' => t('Extracted term names'),
      'description' => t('Array of term names extracted from title and or description.'),
    ),
    'extracted_tids' => array(
      'name' => t('Extracted term tids'),
      'description' => t('Array of term ids (tid) of term names extracted from title and or description.'),
    ),
  );
}

/**
 * Retrieve a source element for an element key.
 */
function extractor_feeds_get_source_element($item, $element_key, $config) {
  if ($element_key == 'extracted_terms') {
    return extractor_extract($item['title'] .' '. $item['description'], $config['extractors'], $config);
  }
  elseif ($element_key == 'extracted_tids') {
    $terms = extractor_extract($item['title'] .' '. $item['description'], $config['extractors'], $config);
    return array_keys($terms);
  }
}