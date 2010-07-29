<?php
// $Id: geotaxonomy_handler_field_term_node_count.inc,v 1.1 2009/09/22 23:13:13 alexb Exp $
/**
 * @file
 * Class definition for geotaxonomy_handler_field_term_node_count.
 */

class geotaxonomy_handler_field_term_node_count extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['depth'] = array('default' => 0);
    return $options;
  }

  /**
   * Add field form.
   */
  function options_form(&$form, &$form_state) {
    $form['depth'] = array(
      '#type' => 'weight',
      '#title' => t('Depth'),
      '#default_value' => $this->options['depth'],
      '#description' => t('The depth will match nodes tagged with terms in the hierarchy. Negative depths match parents instead of children.'),
    );
  }

  function query() {
    $this->ensure_my_table();
    $theterm = 'total_term_nodes_tid';
    $this->query->add_field($this->table_alias, $this->real_field, $theterm);

    $subquery = "\n  SELECT COUNT(DISTINCT tn.nid) FROM {term_node} tn\n";
    $where = "  WHERE tn.tid = $theterm\n";
    $last = "tn";

    // Largely copied from views_handler_argument_term_node_tid_depth.
    if ($this->options['depth'] > 0) {
      $subquery .= "    LEFT JOIN {term_hierarchy} th ON th.tid = tn.tid\n";
      $last = "th";
      foreach (range(1, abs($this->options['depth'])) as $count) {
        $subquery .= "    LEFT JOIN {term_hierarchy} th$count ON $last.parent = th$count.tid\n";
        $where .= "    OR th$count.tid = $theterm\n";
        $last = "th$count";
      }
    }
    else if ($this->options['depth'] < 0) {
      foreach (range(1, abs($this->options['depth'])) as $count) {
        $subquery .= "    LEFT JOIN {term_hierarchy} th$count ON $last.tid = th$count.parent\n";
        $where .= "    OR th$count.tid = $theterm\n";
        $last = "th$count";
      }
    }

    $this->field_alias = $this->query->add_field(NULL, "($subquery$where)", "total_term_nodes_count");
  }
}