<?php
// $Id: az-gardens.profile,v 1.0.00 2010/08/11 11:06:23 fndtn357 Exp $

/**
 * Return an array of the modules to be enabled when this profile is installed.
 *
 * @return
 *   An array of modules to enable.
 *
 * An implementation of hook_profile_modules().    
 */
function az-gardens_profile_modules() {
    global $install_locale;
  // Default Drupal core modules
  $modules = array(
    'block',
    'color',
    'comment',
    'dblog',
    'filter',
    'help',
    'menu',
    'node',
    'path',
    'system',
    'taxonomy',
    'update',
    'user',
  // Contributed modules
    'admin',
    'admin_role',
    'content',
    'filefield',
    'imagefield',
    'link',
    'node_reference',
    'number',
    'option_widgets',
    'text',
    'user_reference',
    'ctools',
    'date',
    'date_api',
    'date_timexone',
    'date_tools',
    'feeds',
    'feeds_ui',
    'imageapi',
    'imageapi_gd',
    'imagecache',
    'advanced_help',
    'backup_migrate',
    'login_destination',
    'logintoboggan',
    'pathauto',
    'token',
    'jquery_ui',
    'jquery_plugins',
    'jquery_ui'
    'views',
    'views_ui',
  // Custom modules - Alphabet Garden modules
    'views_summary_alphabet_icons',
  );
  return $modules;
}

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile,
 *   and optional 'language' to override the language selection for
 *   language-specific profiles.
 *
 * Implementation of hook_profile_details().
 */
function az-gardens_profile_details() {
  return array(
    'name' => 'Alphabet Gardens',
    'description' => 'Alphabet Gardens is a community garden news feed that <ul><li>aggregates RSS/Atom news feeds</li><li>places community garden news on a map</li><li>provides search on it and</li><li>offers a way of organizing community garden news into channels and topics.</li></ul>By Drupal Open Garden Project.'
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
 * Perform any final installation tasks for this profile.
 *
 * The installer goes through the profile-select -> locale-select
 * -> requirements -> database -> profile-install-batch
 * -> locale-initial-batch -> configure -> locale-remaining-batch
 * -> finished -> done tasks, in this order, if you don't implement
 * this function in your profile.
 *
 * If this function is implemented, you can have any number of
 * custom tasks to perform after 'configure', implementing a state
 * machine here to walk the user through those tasks. First time,
 * this function gets called with $task set to 'profile', and you
 * can advance to further tasks by setting $task to your tasks'
 * identifiers, used as array keys in the hook_profile_task_list()
 * above. You must avoid the reserved tasks listed in
 * install_reserved_tasks(). If you implement your custom tasks,
 * this function will get called in every HTTP request (for form
 * processing, printing your information screens and so on) until
 * you advance to the 'profile-finished' task, with which you
 * hand control back to the installer. Each custom page you
 * return needs to provide a way to continue, such as a form
 * submission or a link. You should also set custom page titles.
 *
 * You should define the list of custom tasks you implement by
 * returning an array of them in hook_profile_task_list(), as these
 * show up in the list of tasks on the installer user interface.
 *
 * Remember that the user will be able to reload the pages multiple
 * times, so you might want to use variable_set() and variable_get()
 * to remember your data and control further processing, if $task
 * is insufficient. Should a profile want to display a form here,
 * it can; the form should set '#redirect' to FALSE, and rely on
 * an action in the submit handler, such as variable_set(), to
 * detect submission and proceed to further tasks. See the configuration
 * form handling code in install_tasks() for an example.
 *
 * Important: Any temporary variables should be removed using
 * variable_del() before advancing to the 'profile-finished' phase.
 *
 * @param $task
 *   The current $task of the install system. When hook_profile_tasks()
 *   is first called, this is 'profile'.
 * @param $url
 *   Complete URL to be used for a link or form action on a custom page,
 *   if providing any, to allow the user to proceed with the installation.
 *
 * @return
 *   An optional HTML string to display to the user. Only used if you
 *   modify the $task, otherwise discarded.
 */
