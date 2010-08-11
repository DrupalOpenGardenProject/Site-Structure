<?php
// $Id: az-gardens.profile,v 1.0.00 2010/08/11 11:06:23 fndtn357 Exp $

/**
 * Implementation of hook_profile_details().
 */
function az-gardens_profile_details() {
  return array(
    'name' => 'Alphabet Gardens',
    'description' => 'Alphabet Gardens is a community garden news t that <ul><li>aggregates RSS/Atom news feeds</li><li>places community garden news on a map</li><li>provides search on it and</li><li>offers a way of organizing community garden news into channels.</li></ul>By Drupal Open Garden Project.'
  );
}

/**
 * Implementation of hook_profile_modules().
 */
function az-gardens_profile_modules() {
    global $install_locale;
  // Drupal core
  $modules = array(
    'color',
    'comment',
    'dblog',
    'help',
    'mark',
    'menu',
    'node',
    'path',
    'search',
    'system',
    'taxonomy',
    'update',

    'user',
    'ctools',
    'context',
    'context_ui',
    'context_layouts',
    'designkit',
    'features',
    'feeds',
    'feeds_ui',
    'extractor',
    'flot',
    'imageapi',
    'imageapi_gd',
    'imagecache',
    'jquery_ui',
    'libraries',
    'openidadmin',
    'porterstemmer',
    'purl',
    'spaces',
    'spaces_dashboard',
    'views',
    'views_ui',
    'views_rss',
    'views_modes',
    'votingapi',
    'schema',
    'seed',
    'strongarm',
    'geotaxonomy',
  );
  return $modules;
}

/**
 * Returns an array list of core az-gardens modules.
 */
function _az-gardens_core_modules() {
  return array(
    'mapbox',
    'openlayers',
    'openlayers_ui',
    'openlayers_behaviors',
    'openlayers_views',
    'stored_views',
    'web_widgets',
    'data',
    'data_ui',
    'data_search',
    'data_node',
    'data_taxonomy',
    'az_core',
    'az_about',
    'az_search',
    'az_channels',
    'az_widgets',
    'simpleshare',
    'az_world',
    'az_boxes',
    'boxes',
  );
}

/**
 * Implementation of hook_profile_task_list().
 */
function az-gardens_profile_task_list() {
  return array(
    'az-configure' => st('A-Z Gardens configuration'),
  );
}

/**
 * Implementation of hook_profile_tasks().
 */
function az-gardens_profile_tasks(&$task, $url) {
  global $install_locale;

  // Just in case some of the future tasks adds some output
  $output = '';

  if ($task == 'profile') {
    // Create a default vocabulary for storing geo terms imported by the feed_term content type
    // and subsequently used by the extractor module. Used by the az_core feature.
    $data = array('name' => 'Locations', 'relations' => 1);
    taxonomy_save_vocabulary($data);
    variable_set('az_core_location_vocab', $data['vid']);
    variable_set('geotaxonomy_'. $data['vid'], 1);

    // Create a vocabulary for channel tags.
    $data = array('name' => 'Channel tags', 'required' => 1, 'relations' => 0, 'tags' => 1, 'nodes' => array('channel' => 1), 'help' => 'Articles with these tags will appear in this channel.');
    taxonomy_save_vocabulary($data);
    variable_set('az_core_tags_vocab', $data['vid']);

    $modules = _az-gardens_core_modules();
    $files = module_rebuild_cache();
    $operations = array();
    foreach ($modules as $module) {
      $operations[] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }
    $batch = array(
      'operations' => $operations,
      'finished' => '_az-gardens_profile_batch_finished',
      'title' => st('Installing @drupal', array('@drupal' => drupal_install_profile_name())),
      'error_message' => st('The installation has encountered an error.'),
    );
    // Start a batch, switch to 'profile-install-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'profile-install-batch');
    batch_set($batch);
    batch_process($url, $url);
  }

  if ($task == 'az-configure') {

    // Create the admin role.
    db_query("INSERT INTO {role} (name) VALUES ('%s')", 'admin');

    // Other variables worth setting.
    variable_set('site_footer', 'Powered by <a href="http://www.az-gardens.com">Alphabet Garden</a>.');
    variable_set('site_frontpage', 'feeds');
    variable_set('comment_channel', 0);
    variable_set('comment_feed', 0);
    variable_set('comment_book', 0);

    // Clear caches.
    drupal_flush_all_caches();

    // Enable the right theme. This must be handled after drupal_flush_all_caches()
    // which rebuilds the system table based on a stale static cache,
    // blowing away our changes.
    _az-gardens_system_theme_data();
    db_query("UPDATE {system} SET status = 0 WHERE type = 'theme'");
    db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' AND name = 'alphabetgarden'");
    db_query("UPDATE {blocks} SET region = '' WHERE theme = 'alphabetgarden'");
    variable_set('theme_default', 'alphabetgarden');

    // Revert key components that are overridden by others on install.
    $revert = array(
      'az_core' => array('variable'),
    );
    features_revert($revert);

    $task = 'finished';
  }

  return $output;
}

/**
 * Finished callback for the modules install batch.
 *
 * Advance installer task to language import.
 */
function _az-gardens_profile_batch_finished($success, $results) {
  variable_set('install_task', 'az-configure');
}

/**
 * Implementation of hook_form_alter().
 */
function az-gardens_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'install_configure') {
    $form['site_information']['site_name']['#default_value'] = 'Alphabet Garden';
    $form['site_information']['site_mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
    $form['admin_account']['account']['name']['#default_value'] = 'admin';
    $form['admin_account']['account']['mail']['#default_value'] = 'admin@'. $_SERVER['HTTP_HOST'];
  }
}

/**
 * Reimplementation of system_theme_data(). The core function's static cache
 * is populated during install prior to active install profile awareness.
 * This workaround makes enabling themes in profiles/az-gardens/themes possible.
 */
function _az-gardens_system_theme_data() {
  global $profile;
  $profile = 'az-gardens';

  $themes = drupal_system_listing('\.info$', 'themes');
  $engines = drupal_system_listing('\.engine$', 'themes/engines');

  $defaults = system_theme_default();

  $sub_themes = array();
  foreach ($themes as $key => $theme) {
    $themes[$key]->info = drupal_parse_info_file($theme->filename) + $defaults;

    if (!empty($themes[$key]->info['base theme'])) {
      $sub_themes[] = $key;
    }

    $engine = $themes[$key]->info['engine'];
    if (isset($engines[$engine])) {
      $themes[$key]->owner = $engines[$engine]->filename;
      $themes[$key]->prefix = $engines[$engine]->name;
      $themes[$key]->template = TRUE;
    }

    // Give the stylesheets proper path information.
    $pathed_stylesheets = array();
    foreach ($themes[$key]->info['stylesheets'] as $media => $stylesheets) {
      foreach ($stylesheets as $stylesheet) {
        $pathed_stylesheets[$media][$stylesheet] = dirname($themes[$key]->filename) .'/'. $stylesheet;
      }
    }
    $themes[$key]->info['stylesheets'] = $pathed_stylesheets;

    // Give the scripts proper path information.
    $scripts = array();
    foreach ($themes[$key]->info['scripts'] as $script) {
      $scripts[$script] = dirname($themes[$key]->filename) .'/'. $script;
    }
    $themes[$key]->info['scripts'] = $scripts;

    // Give the screenshot proper path information.
    if (!empty($themes[$key]->info['screenshot'])) {
      $themes[$key]->info['screenshot'] = dirname($themes[$key]->filename) .'/'. $themes[$key]->info['screenshot'];
    }
  }

  foreach ($sub_themes as $key) {
    $themes[$key]->base_themes = system_find_base_themes($themes, $key);
    // Don't proceed if there was a problem with the root base theme.
    if (!current($themes[$key]->base_themes)) {
      continue;
    }
    $base_key = key($themes[$key]->base_themes);
    foreach (array_keys($themes[$key]->base_themes) as $base_theme) {
      $themes[$base_theme]->sub_themes[$key] = $themes[$key]->info['name'];
    }
    // Copy the 'owner' and 'engine' over if the top level theme uses a
    // theme engine.
    if (isset($themes[$base_key]->owner)) {
      if (isset($themes[$base_key]->info['engine'])) {
        $themes[$key]->info['engine'] = $themes[$base_key]->info['engine'];
        $themes[$key]->owner = $themes[$base_key]->owner;
        $themes[$key]->prefix = $themes[$base_key]->prefix;
      }
      else {
        $themes[$key]->prefix = $key;
      }
    }
  }

  // Extract current files from database.
  system_get_files_database($themes, 'theme');
  db_query("DELETE FROM {system} WHERE type = 'theme'");
  foreach ($themes as $theme) {
    $theme->owner = !isset($theme->owner) ? '' : $theme->owner;
    db_query("INSERT INTO {system} (name, owner, info, type, filename, status, throttle, bootstrap) VALUES ('%s', '%s', '%s', '%s', '%s', %d, %d, %d)", $theme->name, $theme->owner, serialize($theme->info), 'theme', $theme->filename, isset($theme->status) ? $theme->status : 0, 0, 0);
  }
}
