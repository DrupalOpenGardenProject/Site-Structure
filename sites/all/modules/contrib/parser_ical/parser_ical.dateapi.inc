<?php
// $Id: parser_ical.dateapi.inc,v 1.4 2010/01/19 11:55:42 ekes Exp $

/**
 * @file
 *  parser_ical include for actually parsing feed.
 */

/**
 * Parse iCal feeds.
 *
 * Pinched pretty much directly from version 1 for now.
 */
function _parser_ical_parse($feed_content) {
  include_once(drupal_get_path('module', 'date_api') .'/date_api_ical.inc');
  $feed_folded = explode("\n", $feed_content);
  $ical_parsed = date_ical_parse($feed_folded);

  // TODO, should we change this to a foreach() instead of just picking
  // out the first one in case there is more than one CALENDAR grouping
  // in a feed? Not sure that ever actually happens.

  $ical = $ical_parsed[0]; // Pick out the first CALENDAR group.

  // Any or all of these items could be missing, so always use isset() to test.
  $parsed_source = array();
  // Detect the title
  $parsed_source['title'] = isset($ical['X-WR-CALNAME']) ? $ical['X-WR-CALNAME'] : '';
  // Detect the description
  $parsed_source['description'] = isset($ical['X-WR-CALDESC']) ? $ical['X-WR-CALDESC'] : '';
  $parsed_source['link'] = ''; // @todo do we have one from the feed?
  $parsed_source['date']['calscale'] = isset($ical['CALSCALE']) ? $ical['CALSCALE'] : '';
  $parsed_source['date']['timezone'] = isset($ical['X-WR-TIMEZONE']) ? $ical['X-WR-TIMEZONE'] : '';
  $parsed_source['items'] = array();
  if (array_key_exists('VEVENT', $ical)) {
    foreach ($ical['VEVENT'] as $event) {
      $item = array();
      $item['title'] = $event['SUMMARY'];
      $item['description'] = isset($event['DESCRIPTION']) ? $event['DESCRIPTION'] : '';
      $item['author'] = ''; // @todo can we get this, what format
      $item['url'] = isset($event['URL']) ? $event['URL'] : '';

      // Make sure a valid timestamp is created.
      $item['timestamp'] = time();
      if (isset($event['DTSTAMP'])) {
        $date = date_ical_date($event['DTSTAMP']);
        if (date_is_valid($date, DATE_OBJECT)) {
          $item['timestamp'] = date_format($date, 'U');
        }
      }

      $item['guid'] = isset($event['UID']) ? $event['UID'] : ''; // intention
      $item['tags'] = isset($event['CATEGORIES']) ? explode(',', $event['CATEGORIES']) : array();
      $item['ical_date'] = new ParserIcalDateTimeElement($event);
      $parsed_source['items'][] = $item;
    }
  }
  return $parsed_source;
}
