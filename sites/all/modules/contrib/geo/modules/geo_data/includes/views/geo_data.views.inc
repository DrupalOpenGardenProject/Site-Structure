<?php // $Id: geo_data.views.inc,v 1.2 2010/01/13 18:26:24 vauxia Exp $

function geo_data_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'geo_data') .'/includes/views',
    ),
    'handlers' => array(
      'views_handler_field_geo_data' => array(
        'parent' => 'content_handler_field_multiple',
      ),
    ),
  );
}
