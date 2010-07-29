<?php
// $Id: geotaxonomy.views.inc,v 1.1.2.1.2.1 2010/06/24 14:04:47 tmcw Exp $
/**
 * @file
 * Geotaxonomy views definitions, exposes the geotaxonomy table and a count-per-term field.
 */

/**
 * Implementation of hook_views_data().
 */
function geotaxonomy_views_data() {
  $data['term_geo']['table']['group'] = t('Taxonomy Geo');
  $data['term_geo']['table']['join'] = array(
    'term_data' => array(
      'left_field' => 'tid',
      'field' => 'tid',
    ),
    'node' => array(
      'left_table' => 'term_node',
      'left_field' => 'tid',
      'field' => 'tid',)
  );
  
  $data['term_geo']['lat'] = array(
    'title' => t('Latitude'),
    'help' => t('The decimal latitude of this term'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );
  $data['term_geo']['lon'] = array(
    'title' => t('Longitude'),
    'help' => t('The decimal longitude of this term'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );
  $data['term_geo']['bound_top'] = array(
    'title' => t('Top bound'),
    'help' => t('The decimal top bound for this term'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );
  $data['term_geo']['bound_right'] = array(
    'title' => t('Right bound'),
    'help' => t('The decimal right bound for this term'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );
  $data['term_geo']['bound_bottom'] = array(
    'title' => t('Bottom bound'),
    'help' => t('The decimal bottom bound for this term'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );
  $data['term_geo']['bound_left'] = array(
    'title' => t('Left bound'),
    'help' => t('The decimal left bound for this term'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );
  $data['term_geo']['geometry'] = array(
    'title' => t('Geometry'),
    'help' => t('Geometry data stored as WKT in this term'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  $data['term_geo']['unique_term'] = array(
    'title' => t('Unique id/location'),
    'help' => t('Only show one of each location/id pair.'),
    'filter' => array(
      'handler' => 'geotaxonomy_handler_filter_unique',
    ),
    'real field' => 'tid',
  );
  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 */
function geotaxonomy_views_data_alter(&$data) {
  $data['term_data']['node_count'] = array(
    'title' => t('Node count for term'),
    'help' => t('Count the nodes of this term and optionally its subterms'),
    'field' => array(
      'handler' => 'geotaxonomy_handler_field_term_node_count',
    ),
    'real field' => 'tid',
  );
  $data['term_data']['tid_geo']['relationship'] = array(
    'title' => t('Geo data for term.'),
    'help' => t('Relate term data to geo data.'),
    'label' => t('Relate term data to geo data.'),
    'base' => 'term_geo',
    'base field' => 'tid',
    'relationship field' => 'tid',
  );
}

/**
 * Implementation of hook_views_handlers()
 */
function geotaxonomy_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'geotaxonomy') . '/views',
    ),
    'handlers' => array(
      // term count handler
      'geotaxonomy_handler_field_term_node_count' => array(
        'parent' => 'views_handler_field',
      ),
      'geotaxonomy_handler_filter_unique' => array(
        'parent' => 'views_handler_filter',
      ),
    ),
  );
}
