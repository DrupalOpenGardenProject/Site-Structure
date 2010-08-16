<?php
// $Id: tw.views_default.inc,v 1.1.2.22 2010/06/29 01:07:28 mikeryan Exp $

/**
 * @file
 * Views default views implementation
 *
 */

/**
 * Implementation of hook_default_view_views().
 */
function tw_views_default_views() {
  $views = array();

  // Go through each import table and create default views for them
  // Skip any without a primary key
  $sql = "SELECT tt.twtid,tt.tablename,tt.dbconnection,tt.view_name,COUNT(*) AS cnt
          FROM {tw_tables} tt
          INNER JOIN {tw_columns} tc ON tt.twtid=tc.twtid
          WHERE tt.provide_view=1 AND tc.primarykey=1
          GROUP BY tt.twtid,tt.tablename,tt.view_name,tt.dbconnection";
  $tblresult = db_query($sql);
  while ($tblrow = db_fetch_object($tblresult)) {
    // For a default view to be possible, the table must have a single primary key field
    if ($tblrow->cnt != 1) {
      continue;
    }

    $twtid = $tblrow->twtid;
    $tablename = $tblrow->tablename;
    $view_name = $tblrow->view_name;
    $dbconnection = $tblrow->dbconnection;
    if ($dbconnection == 'default') {
      $rawtablename = schema_unprefix_table($tablename);
      $cleantablename = $rawtablename;
    }
    else {
      $truedbname = tw_get_dbinfo($dbconnection, 'name');
      $rawtablename = tw_qualified_tablename($dbconnection, $tablename);
      $cleantablename = $truedbname . '_' . $tablename;
    }
    // Create a basic table view, with exclusion flags, for each import table
    $view = new view;
    $view->name = $view_name;
    $view->description = $tablename;
    $view->tag = 'tw';
    $view->view_php = '';
    $view->base_table = $rawtablename;
    $view->is_cacheable = FALSE;
    $view->api_version = 2;
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
    $handler = $view->new_display('default', $view_name, 'default');

    // Grab the available columns for this table (skip any marked ignore)
    $pk = NULL;
    $colnames = array();
    $sql = "SELECT colname, primarykey
            FROM {tw_columns}
            WHERE ignorecol=0 AND twtid=%d
            ORDER BY weight";
    $colresult = db_query($sql, $twtid);
    while ($colrow = db_fetch_object($colresult)) {
      $colnames[] = $colrow->colname;
      if ($colrow->primarykey) {
        $pk = $colrow->colname;
      }
    }

    // Add our columns to the fields
    $fields = array();
    foreach ($colnames as $colname) {
      $fields[$colname] = array(
        'id' => $colname,
        'table' => $rawtablename,
        'field' => $colname,
        'label' => $colname,
        'exclude' => 0,
        'relationship' => 'none',
      );
    }

    // Add columns for joined tables
    $sql = "SELECT twc2.colname, twt2.tablename
            FROM {tw_tables} twt1
            INNER JOIN {tw_columns} twc1 ON twt1.twtid=twc1.twtid
            INNER JOIN {tw_relationships} twr ON twc1.twcid=twr.leftcol AND twr.automatic=1
            INNER JOIN {tw_columns} twc2 ON twr.rightcol=twc2.twcid
            INNER JOIN {tw_tables} twt2 ON twc2.twtid=twt2.twtid
            WHERE twt1.twtid=%d";
    $result = db_query($sql, $twtid);
    while ($row = db_fetch_object($result)) {
      $colname = $row->colname;
      $colnames[] = $colname;
      $fields[$colname] = array(
        'id' => $colname,
        'table' => $row->tablename,
        'field' => $colname,
        'label' => $colname,
        'exclude' => 0,
        'relationship' => 'none',
        'override' => array(
          'button' => 'Override',
        ),
        'alter' => array(
          'alter_text' => 0,
          'text' => '',
          'make_link' => 0,
          'path' => '',
          'alt' => '',
          'prefix' => '',
          'suffix' => '',
          'help' => '',
          'trim' => 0,
          'max_length' => '',
          'word_boundary' => 1,
          'ellipsis' => 1,
          'strip_tags' => 0,
          'html' => 0,
        ),
      );
    }

    $handler->override_option('fields', $fields);
    $handler->override_option('access', array(
      'type' => 'perm',
      'perm' => TW_ACCESS,
    ));
    $handler->override_option('title', t('Contents of !tablename', array('!tablename' => $rawtablename)));
    $handler->override_option('header', t('This is a view of a raw database table. It may be ' .
      'sorted in various ways by clicking the column headers.

      If you identify a particular field that does not need to be used in views of this table, ' .
      'go to the <a href="!analyze_url">analysis page</a> ' .
      'and check the <em>Ignore</em> box for that field. It will then no longer appear here.',
      array('!analyze_url' => url("admin/content/tw/analyze/$twtid"))));
    $handler->override_option('header_format', '1');
    $handler->override_option('header_empty', 0);
    $handler->override_option('empty', 'There are no rows in this table.');
    $handler->override_option('empty_format', '1');
    $handler->override_option('items_per_page', 25);
    $handler->override_option('use_pager', '1');
    $handler->override_option('style_plugin', 'table');
    // Add our columns into the style options
    $columns = array();
    foreach ($colnames as $colname) {
      $columns[$colname] = $colname;
    }
    $info = array();
    foreach ($colnames as $colname) {
      $info[$colname] = array(
        'sortable' => 1,
        'separator' => '',
      );
    }
    $handler->override_option('style_options', array(
      'grouping' => '',
      'override' => 1,
      'sticky' => 1,
      'order' => 'asc',
      'columns' => $columns,
      'info' => $info,
      'default' => -1,
    ));
    $handler = $view->new_display('page', 'Page', 'page_1');
    $handler->override_option('path', "admin/content/tw/view/$view_name");
    $handler->override_option('menu', array(
      'type' => 'none',
      'title' => '',
      'weight' => 0,
    ));
    $handler->override_option('tab_options', array(
      'type' => 'none',
      'title' => '',
      'weight' => 0,
    ));
    $views[$view->name] = $view;
  }
  return $views;
}
