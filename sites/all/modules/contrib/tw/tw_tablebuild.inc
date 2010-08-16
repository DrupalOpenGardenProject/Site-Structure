<?php
// $Id: tw_tablebuild.inc,v 1.1.2.19 2010/07/21 01:43:54 mikeryan Exp $

/**
 * @file
 * Shared functions used by tw's views hook implementations and exporter to
 * generate metadata for hook_views_data().
 */

/**
 * Return a views handler based on the column type.
 */
function _tw_views_handler($sqltype, $type) {
  preg_match('/^[a-zA-Z]+/', $sqltype, $matches);
  $coltype = tw_column_type($matches[0]);
  switch ($coltype) {
    case 'numeric':
      $filter = "views_handler_{$type}_numeric";
      break;
    default:
      if ($type == 'field') {
        $filter = 'views_handler_field';
      }
      else {
        $filter = "views_handler_{$type}_string";
      }
      break;
  }

  return $filter;
}

function _tw_generate_views_table_data($twtids = NULL, $export = FALSE) {
  $t = $export ? '_tw_t_wrap' : 't';
  $sql = "SELECT twtid, tablename, dbconnection
          FROM {tw_tables}";
  if (!is_null($twtids)) {
    // If a specific subset of tables are requested, add the appropriate
    // constraining WHERE clause
    $sql .= ' WHERE twtid IN (' . db_placeholders($twtids) . ')';
    $tblresult = db_query($sql, $twtids);
  }
  else {
    $tblresult = db_query($sql);
  }
  // Use slightly different helptext when generating for export vs. tw data hook.
  // This is overridden by the schema definition, if it exists.
  $help = $t('Table managed by the Table Wizard');
  if ($export) {
   $help =  $t('Table definition exported by the Table Wizard.');
  }

  $tables = array();
  while ($tblrow = db_fetch_object($tblresult)) {
    // Table Wizard stores the true DB table name - Drupal knows the name without
    // the table prefix (if there is one). We'll use the true name for display
    $tablename = $tblrow->tablename;
    // Load the schema so we can get table comments.
    $schema = drupal_get_schema($tablename);
    $dbconnection = $tblrow->dbconnection;

    $qualtablename = tw_qualified_tablename($dbconnection, $tablename);

    if ($dbconnection == 'default') {
      $rawtablename = schema_unprefix_table($tablename);
      $disptablename = $tablename;
    }
    else {
      $rawtablename = $qualtablename;
      $disptablename = $qualtablename;
      // Only do this if qualification support is active
      if ($qualtablename != $tablename) {
        $dbconnection = 'default';
      }
    }
    $twtid = $tblrow->twtid;
    $table = array();
    // Add each viewable column to the table definition
    // Note that we include the primary key column even if it's empty - this means
    // the table is totally empty, and we need to have at least one column present
    // to prevent errors in the view
    $sql = "SELECT twcid, colname, primarykey, secure, coltype
            FROM {tw_columns}
            WHERE twtid=%d AND ignorecol=0
            ORDER BY weight";
    $colresult = db_query($sql, $twtid);
    $pk = array();
    while ($colrow = db_fetch_object($colresult)) {
      $colname = $colrow->colname;
      if (isset($schema['fields'][$colname]['description'])) {
        $help = $export ?
          str_replace("'", "\\'", $schema['fields'][$colname]['description']) :
          $schema['fields'][$colname]['description'];
      }
      else {
        $help = $disptablename . '.' . $colname;
      }
      $table[$colname] = array(
        'title' => $t($colname),
        'help' => $t($help),
        // TODO: Truncate text at 80 characters.
        // TODO: Better yet, do some jQuery magic to expand to the full text
        'field' => array(
          'handler' => _tw_views_handler($colrow->coltype, 'field'),
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => _tw_views_handler($colrow->coltype, 'filter'),
          'allow empty' => TRUE,
        ),
        'argument' => array(
          'handler' => _tw_views_handler($colrow->coltype, 'argument'),
        ),
        'sort' => array(
          'handler' => 'views_handler_sort'
        ),
      );
      if ($colrow->primarykey) {
        $pk[] = $colname;
      }
    }
    // Any table with a single primary key column can be a base table
    if (count($pk) == 1) {
      $description =
        !empty($schema['description']) ?
          $t($export ?
              str_replace("'", "\\'", $schema['description']) :
              $schema['description']) :
          $help;
      $table['table'] = array(
        'base' => array(
          'field' => $pk[0],
          'title' => $t('Database table @tablename', array('@tablename' => $disptablename)),
          'help' => $description,
          'weight' => 10,
          'database' => ($tablename == $qualtablename) ? $dbconnection : NULL,
        ),
      );
    }
    $table['table']['group'] = $t($disptablename);

    $tables[$rawtablename] = $table;
  }
  return $tables;
}

function _tw_generate_views_relationship_data($tables, $twtids = NULL, $export = FALSE) {
  $t = $export ? '_tw_t_wrap' : 't';
  $where = is_null($twtids) ? '' : 'WHERE twt1.twtid IN (' . db_placeholders($twtids) . ')';
  // Now that all tables are present, fill in relationships defined by foreign keys
  $sql = "SELECT twt1.tablename AS tbl1, twc1.colname AS col1, twt1.dbconnection AS dbcon1, twt2.tablename AS tbl2,
                  twc2.colname AS col2, twt2.twtid AS twtid2, twt2.dbconnection AS dbcon2,
                  twr.automatic
          FROM {tw_relationships} twr
          INNER JOIN {tw_columns} twc1 ON twr.leftcol=twc1.twcid
          INNER JOIN {tw_tables} twt1 ON twc1.twtid=twt1.twtid
          INNER JOIN {tw_columns} twc2 ON twr.rightcol=twc2.twcid
          INNER JOIN {tw_tables} twt2 ON twc2.twtid=twt2.twtid
          $where
          ORDER BY tbl1, col1, tbl2, col2";
  $result = is_null($twtids) ? db_query($sql) : db_query($sql, $twtids);

  // To allow multiple joins from one tbl/col, must use an alias and
  // 'relationship field' for the left side
  $i = 0;
  while ($row = db_fetch_array($result)) {
    extract($row);
    $rawtbl1 = tw_qualified_tablename($dbcon1, schema_unprefix_table($tbl1));
    $rawtbl2 = tw_qualified_tablename($dbcon2, schema_unprefix_table($tbl2));
    if ($automatic) {
      // Use Views joins (automatically include right-table fields in left-table views)
      $disptablename = $dbcon2 . '_' . $tbl2;
      $tables[$rawtbl2]['table']['join'][$rawtbl1] = array(
        'table' => $rawtbl2,
        'left_field' => $col1,
        'field' => $col2,
      );
    }
    else {
      // Use Views relationships (right-table must be explicitly added to a view)
      if (!isset($tables[$rawtbl1][$col1]['relationship'])) {
        $tables[$rawtbl1][$col1]['relationship'] = array(
          'base' => $rawtbl2,
          'base field' => $col2,
          'label' => $t("Join @table1 to @table2", array('@table1' => $tbl1, '@table2' => $tbl2)),
        );
      }
      else {
        $i++;
        $mungedcol = $col1 . '_' . $i;
        $tables[$rawtbl1][$mungedcol] = $tables[$rawtbl1][$col1];
        $tables[$rawtbl1][$mungedcol]['title'] = $t("@column (joins to @table)", array('@column' => $col1, '@table' => $tbl2));
        $tables[$rawtbl1][$mungedcol]['real field'] = $col1;
        $tables[$rawtbl1][$mungedcol]['relationship'] = array(
          'base' => $rawtbl2,
          'base field' => $col2,
          'relationship field' => $col1,
          'label' => $t("Join @table1 to @table2", array('@table1' => $tbl1, '@table2' => $tbl2)),
        );
      }
    }
  }

  return $tables;
}
