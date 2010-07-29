<?php

/**
 * A tag-cloud style view.
 */
class views_cloud_plugin_style_cloud extends views_plugin_style {
  function option_definition() {
    $options = parent::option_definition();
    $options['randomize'] = array('default' => TRUE);
    $options['weight_field'] = array('default' => NULL);
    $options['sizes'] = array('default' => '7');
    $options['font_size'] = array('default' => '');
    $options['hide_weight_field'] = array('default' => TRUE);
    $options['algorithm'] = array('default' => 'log');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $options = array();
  
    $fields = $this->display->handler->get_handlers('field');

    foreach ($fields as $field => $handler) {
      $supported_handlers = array(
        'views_handler_field_numeric',
        'views_handler_field_date',
        'content_handler_field_multiple', // CCK.
        'term_node_count_handler_field', // Term Node Count.
      );
      if (in_array($handler->definition['handler'], $supported_handlers)) {
        // CCK uses 'content_handler_field_multiple' for everything.
        if ($handler->definition['handler'] == 'content_handler_field_multiple') {
          $content_field = content_fields($handler->definition['content_field_name']);
          if (!in_array($content_field['type'], array('number_integer', 'number_float', 'number_decimal', 'date', 'datetime', 'datestamp'))) {
            continue;
          }
        }

        if ($label = $handler->label()) {
          $options[$field] = $label;
        }
        else {
          $options[$field] = $handler->ui_name();
        }
      }
    }

    if (empty($options)) {
      $options[''] = t('No available numeric fields');
    }

    $form['weight_field'] = array(
      '#type' => 'select',
      '#title' => t('Cloud weight field'),
      '#required' => TRUE,
      '#description' => t('This field will be used to control the size of each row in the cloud.'),
      '#options' => $options,
      '#default_value' => $this->options['weight_field'],
    );

    $form['hide_weight_field'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide weight field'),
      '#description' => t('This field used to weight individual items in the view will not be output.'),
      '#default_value' => $this->options['hide_weight_field'],
    );

    $form['randomize'] = array(
      '#type' => 'checkbox',
      '#title' => t('Randomize the order of items'),
      '#description' => t("This setting respects the View's sort order when limiting large paged lists, but shuffles each list of items when displayed on the page."),
      '#default_value' => $this->options['randomize'],
    );

    $form['sizes'] = array(
      '#type' => 'select',
      '#title' => t('Number of font sizes'),
      '#options' => drupal_map_assoc(range(4,10)),
      '#default_value' => $this->options['sizes'],
      '#description' => t('Increasing the number of sizes increases the number of possible sizes an item may be.'),
    );

    $form['font_size'] = array(
      '#type' => 'select',
      '#title' => t('Font size adjustment'),
      '#options' => array(
        '0.5' => t('50%'),
        '0.6' => t('60%'),
        '0.7' => t('70%'),
        '0.8' => t('80%'),
        '0.9' => t('90%'),
        '' => t('None'),
        '1.1' => t('110%'),
        '1.2' => t('140%'),
        '1.3' => t('130%'),
        '1.4' => t('140%'),
        '1.5' => t('150%'),
      ),
      '#default_value' => $this->options['font_size'],
      '#description' => t('Note that changing this value may affect your site differently depending on your theme.'),
    );

    $form['algorithm'] = array(
      '#type' => 'select',
      '#title' => t('Weight to size algorithm'),
      '#description' => t("Select the item weight sizing algorithm, linear or logarithmic. Logarithmic emphasizes the relative weight of items."),
      '#options' => array('log' => t('Logarithmic'), 'linear' => t('Linear')),
      '#default_value' => $this->options['algorithm'],
    );

  }
}
