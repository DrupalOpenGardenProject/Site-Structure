<?php
// $Id: extractor_simple.inc,v 1.1 2009/12/04 15:01:46 alexb Exp $

/**
 * @file:
 * Simple term extraction.
 */

/**
 * Finds tags in text.
 */
function extractor_simple_extract($text) {
  $tags = array();
  $text = strip_tags($text);
  $words = _extractor_simple_split($text);
  $vid = variable_get('extractor_simple_vid', 1);

  for ($pos = 0; $pos < count($words); $pos++) {
    $term_names = $term_tids = $terms = array();
    $word = $words[$pos];

    // 1) get all terms that start with this word.
    foreach (_extractor_simple_lookup($word) as $term) {
      $term_tids[$term->name] = $term->tid;
      $term_names[$term->name] = $term->name;
    }
    // Skip to immediate loop if no results.
    if (!count($term_tids)) {
      continue;
    }

    // 2) Order result by length desc.
    $sorted = FALSE;
    $sorted_terms = array_values($term_names);
    $terms = array();
    while (!$sorted) {
      $sorted = TRUE;
      for ($i = 0; $i < count($sorted_terms) - 1; $i++) {
        if (strlen($sorted_terms[$i]) < strlen($sorted_terms[$i+1])) {
          $tmp = $sorted_terms[$i+1];
          $sorted_terms[$i+1] = $sorted_terms[$i];
          $sorted_terms[$i] = $tmp;
          $sorted = FALSE;
        }
      }
    }
    foreach ($sorted_terms as $term) {
      $terms[$term_tids[$term]] = $term_names[$term];
    }

    // 4) Determine which tag fits by looking at next word in text.
    foreach ($terms as $tid => $term) {
      $term_words = _extractor_simple_split($term);
      // Iterate through tag words backwards, skip to the start of the outmost loop
      // if we find a mismatch.
      for ($i = count($term_words) - 1; $i >= 0; $i--) {
        if ($term_words[$i] != $words[$pos+$i]) {
          continue 2; // Skips to start of foreach ($terms as $term) {
        }
      }
      // We have a full match, add to result array, shift $pos pointer to the next word
      // after this term and break out of the immediate loop.
      $tags[$tid] = $term;
      $pos = $pos + count($term_words);
      break; // Skips to start of while (!$sorted) {
    }
  }

  return $tags;
}

/**
 * Split text into words.
 */
function _extractor_simple_split($text) {
  return preg_split("/[\s,.:\-\(\)\[\]{}*\/]+/", $text);
}

/**
 * Look up terms for a given word. Supports up to 2000 terms.
 */
function _extractor_simple_lookup($word) {
  static $term_cache = array();
  static $loaded;

  // Do not bother if word starts with a numeric or if word is in stop word list.
  if ((strlen($word) < 3) || is_numeric($word[0]) || in_array(strtolower($word), _extractor_simple_stopwords())) {
    return array();
  }

  if (!$loaded) {
    $result = db_query_range('SELECT tid, name FROM {term_data} WHERE vid = %d', variable_get('extractor_simple_vid', 1), 0, 2000);
    while ($term = db_fetch_object($result)) {
      $term_cache[strtolower($term->name[0])][$term->name] = $term;
    }
    $loaded = TRUE;
  }

  $terms = array();
  if (!empty($term_cache)) {
    if (isset($term_cache[strtolower($word[0])])) {
      foreach ($term_cache[strtolower($word[0])] as $name => $term) {
        if (stripos($name, $word) === 0) {
          $terms[$term->tid] = $term;
        }
      }
    }
  }

  return $terms;
}

/**
 * Stop words.
 */
function _extractor_simple_stopwords() {
  return array('a', 'able', 'about', 'across', 'after', 'all', 'almost', 'also', 'am', 'among', 'an', 'and', 'any', 'are', 'as', 'at', 'be', 'because', 'been', 'but', 'by', 'can', 'cannot', 'could', 'dear', 'did', 'do', 'does', 'either', 'else', 'ever', 'every', 'for', 'from', 'get', 'got', 'had', 'has', 'have', 'he', 'her', 'hers', 'him', 'his', 'how', 'however', 'i', 'if', 'in', 'into', 'is', 'it', 'its', 'just', 'least', 'let', 'like', 'likely', 'may', 'me', 'might', 'most', 'must', 'my', 'neither', 'no', 'nor', 'not', 'of', 'off', 'often', 'on', 'only', 'or', 'other', 'our', 'own', 'rather', 'said', 'say', 'says', 'she', 'should', 'since', 'so', 'some', 'than', 'that', 'the', 'their', 'them', 'then', 'there', 'these', 'they', 'this', 'tis', 'to', 'too', 'twas', 'us', 'wants', 'was', 'we', 'were', 'what', 'when', 'where', 'which', 'while', 'who', 'whom', 'why', 'will', 'with', 'would', 'yet', 'you', 'your');
}