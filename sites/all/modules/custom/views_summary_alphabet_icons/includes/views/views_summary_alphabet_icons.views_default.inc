<?php
// $Id$

/**
 * @file
 *
 * Provide a default view.
 */

/**
 * Implementation of hook_views_default_views().
 */
function views_summary_alphabet_icons_views_default_views() {
  // --- Paste any default views here:

  // --- End paste.
  $views[$view->name] = $view;
  return $views;
}