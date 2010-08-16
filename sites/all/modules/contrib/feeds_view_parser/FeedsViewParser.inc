<?php
// $Id: FeedsViewParser.inc,v 1.17 2010/08/12 10:40:29 adityakg Exp $

/**
 * @file Implementation of View Parser plugin
 */

/**
 * Parses the view output (in PHP Array format).
 * @package feeds
 * @author aditya
 */
class FeedsViewParser extends FeedsParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    // Get the view result manually by executing it.

    $config = $this->_getConfigurationDetails();
    $source_config = $source->getConfigFor($this);

    $result_rows = array();
    $view = views_get_view($config['view_name']);

    // @todo check access here

    // ensure that the view has been built properly.
    if (is_object($view)) {
      // @todo load arguments into view here.
      // @todo ensure that the display has been initialized properly by now.

      // prepare the initial view to get the total pages.
      $view->set_display($config['display_id']);
      $view->set_arguments($source_config['arguments']);
      $view->preview();

      // get the total pages.
      $pager = $view->query->pager;

      $total_pages = intval($pager->get_total_items() / $pager->options['items_per_page']);
      $total_pages += $pager->get_total_items() % $pager->options['items_per_page'] > 0 ? 1 : 0;

      // @todo delete after fix. this is a hack for query backend that has not implemented their pager function yet!
      if (count($view->result) != 0 && $total_pages == 0) {
      	$total_pages = 1;
      }

      // execute the view for every pages
      for ($i=0; $i < $total_pages ; $i++) {
        // @todo can other people add content and add the number of pages when this
        // @todo is being aggregated?

        $view->set_current_page($i);
        $view->set_display($config['display_id']);
        $view->set_arguments($source_config['arguments']);

        //$view->pre_execute();
        $groups = $view->preview();

        // populate the result_rows array
        foreach ($groups as $group) {
          foreach ($group as $row) {
            $result_rows[] = $row;
          }
        }

        // destroy and rebuild the views
        $view->destroy();
        if ($i != $total_pages-1) { //prevent rebuilt if it is already the last page
          $view = views_get_view($config['view_name']);
        }
      }
    }
    else {
      // do nothing, this block exists only to
      // cater for the possibility of broken view
      // @todo throw exception?
    }

    // dpm($result_rows);
    // Populate batch.
    $batch->setItems($result_rows);
  }

  /**
   * Define default configuration.
   *
   * The default is the first view-display pair found
   * @todo as there is no configuration, so obviously there will be no default
   *       change this when configuration is added.
   */
  public function configDefaults() {
    // refresh php_view_list
    if (!isset($this->php_view_list)) {
      $this->php_view_list = array();
      $views = views_get_all_views();

      foreach ($views as $view) {
        $has_php = FALSE;
        foreach ($view->display as $display) {
          if ($display->display_plugin == 'php_array') {
            //create appropriate view details for execution later
            $this->php_view_list[] = array(
              'view_name' => $view->name,
              'display_id' => $display->id,
            );
          }
        }
      }
    }

    if (count($this->php_view_list) != 0) {
      return array('source' => $this->php_view_list[0]['view_name'] . ', ' . $this->php_view_list[0]['display_id']);
    }

    // @todo return exception here?
    return NULL;
  }

  /**
   * Configuration form to choose which view to be imported.
   */
  public function configForm(&$form_state) {
    $form = array();

    // Help text for the config form.
    $items = array(
      t('Import from view (Views) output.'),
      t('Don\'t forget to add PHP Array display into your view. Otherwise, it would not be shown here.'),
    );
    $form['help']['#value'] = '<div class="help">'. theme('item_list', $items) .'</div>';

    // Refresh the array of view list if it is not yet initialized.
    // @todo delete this? php_view_list should have been initialized in the configDefaults method
    if (!isset($this->php_view_list)) {
      $this->php_view_list = array();

      // fetch the views that contain PHP array display.
      $views = views_get_all_views();

      foreach ($views as $view) {
        $has_php = FALSE;
        foreach ($view->display as $display) {
          if ($display->display_plugin == 'php_array') {
            //create appropriate view details for execution later
            $this->php_view_list[] = array(
              'view_name' => $view->name,
              'display_id' => $display->id,
            );

            // create the appropriate string list for options
            $select_list[] = $view->name . ', ' . $display->id;
          }
        }
      }
    }

    // construct the array for the option list
    foreach ($this->php_view_list as $value) {
      $select_list[] = $value['view_name'] . ', ' . $value['display_id'];
    }

    $form['source'] = array(
      '#type' => 'select',
      '#title' => t('View'),
      '#description' => t('Specify the view that you want to use here. They are in the format of view_name, display_id'),
      '#options' => !empty($select_list) ? drupal_map_assoc($select_list) : array(),
      '#default_value' => $this->config['source']
    );

    return $form;
  }

  /**
   * Get mapping source
   */
  public function getMappingSources() {
    $source = array();
    $batch = feeds_importer($this->id)->fetcher->getBatch();

    // execute view to get the fields
    // @todo special case for grouping - DONE?

    //$view = views_get_view($batch->getViewName());

    $config = $this->_getConfigurationDetails();

    $view = views_get_view($config['view_name']);

    // get the default display plugin to retrieve the fields
    // try the default display first
    $display = $view->display['default'];

    // if the fields option is overriden, get the field option from the display instead
    if (isset($view->display[$config['display_id']]->display_options['fields'])) {
      $display = $view->display[$config['display_id']];
    }

    /*
    foreach ($view->display as $key => $value) {
      // if display has not been initialized, assign it to 'default' display
      if ($value->display_plugin == 'default' && $display == NULL) {
        $display = $value;
      }
      // or if the fields option is overriden in the display
      else if ($value->id == $config['display_id'] && isset($value->display_options['fields'])) {
        $display = $value;
      }
    }
    */

    // get the list of fields from view
    foreach ($display->display_options['fields'] as $fname => $value) {
      // @todo make sure whether to use id or field, for now use the key
      $source[$fname] = array(
        'name' => t($fname),
        'description' => t($value['label']),
      );
    }

    return $source;
  }

  /**
   * Override parent::getSourceElement() to use only lower keys.
   */
  public function getSourceElement($item, $element_key) {
    $element_key = drupal_strtolower($element_key);
    return isset($item[$element_key]) ? $item[$element_key] : '';
  }

  /**
   * Define defaults.
   */
  public function sourceDefaults() {
    return array(
      'source' => $this->config['source'],
      'arguments' => '',
    );
  }

  /**
   * Source form.
   *
   * Show mapping configuration as a guidance for import form users.
   */
  public function sourceForm($source_config) {
    $form = array();
    $form['#weight'] = -10;

    $items = array(
      t('The following view will be imported.'),
      t('You can change the view/display to be imported in the Feeds Importer Configuration'),
    );
    $form['help']['#value'] = '<div class="help">'. theme('item_list', $items) .'</div>';

    $form['source'] = array(
      '#type' => 'textfield',
      '#title' => t('View/Display'),
      '#description' => t('The view name and the display id (format: view_name, display_id)'),
      '#default_value' => $this->config['source'],
      '#disabled' => TRUE,
    );

    $form['arguments'] = array(
        '#type' => 'textfield',
        '#title' => t('View Arguments'),
        '#description' => t('The argument to be passed into the View'),
        '#default_value' => isset($source_config['arguments']) ? $source_config['arguments'] : '',
    );
    return $form;
  }

  /**
   * Tokenize and get the configuration details
   * @return array with 'view_name' and 'display_id' element
   */
  protected function _getConfigurationDetails() {
    $s = $this->config['source'];

    $array = array();
    $array['view_name'] = trim(strtok($s, ','));
    $array['display_id'] = trim(strtok(' '));

    return $array;
  }
}
