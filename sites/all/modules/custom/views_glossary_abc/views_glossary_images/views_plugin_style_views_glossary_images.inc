<?php
// $Id$

/**
 * @file
 *
 * Override a views style for views summary.
 */
class views_plugin_style_views_glossary_images extends views_plugin_style_summary {
  function option_definition() {
    $options = parent::option_definition();
    $options['inline'] = array('default' => FALSE);
    $options['separator'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['inline'] = array(
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['inline']),
      '#title' => t('Display items inline'),
    );
    $form['separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Separator'),
      '#default_value' => $this->options['separator'],
    );
  }
}
