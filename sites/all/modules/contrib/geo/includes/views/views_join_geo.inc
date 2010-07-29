<?php // $Id: views_join_geo.inc,v 1.1 2009/12/09 17:34:02 vauxia Exp $

class views_join_geo extends views_join {

  function join($table, &$query) {

    if (!$gid = $this->definition['geo_gid']) {
      if (!$gid = $table['geo_gid']) return;
    }

    $geo = geo_load(array('gid' => $gid));

    if (!isset($query->geo_base)) {
      $query->geo_base = $geo;
      $query->geo_base->setTableName($this->left_table);
      if ($query->base_table == 'geo_data') $query->base_table = $table['table'];
    }
    else {
      $geo->setTableName($this->left_table .'__'. $geo->tableName());
    }

    // There's no reason to join on the same dataset.
    if ($query->geo_base->gid() == $geo->gid()) return;

    /*
    if ($this->left_table) {
      $left = $query->get_table_info($this->left_table);
      $output = " $this->type JOIN {" . $this->table . "} $table[alias] ON $left[alias].$this->left_field = $table[alias].$this->field";
    }
    else {
      // This can be used if left_field is a formula or something. It should be used only *very* rarely.
      $output = " $this->type JOIN {" . $this->table . "} $table[alias] ON $this->left_field = $table[alias].$this->field";
    }
    */

//    return " $this->type JOIN {" . $this->table . "} $table[alias] ON ". $geo->intersects($query->geo_base, $geo);
    return " $this->type JOIN {" . $this->table . "} ". $geo->tableName() . " ON ". $geo->intersects($query->geo_base, $geo);


  //  $query->table_queue['geo_data'] = $new_base;


   // if (!isset($query->tables[$new_base])) $query->tables[$new_base] = array();
//    $query->tables[$new_base] = array_merge($query->tables[$new_base], $query->tables['geo_data']);
 //   unset($query->table_queue['geo_data'], $query->tables['geo_data']);


  }
}

?>
