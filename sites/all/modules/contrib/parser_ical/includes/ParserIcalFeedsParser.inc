<?php
// $Id: ParserIcalFeedsParser.inc,v 1.1 2010/01/19 11:55:42 ekes Exp $

/**
 * Overridden version of FeedsDateTimeElement that supports iCal specific
 * parsing and repetition.
 *
 * @todo repeating date storage not iCal specific, could be moved to base class.
 */
class ParserIcalDateTimeElement extends FeedsDateTimeElement {
  public $repeat_vals = NULL;

  /**
   * Construct from an iCal VEVENT date array.
   */
  public function __construct($feed_element) {
    if (empty($feed_element['DTSTART']['datetime'])) {
      return;
    }
    include_once(drupal_get_path('module', 'date_api') .'/date_api_ical.inc');

    $timezone = $feed_element['DTSTART']['tz'];
    if (!empty($timezone)) {
      $timezone = new DateTimeZone($timezone);
    }
    $this->start = new FeedsDateTime($feed_element['DTSTART']['datetime'], $timezone);
    if (!empty($feed_element['DTEND']) && !empty($feed_element['DTEND']['datetime'])) {
      $this->end = new FeedsDateTime($feed_element['DTEND']['datetime'], $timezone);
    }
    if ($feed_element['DTSTART']['all_day']) {
      // All day event; remove time granularity, set to = from
      $this->start->setTime(0, 0, 0);
      $this->start->removeGranularity('hour');
      $this->start->removeGranularity('minute');
      $this->start->removeGranularity('second');
      $this->end = clone $this->start;
    }

    if (array_key_exists('RRULE', $feed_element) && !empty($feed_element['RRULE']) && module_exists('date_repeat')) {
      include_once('./'. drupal_get_path('module', 'date_repeat') .'/date_repeat_calc.inc');
      include_once('./'. drupal_get_path('module', 'date') .'/date_repeat.inc');
      // Explode the RRULE into parts so we can analyze it.
      $rrule = $feed_element['RRULE']['DATA'] . (!empty($feed_element['EXDATE']) ? "/n". $feed_element['EXDATE'] : "");
      // In current API the first variable, $field, is unused--may change?
      $form_values = date_ical_parse_rrule(NULL, $rrule);

      /**
       * Make sure we don't end up with thousands of values with RRULES
       * that have no UNTIL or COUNT.
       * @todo could be adjusted or made configurable later.
       * NOTE: This is not properly timezone converted; that's the least of its
       * problems.
       */
      $max = date_now();
      $max_repeats = 52;
      date_modify($max, '+5 years');
      $until = date_format($max, 'Y-m-d H:i:s');
      if (empty($form_values['COUNT']) && (empty($form_values['UNTIL']) || $until < $form_values['UNTIL']['datetime'])) {
        $form_values['UNTIL'] = array('datetime' => $until, 'tz' => 'UTC');
        $form_values['COUNT'] = $max_repeats;
      }
      elseif (empty($form_values['COUNT'])) {
        $form_values['COUNT'] = $max_repeats;
      }
      elseif (empty($form_values['UNTIL'])) {
        $form_values['UNTIL'] = array('datetime' => $until, 'tz' => 'UTC');
      }
      // Save these in the form_values format, which date can convert to an
      // rrule with date_api_ical_build_rrule()
      $this->repeat_vals = $form_values;
    }
  }

  /**
   * Overridden merge method to combine two iCal date elements.
   * Most of the heavy lifting still handled by parent merge method.
   */
  public function merge(FeedsDateTimeElement $other) {
    $ret = parent::merge($other);
    if (($other instanceof FeedsIcalDateTimeElement) && !$ret->repeat_vals && $other->repeat_vals) {
      $ret->repeat_vals = $other->repeat_vals;
    }
    return $ret;
  }

  /**
   * Build a node's date CCK field from our object.
   */
  public function buildDateField($node, $field_name) {
    parent::buildDateField($node, $field_name);
    if (empty($this->repeat_vals)) {
      return;
    }
    $field = content_fields($field_name);
    $node_field = $node->{$field_name}[0];
    $values = date_repeat_build_dates(NULL, $this->repeat_vals, $field, $node_field);
    $node->$field_name = $values;
  }
}

/**
 * Class definition for iCal date module Parser.
 *
 * Parses iCal feeds using the iCal parser included with the date module.
 */
class ParserIcalFeedsParser extends FeedsParser {

  /**
   * Parse content fetched by fetcher.
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    module_load_include('inc', 'parser_ical', 'parser_ical.dateapi');
    $result = _parser_ical_parse($batch->getRaw());
    $batch->setTitle($result['title']);
    $batch->setItems($result['items']);
    // also available description, calscale, timezone
  }

  /**
   * Return mapping sources.
   *
   * At a future point, we could expose data type information here,
   * storage systems like Data module could use this information to store
   * parsed data automatically in fields with a correct field type.
   */
  public function getMappingSources() {
    return array(
      'title' => array(
        'name' => t('Title'),
        'description' => t('Title of the feed item.'),
      ),
      'description' => array(
        'name' => t('Description'),
        'description' => t('Description of the feed item.'),
      ),
      // 'author' => t('Author'), // not implemented
      'timestamp' => array(
        'name' => t('Published date'),
        'description' => t('Published date as UNIX time UTC of the feed item.'),
      ),
      'url' => array(
        'name' => t('Item URL (link)'),
        'description' => t('URL of the feed item.'), // @todo check description
      ),
      'guid' => array(
        'name' => t('Item GUID'),
        'description' => t('Global Unique Identifier of the feed item.'),
      ),
      'tags' => array(
        'name' => t('Categories'),
        'description' => t('An array of categories that have been assigned to the feed item.'),
      ),
      'ical_date' => array(
         'name' => t('iCal Date'),
         'description' => t('iCal date associated with item as an array.'),
      ),
    );
  }
}
