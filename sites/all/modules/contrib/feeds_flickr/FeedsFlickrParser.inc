<?php
// $Id: FeedsFlickrParser.inc,v 1.1.2.1 2010/05/12 14:41:19 dragonwize Exp $
/**
 * @file
 *  Feeds parser class for Flickr.

/**
 * Class definition for Flickr Flicker Parser.
 *
 * Parses RSS and Atom feeds.
 */
class FeedsFlickrParser extends FeedsSimplePieParser {

  /**
   * Parse the extra mapping sources provided by this parser.
   */
  protected function parseExtensions(&$item, $simplepie_item) {
    // Extract media fields out of the enclosure.
    $enclosure = $simplepie_item->get_enclosure();
    if (empty($enclosure) || !is_object($enclosure)) {
      return;
    }

    $item['media_link']     = $enclosure->get_link();
    $item['media_width']    = $enclosure->get_width();
    $item['media_height']   = $enclosure->get_height();
    $item['media_title']    = $enclosure->get_title();
    $item['media_desc']     = $enclosure->get_description();
    $item['media_credit']   = $enclosure->get_credit();
    $item['media_category'] = $enclosure->get_category();
    $item['media_thumbnail_75x75'] = $enclosure->get_thumbnail();
    $item['media_thumbnail_100']   = str_replace('_s.', '_t.', $item['media_thumbnail_75x75']);
    $item['media_thumbnail_240']   = str_replace('_s.', '_m.', $item['media_thumbnail_75x75']);
    $item['media_thumbnail_500']   = str_replace('_s.', '.', $item['media_thumbnail_75x75']);
    $item['media_thumbnail_1024']  = str_replace('_s.', '_b.', $item['media_thumbnail_75x75']);
  }

  /**
   * Add the extra mapping sources provided by this parser.
   */
  public function getMappingSources() {
    return parent::getMappingSources() + array(
      'media_title' => array(
        'name' => t('Media: Title'),
        'description' => t('Media:title field.'),
      ),
      'media_desc' => array(
        'name' => t('Media: Description'),
        'description' => t('Media:description field.'),
      ),
      'media_credit' => array(
        'name' => t('Media: Credit'),
        'description' => t('Media:credit field.'),
      ),
      'media_category' => array(
        'name' => t('Media: Category'),
        'description' => t('Media:category field.'),
      ),
      'media_link' => array(
        'name' => t('Media: Link'),
        'description' => t('Media:content url field.'),
      ),
      'media_width' => array(
        'name' => t('Media: Width'),
        'description' => t('Media:content width field.'),
      ),
      'media_height' => array(
        'name' => t('Media: Height'),
        'description' => t('Media:content height field.'),
      ),
      'media_thumbnail_75x75' => array(
        'name' => t('Media: Thumbnail 75x75'),
        'description' => t('Media:thumbnail field sized at 75x75 pixels.'),
      ),
      'media_thumbnail_100' => array(
        'name' => t('Media: Thumbnail 100'),
        'description' => t('Media:thumbnail field sized at 100 pixels on the longest side.'),
      ),
      'media_thumbnail_240' => array(
        'name' => t('Media: Thumbnail 240'),
        'description' => t('Media:thumbnail field sized at 240 pixels on the longest side.'),
      ),
      'media_thumbnail_500' => array(
        'name' => t('Media: Thumbnail 500'),
        'description' => t('Media:thumbnail field sized at 500 pixels on the longest side.'),
      ),
      'media_thumbnail_1024' => array(
        'name' => t('Media: Thumbnail 1024'),
        'description' => t('Media:thumbnail field sized at 1024 pixels on the longest side.'),
      ),
     );
  }

}
