<?php 
/**
 * @author: Nazrul Kamaruddin <nazroll@gmail.com>
 * @since:  2009
 * 
 */

class FeedsGMapsParser extends FeedsParser {
    /*
     * Parsers a raw string and returns a Feed object from it
     */
	  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
	  	feeds_include_library('common_syndication_parser.inc', 'common_syndication_parser');	  	
	  	$xml = simplexml_load_string($batch->getRaw());
	  	$items = $xml->channel->item;
	  	foreach ($items as $item) {
        $parsed_item['title'] = trim((string)$item->title);
        $parsed_item['description'] = trim((string)$item->description);
        $parsed_item['timestamp'] = _parser_common_syndication_parse_date($item->pubDate);
        $guid = (array)$item->guid;
        $parsed_item['guid'] = $guid[0];
        $point = (string)$item->children('http://www.georss.org/georss');
        if ($point) {
          $parsed_item['point'] = trim($point);
          list($latitude, $longitude) = explode(" ", $parsed_item['point']);
          $parsed_item['longitude'] = $longitude;
          $parsed_item['latitude'] = $latitude;
        }
        $parsed_items[] = $parsed_item;
	  	}
	  	$parsed_feed['title'] = (string)$xml->channel->title[0];
	  	$parsed_feed['link'] = (string)$xml->channel->link[0];
	  	$parsed_feed['description'] = (string)$xml->channel->description[0];
	  	
	  	$batch->setTitle($parsed_feed['title']);
      $batch->setDescription($parsed_feed['description']);
      $batch->setLink($parsed_feed['link']);
	  	if (is_array($parsed_items)) {
	  		$batch->setItems($parsed_items);
	  	}
	  }
	  
    /* 
     * Return mapping GeoRSS sources
     */
    public function getMappingSources() { 
        return array(
           'title' => array(
               'name' => t('Title'),
               'description' => t('Title of the feed item.')
           ),
           'guid' => array(
               'name' => t('Item GUID'),
               'description' => t('GUID of the feed item.')
           ),
           'description' => array(
               'name' => t('Description'),
               'description' => t('Description of the feed item.')
           ),           
           'point' => array(
               'name' => t('Point'),
               'description' => t('Geolocation data of the feed item.')
           ),
           'longitude' => array(
               'name' => t('Longitude'),
               'description' => t('Longitude geolocation point of the feed item.'),
           ),
           'latitude' => array(
               'name' => t('Latitude'),
               'description' => t('Latitude geolocation point of the feed item.'),
           ),
           'timestamp' => array(
               'name' => t('Published date'),
               'description' => t('Publised date of the feed item.')
           ),
        );
    }
}
