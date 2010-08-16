<?php
// $Id: FeedsXPathParser.inc,v 1.1.2.1 2010/06/28 04:04:13 twistor Exp $


define('FEEDS_XPATH_PARSER_HTML', 0);
define('FEEDS_XPATH_PARSER_XML', 1);
define('FEEDS_XPATH_PARSER_REGEX', 2);

/**
 * @file
 *
 * Provides the Feeds XPath Parser.
 */

/**
 * Takes a document and runs user provided XPath queries against it.
 */
class FeedsXPathParser extends FeedsParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    $raw = $batch->getRaw();

    $config = $source->getConfigFor($this);
    $rawXML = array_keys(array_filter($config['rawXML']));

    $dom = new DOMDocument();

    if ($config['parser_type'] == FEEDS_XPATH_PARSER_XML) {
      $success = @$dom->loadXML($raw);
    }
    elseif ($config['parser_type'] == FEEDS_XPATH_PARSER_HTML) {
      $success = @$dom->loadHTML($raw);
    }
    elseif ($config['parser_type'] == FEEDS_XPATH_PARSER_REGEX) {
      drupal_set_message(t('Regex support not implemented yet.'), 'error');
      return;
    }

    if (!$success) {
      drupal_set_message(t('There was an error parsing the document.
        Please make sure you have selected the correct parser.'), 'error');
      return;
    }

    $xml = simplexml_import_dom($dom);
    unset($dom);

    $mappings = feeds_importer($this->id)->processor->config['mappings'];

    $queries = array();
    $sources = array();

    foreach ($mappings as $mapping) {
      $source = $mapping['source'];
      if (trim($config[$source])) {
       $sources[] = $source;
       $queries[] = $config[$source];
      }
    }

    $results = array();
    foreach ($queries as $key => $query) {
      $result = @$xml->xpath($query);
      if (!$result) {
        drupal_set_message(t('There was an error with one of your XPath queries.
          Make sure the syntax is valid.'), 'error');
        return;
      }
      $results[$sources[$key]] = $result;
    }
    unset($xml);

    $output = array();
    foreach ($results as $source => $items) {
      if (!isset($count) || $count == count($items)) {
        foreach ($items as $key => $item) {
          if (in_array($source, $rawXML)) {
            $item = $item->asXML();
          }
          else {
            $item = (string) $item;
          }
          if (isset($output[$key])) {
            $output[$key] = array_merge(array($source => $item), $output[$key]);
          }
          else {
            $output[$key] = array($source => $item);
          }
        }
        $count = count($items);
      }
      else {
        drupal_set_message(t('Mismatching results.
          Queries must produce the same number of items.'), 'error');
        return;
      }
    }

    $batch->setItems($output);
  }

  /**
   * Define defaults.
   */
  public function sourceDefaults() {
    return array('XML' => 0);
  }

  /**
   * Source form.
   */
  public function sourceForm($source_config) {
    $form = array();
    $form['#weight'] = -10;

    $mappings = feeds_importer($this->id)->processor->config['mappings'];
    $sources = $uniques = array();

    foreach ($mappings as $mapping) {
      $sources[] = $mapping['source'];
      if ($mapping['unique']) {
        $uniques[] = $mapping['source'];
      }
    }

    $items = array(
      format_plural(count($uniques),
        t('Field <strong>!column</strong> is mandatory and considered unique: only one item per !column value will be created.',
          array('!column' => implode(', ', $uniques))),
        t('Fields <strong>!columns</strong> are mandatory and values in these columns are considered unique: only one entry per value in one of these columns will be created.',
          array('!columns' => implode(', ', $uniques)))),
    );

    $form['help']['#value'] = '<div class="help">' . theme('item_list', $items) . '</div>';

    $form['parser_type'] = array(
      '#title'    => t('Select the parsing engine to use'),
      '#type'     => 'radios',
      '#options'   => array('HTML', 'XML'),
      '#default_value' => isset($source_config['parser_type']) ?
                          $source_config['parser_type'] : FEEDS_XPATH_PARSER_HTML,
    );

    foreach ($sources as $source) {
      $form[$source] = array(
        '#type'          => 'textfield',
        '#title'         => $source,
        '#description'   => t('The query string to run.'),
        '#default_value' => isset($source_config[$source]) ? $source_config[$source] : '',
      );
    }

    $form['rawXML'] = array(
      '#type'          => 'checkboxes',
      '#title'         => t('Select the queries you would like to return raw XML/HTML
                            (not used for REGEX))'),
      '#options'       => array_combine($sources, $sources),
      '#default_value' => isset($source_config['rawXML']) ? $source_config['rawXML'] : array(),
    );

    return $form;
  }
}
