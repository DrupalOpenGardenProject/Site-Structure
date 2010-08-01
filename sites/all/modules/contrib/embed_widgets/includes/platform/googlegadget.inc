<?php
// $Id: googlegadget.inc,v 1.7.2.5 2009/09/09 03:08:02 jtsnow Exp $

class googlegadget extends widget_platform {
  
  public $name;
  public $id;
  public $description;
  public $format;
  public $filename;
   
  static public function info() {
    return array(
      'title' => t('Google Gadget'),
      'description' => t('Embed on iGoogle or any other Google Gadget container.'),
      'formats' => array('iframe', 'flash'),
      'share_method' => 'link',
    );
  }
  
  static public function theme() {
    return array(
      'googlegadget' => array(
        'template' => 'googlegadget',
        'arguments' => array('widget' => NULL),
        'path' => drupal_get_path('module', 'embed_widgets') . "/includes/platform"
      ),
    );
  }
  
  static public function code($widget) {
    //$format_info = call_user_func($this->format . '::info');
    switch($widget->format) {
      case 'iframe':
        $code = '<script src="http://www.gmodules.com/ig/ifr?url=' . $widget->get_content_url() . '&amp;synd=open&amp;w=' . $widget->get_variable('width') . '&amp;h=' . $widget->get_variable('height') . '&amp;title=' . $widget->get_variable('title') . '&amp;border=%23ffffff%7C3px%2C1px+solid+%23999999&amp;output=js"></script>';
        break;
      case 'flash':
        $code = '';
        break;
    }
    
    return $code;
  }
  
  static public function link(embed_widget $widget) {
    return 'http://fusion.google.com/ig/add?synd=open&source=ggyp&moduleurl=' . $widget->get_platform_url();
  }
  
  static public function live_preview($widget) {
    switch($widget->format) {
      case 'iframe':
        if (function_exists($widget->format . '::embed_code_noscript')) {
          $code = call_user_func($widget->format . '::embed_code_noscript', $widget);
        }
        break;
      case 'flash':
        $code = '';
        break;
    }
    
    return $code;
  }
  
  static public function platform_file($widget) {
    drupal_set_header('Content-type: text/xml; charset=utf-8');
    return theme('googlegadget', $widget);
  }
  
  static public function settings_form() {
    $form = array();
    $form['google_gadget'] = array(
      '#type' => 'fieldset',
      '#title' => t('Google Gadget Settings'),
      '#description' => t("The settings below are used as the default settings for Google Gadgets. Some of these fields are required to submit your gadget to Google's content directory. See !link for more information.", array('!link' => l('this page', 'http://code.google.com/apis/gadgets/docs/legacy/publish.html#Submitting'))),
      '#collapsible' => TRUE,
    );
    $form['google_gadget']['embed_widgets_google_gadgets_author'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#default_value' => variable_get('embed_widgets_google_gadgets_author', ''),
      '#size' => 25,
      '#maxlength' => 60,
      '#description' => t('The author of the gadget.'),
    );
    $form['google_gadget']['embed_widgets_google_gadgets_author_email'] = array(
      '#type' => 'textfield',
      '#title' => t('Author E-mail'),
      '#default_value' => variable_get('embed_widgets_google_gadgets_author_email', ''),
      '#size' => 30,
      '#maxlength' => 100,
      '#description' => t("You should not use a personal email address because of spam."),
    );
    $form['google_gadget']['embed_widgets_google_gadgets_author_affiliation'] = array(
      '#type' => 'textfield',
      '#title' => t('Author Affiliation'),
      '#default_value' => variable_get('embed_widgets_google_gadgets_author_affiliation', ''),
      '#size' => 30,
      '#maxlength' => 100,
      '#description' => t('String such as "Google" that indicates the author\'s affiliation.'),
    );
    $form['google_gadget']['embed_widgets_google_gadgets_author_location'] = array(
      '#type' => 'textfield',
      '#title' => t('Author Location'),
      '#default_value' => variable_get('embed_widgets_google_gadgets_author_location', ''),
      '#size' => 30,
      '#maxlength' => 100,
      '#description' => t('The author\'s geographical location, such as "Mountain View , CA, USA ".'),
    );
    return $form;
  }
  

}

/**
 * Process variables for embed_widgets_google_gadgets_page.tpl.php
 */
function template_preprocess_googlegadget(&$variables) {
  global $base_url;
  $widget = $variables['widget'];
  $variables['title'] = check_plain($widget->title);
  $variables['description'] = check_plain($widget->description);
  $variables['title_url'] = $base_url;
  $variables['height'] = check_plain($widget->get_variable('height'));
  $variables['width'] = check_plain($widget->get_variable('width'));
//  $variables['screenshot'] = check_plain($variables['content']['settings']['google-gadget']['screenshot']);
//  $variables['thumbnail'] = check_plain($variables['content']['settings']['google-gadget']['thumbnail']);
  $variables['author'] = check_plain(variable_get('embed_widgets_google_gadgets_author', ''));
  $variables['author_email'] = check_plain(variable_get('embed_widgets_google_gadgets_author_email', ''));
  $variables['author_location'] = check_plain(variable_get('embed_widgets_google_gadgets_author_location', ''));
  $variables['author_affiliation'] = check_plain(variable_get('embed_widgets_google_gadgets_author_affiliation', ''));
  $variables['url'] = check_url($widget->get_content_url());
}
