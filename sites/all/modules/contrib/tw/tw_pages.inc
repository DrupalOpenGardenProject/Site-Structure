<?php
// $Id: tw_pages.inc,v 1.1.2.59 2010/06/29 01:11:07 mikeryan Exp $
/**
 * @file
 * Table Wizard menu callbacks
 */

define('TW_COLS_ALL', 1);
define('TW_COLS_IGNORE', 2);
define('TW_COLS_NOIGNORE', 3);

/**
 * Page callback for sources form.
 */
function tw_sources() {
  return drupal_get_form('tw_sources_form');
}

/**
 * Sources form definition.
 */
function tw_sources_form($form_state) {
  $form['description'] = array(
    '#prefix' => '<div>',
    '#value' => t('Tables managed by the Table Wizard module are listed here, each with the name of the
      table used to store the data, and statistics on the amount of data. Click the table name
      to view and edit information on the table, including its fields. For tables with
      default views, click on the view name to view the data in the table.'),
    '#suffix' => '</div>',
  );

  // To add the "select all" checkbox to the following tables, we call
  // theme_table_select_header_cell.
  // This will include the tableselect.js file. We don't need the output.
  theme('table_select_header_cell');

  $sql = "SELECT COUNT(DISTINCT(dbconnection)) FROM {tw_tables} WHERE dbconnection <> 'default'";
  $extconns = db_result(db_query($sql));
  if ($extconns >= 1) {
    $connheader = array('data' => t('Connection'), 'field' => 'twt.dbconnection', 'sort' => 'asc');
    $nameheader = array('data' => t('Table name'), 'field' => 'twt.tablename');
  }
  else {
    $nameheader = array('data' => t('Table name'), 'field' => 'twt.tablename', 'sort' => 'asc');
  }
  if ($extconns >= 1) {
    $form['header'] = array(
      '#type' => 'value',
      '#value' => array(
        array('data' => '', 'class' => 'select-all'),
        $connheader,
        $nameheader,
        array('data' => t('View name'), 'field' => 'twt.view_name'),
        array('data' => t('Row count')),
      ),
    );
  }
  else {
    $form['header'] = array(
      '#type' => 'value',
      '#value' => array(
        array('data' => t(''), 'class' => 'select-all'),
        $nameheader,
        array('data' => t('View name'), 'field' => 'twt.view_name'),
        array('data' => t('Row count')),
      ),
    );
  }

  $sql = "SELECT twt.twtid, twt.tablename, twt.dbconnection, twt.provide_view, twt.view_name,
            COUNT(twc.twcid) AS pkcnt
          FROM {tw_tables} twt
          LEFT JOIN {tw_columns} twc ON twt.twtid=twc.twtid AND primarykey=1
          GROUP BY twt.twtid, twt.tablename, twt.dbconnection, twt.provide_view, twt.view_name";
  if ($extconns >= 1) {
    // If no header has been clicked, sort by both connection and tablename
    if (isset($_GET['order'])) {
      $tablesort = tablesort_sql($form['header']['#value']);
    }
    else {
      $tablesort = " ORDER BY twt.dbconnection ASC, twt.tablename ASC";
    }
  }
  else {
    $tablesort = tablesort_sql($form['header']['#value']);
  }
  $result = db_query($sql . $tablesort);
  $checks = array();
  $last_connection = 'default';
  while ($row = db_fetch_object($result)) {
    $checks[$row->twtid] = '';
    $form['twtid'][$row->twtid] = array('#value' => $row->twtid);
    // Make sure we're using the default connection - l() may query the alias table
    if ($last_connection != 'default') {
      db_set_active('default');
      $last_connection = 'default';
    }
    if ($extconns >= 1) {
      $form['dbconnection'][$row->twtid] = array('#value' => $row->dbconnection);
    }
    $form['tablename'][$row->twtid] = array('#value' =>
      l($row->tablename, 'admin/content/tw/analyze/' . $row->twtid, array('html' => TRUE)));
    // Only link to the default view if it exists
    if ($row->provide_view == 1 && $row->view_name) {
      $form['view_name'][$row->twtid] = array('#value' =>
        l($row->view_name, 'admin/content/tw/view/' . $row->view_name, array('html' => TRUE)));
    }
    else {
      $form['view_name'][$row->twtid] = array('#value' => '');
    }
    if ($last_connection != $row->dbconnection) {
      db_set_active($row->dbconnection);
      $last_connection = $row->dbconnection;
    }
    $prefixed = db_prefix_tables('{' . $row->tablename . '}');
    if ($prefixed != $row->tablename && !db_table_exists($row->tablename)) {
      drupal_set_message(t('Table %tablename is subject to Drupal prefixing, but
        the physical table does not have a prefix. To work properly with Table Wizard,
        add an element to $db_prefix setting the prefix for this table to an empty string.',
        array('%tablename' => $row->tablename)));
      $rowcount = t('N/A');
    }
    else {
      $sql = 'SELECT COUNT(*) FROM ' . tw_quote_identifier('{' . $row->tablename . '}');
      $rowcount = db_result(db_query($sql));
    }
    $form['rowcount'][$row->twtid] = array('#value' => $rowcount);
  }
  if ($last_connection != 'default') {
    db_set_active('default');
  }

  $form['checks'] = array('#type' => 'checkboxes', '#options' => $checks);
  $form['#theme'] = 'tw_sources';
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Remove selected tables'),
  );
  $form['export'] = array(
    '#type' => 'submit',
    '#value' => t('Export views definitions for selected tables'),
  );

  // Keep each type's fields apart
  $form['#tree'] = TRUE;

  // Note that fieldset names ('existing', 'delimited', ...) are the source type names
  $sourcefieldsets = module_invoke_all('tw_form');
  $form = array_merge($form, $sourcefieldsets);
  // Support file uploads
  $form['#attributes'] = array('enctype' => 'multipart/form-data');

  return $form;
}

function theme_tw_sources($form) {
  $output = drupal_render($form['description']);

  if (isset($form['twtid']) && is_array($form['twtid'])) {
    foreach (element_children($form['twtid']) as $twtid) {
      $row = array();
      // Don't show the table id
      $null = drupal_render($form['twtid']);
      $row[] = drupal_render($form['checks'][$twtid]);
      if (isset($form['dbconnection'][$twtid])) {
        $row[] = drupal_render($form['dbconnection'][$twtid]);
      }
      $row[] = drupal_render($form['tablename'][$twtid]);
      $row[] = drupal_render($form['view_name'][$twtid]);
      $row[] = drupal_render($form['rowcount'][$twtid]);
      $rows[] = $row;
    }
  }
  $header = $form['header']['#value'];
  if (!isset($rows)) {
    $rows[] = array(array('data' => t('No tables have been added..'),
                          'colspan' => count($header)));
  }
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($form['delete']);
  $output .= drupal_render($form['export']);
  $output .= drupal_render($form);
  return $output;
}

/**
 * Sources form submit handler.
 */
function tw_sources_form_submit($form, &$form_state) {
  $type = $form_state['clicked_button']['#parents'][0];
  if ($type == 'delete') {
    $tables = array();
    foreach ($form_state['values']['checks'] as $twtid => $value) {
      if ($value) {
        $sql = "SELECT dbconnection,tablename FROM {tw_tables} WHERE twtid=%d";
        $row = db_fetch_object(db_query($sql, $twtid));
        $tables[] = $row->dbconnection . '.' . $row->tablename;
      }
    }
    $count = count($tables);
    if ($count > 3) {
      tw_remove_tables_batch($tables);
    }
    else {
      tw_remove_tables($tables);
    }
    drupal_set_message(t('Removed @tables: !list',
      array('@tables' => format_plural($count, t('table'), t('tables'), $tables), '!list' => theme('item_list', $tables))));
  }
  elseif ($type == 'export') {
    $twtids = array_values(array_filter($form_state['values']['checks']));
    $form_state['redirect'] = 'admin/content/tw/export/' . implode(',', $twtids);
  }
  else {
    // Submit hooks return arrays of tablenames they're bringing in
    $values = $form_state['values'][$type];
    if (isset($values['skip_full_analysis'])) {
      $skip_full_analysis = $values['skip_full_analysis'];
    }
    else {
      $skip_full_analysis = FALSE;
    }
    if (isset($values['provide_view'])) {
      $provide_view = $values['provide_view'];
    }
    else {
      $provide_view = 0;
    }
    if (isset($values['view_name'])) {
      $view_name = $values['view_name'];
    }
    else {
      $view_name = '';
    }
    $tableset = module_invoke_all("tw_form_submit_$type", $values);
    if (count($tableset) == 1) {
      tw_add_tables($tableset, $skip_full_analysis, $provide_view, $view_name);
    }
    else {
      if ($view_name) {
        drupal_set_message(t('A view name can only be provided when adding a single table.'));
      }
      tw_add_tables_batch($tableset, $skip_full_analysis, $provide_view);
    }
  }
}

/**
 * Add a fieldset into the import form, for identifying where to obtain source data.
 */
function tw_tw_form() {
  $fieldsets['existing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add existing tables'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $fieldsets['existing']['uploadhelp'] = array(
      '#prefix' => '<div>',
      '#value' => t('Add tables to the Table Wizard.'),
      '#suffix' => '</div>',
  );

  // Build list of tables we already manage
  $excludes = array();
  $sql = "SELECT * FROM {tw_tables}";
  $tblresult = db_query($sql);
  while ($tblrow = db_fetch_object($tblresult)) {
    $tblname = $tblrow->tablename;
    // Exclude the table itself...
    $excludes[$tblrow->dbconnection][$tblname] = $tblname;
  }

  // Add tables from any available connections
  global $db_url;
  if (!is_array($db_url)) {
    $connlist = array('default' => $db_url);
  }
  else {
    $connlist = $db_url;
  }
  // We assume the default is first
  foreach ($connlist as $dbconnection => $url) {
    if ($dbconnection == 'default') {
      $defaulturl = $url;
    }
    db_set_active($dbconnection);
    global $db_type;
    if ($db_type == 'mysql' || $db_type == 'mysqli') {
      $sql = 'SHOW TABLES';
    }
    else if ($db_type == 'pgsql') {
      $sql = 'SELECT tablename FROM pg_tables ORDER BY tablename';
    }
    else {
      drupal_set_message(t('Unrecognized database type %dbtype', array('%dbtype' => $db_type)));
      return $fieldsets;
    }
    $result = db_query($sql);
    $options = array();
    while ($row = db_fetch_array($result)) {
      foreach ($row as $tablename) {
        $unprefixed = schema_unprefix_table($tablename);

        // Skip those we're already managing
        if (isset($excludes[$dbconnection][$unprefixed])) {
          continue;
        }
        // If we're in the default connection, skip tables which weren't prefixed
        global $db_prefix;
        if ($dbconnection == 'default' && $db_prefix && $tablename == $unprefixed) {
          continue;
        }
        // If we're in a connection that's not the default, but is using the
        // same database as the default, skip tables which were prefixed
        if ($dbconnection != 'default' && $url == $defaulturl && $tablename != $unprefixed) {
          continue;
        }
        $options[$unprefixed] = $unprefixed;
      }
    }

    if (!empty($options)) {
      $fieldsets['existing']['lists'][$dbconnection] = array(
          '#type' => 'select',
          '#title' => t('Available tables in %connection connection', array('%connection' => $dbconnection)),
          '#options' => $options,
          '#multiple' => TRUE,
          '#size' => min(20, count($options)),
          '#description' => t('Tables which are not currently managed
            by the Table Wizard or otherwise already made available to Views'),
      );
    }
  }
  db_set_active('default');

  $fieldsets['existing']['skip_full_analysis'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip full analysis'),
    '#description' => t('When tables are added, they are analyzed not only for what
      columns and primary keys are present, but for the ranges of values each column
      contains. This can take a long time for large tables - check this button to skip
      the value analysis.'),
    '#default_value' => FALSE,
  );

  $fieldsets['existing']['provide_view'] = array(
    '#type' => 'checkbox',
    '#title' => t('Provide default view'),
    '#description' => t('Provide a default view of the table data. Note that the view
      will only be available if the table has a single-column primary key.'),
    '#default_value' => TRUE,
  );

  $fieldsets['existing']['view_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Default view name'),
    '#length' => 32,
    '#default_value' => '',
    '#description' => t('If <em>Provide default view</em> is checked and a single table is
      being added, the name to use for the default view of that table. If left blank and
      <em>Provide default view</em> is checked, each selected table will have a default
      view with the same name as the table name.'),
  );

  $fieldsets['existing']['existingsubmit'] = array(
      '#type' => 'submit',
      '#value' => t('Add tables'),
  );
  return $fieldsets;
}

/**
 * Implementation of hook_tw_form_submit_<type>.
 */
function tw_tw_form_submit_existing($values) {
  $tablenames = array();
  foreach ($values['lists'] as $dbconnection => $tablelist) {
    foreach ($tablelist as $tablename) {
      $tablename = $dbconnection . '.' . $tablename;
      $tablenames[] = $tablename;
      drupal_set_message(t('Added table %tablename to the Table Wizard.',
        array('%tablename' => $tablename)));
    }
  }

  return $tablenames;
}


/**
 * Menu callback function.
 * TODO: Flag any available FKs that are not indexed.
 */
function tw_analysis($form_state, $twtid, $flag=TW_COLS_NOIGNORE) {
  $row = db_fetch_object(db_query("SELECT *
                                   FROM {tw_tables}
                                   WHERE twtid=%d",
                                  $twtid));
  $tablename = $row->tablename;
  $dbconnection = $row->dbconnection;
  $provide_view = $row->provide_view;
  $view_name = $row->view_name;

  if (isset($_GET['reanalyze'])) {
    tw_perform_analysis($tablename, $dbconnection);
    drupal_set_message(t('%tablename analyzed', array('%tablename' => $tablename)));
  }

  $form['twtid'] = array('#type' => 'value', '#value' => $twtid);
  $form['tablename'] = array('#type' => 'value', '#value' => $tablename);

  switch ($flag) {
    case TW_COLS_ALL:
      $flaglabel = t('All fields');
      break;
    case TW_COLS_IGNORE:
      $flaglabel = t('Ignored fields only');
      break;
    case TW_COLS_NOIGNORE:
      $flaglabel = t('Non-ignored fields only');
      break;
  }
  $form['provide_view'] = array(
    '#type' => 'checkbox',
    '#title' => t('Provide default view'),
    '#description' => t('Provide a default view of the table data. Note that the view
      will only be available if the table has a single-column primary key.'),
    '#default_value' => $row->provide_view,
  );

  $form['view_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Default view name'),
    '#length' => 32,
    '#default_value' => $row->view_name,
    '#description' => t('If <em>Provide default view</em> is checked and a single table is
      being added, the name to use for the default view of that table. If left blank and
      <em>Provide default view</em> is checked, each selected table will have a default
      view with the same name as the table name.'),
  );


  $form['help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Help'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['help']['help1'] = array(
    '#prefix' => '<div>',
    '#value' => t('Fields in the table are listed below, with some information
      on the range and type of values each field contains. Comments may be entered to
      document each field individually, and fields deemed unnecessary can be marked
      <b>Ignore</b> to omit them from views based on this table.'),
    '#suffix' => '</div>',
  );

  $form['help']['help3'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>View table contents</b> goes to the Table View page for this table.
      You may find it helpful to open this link in a new window, to browse the data in context
      while figuring out its meaning for the comments here.'),
    '#suffix' => '</div>',
  );

  $form['help']['fields'] = array(
    '#prefix' => '<div>',
    '#value' => t('These are the fields in the table below:'),
    '#suffix' => '</div>',
  );
  $form['help']['fieldname'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>Field name</b> - The name of the field in the database table.'),
    '#suffix' => '</div>',
  );

  $form['help']['ignore'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>Ignore</b> - Checking this box for a field will omit that field from the
      table view. A primary key field cannot be ignored - it is needed for the view to work.
      Note that, since Table Wizard does not provide a default view for a table whose views
      implementation is provided by another module (such as node), for such tables this
      only affects the filter on this page.'),
    '#suffix' => '</div>',
  );

  $form['help']['empty'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>Empty</b> - Indicates whether this field is empty for all rows of the table.'),
    '#suffix' => '</div>',
  );

  $form['help']['pk'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>PK</b> - Indicates that this field is the primary key of the table.'),
    '#suffix' => '</div>',
  );

  $form['help']['fk'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>Foreign key</b> - Check this box to make the field available for use
      in table relationships.'),
    '#suffix' => '</div>',
  );

  $form['help']['type'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>Type</b> - The Drupal schema type of the field.'),
    '#suffix' => '</div>',
  );

  $form['help']['strlength'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>Text length</b> - The range of text lengths in this field, if it\'s
      a text field.'),
    '#suffix' => '</div>',
  );

  $form['help']['range'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>Range of values</b> - The range of values in the field, from lowest to highest'),
    '#suffix' => '</div>',
  );

  $form['help']['comments'] = array(
    '#prefix' => '<div>',
    '#value' => t('<b>Comments</b> - Description of the field.'),
    '#suffix' => '</div>',
  );

  $form['title'] = array('#value' => t('Analysis of %table', array('%table' => $tablename)));
  $form['header'] = array(
    '#type' => 'value',
    '#value' => array(
      array('data' => t('Field name')),
      array('data' => t('Ignore')),
      array('data' => t('Empty')),
      array('data' => t('PK')),
      array('data' => t('Foreign key')),
      array('data' => t('Type')),
      array('data' => t('Text length')),
      array('data' => t('Range')),
      array('data' => t('Comments')),
    ),
  );

  $colcount = 0;
  $emptycount = 0;
  $result = db_query("SELECT *
                      FROM {tw_columns}
                      WHERE twtid=%d
                      ORDER BY weight",
                      $twtid);

  $availablefks = array();
  $availablefkenable = array();
  $ignoredcols = array();
  $ignoreenable = array();
  $cols = array();
  $pks = array();
  $pksenable = array();
  while ($row = db_fetch_object($result)) {
    $colname = $row->colname;
    $colcount++;
    if ($row->isempty) {
      $emptycount++;
    }
    // Display this column if:
    //  Asked to see all columns, or
    //  Asked to see ignored columns, and the column is ignored, or
    //  Ask to see non-ignored columns (the default), and the column is not being ignored
    if (($flag == TW_COLS_ALL) ||
       (($flag == TW_COLS_IGNORE) && $row->ignorecol) ||
       (($flag == TW_COLS_NOIGNORE) && !$row->ignorecol)) {
      $cols[] = $colname;
      $form['colname'][$colname] = array('#value' => $colname);
      $ignoredcols[$colname] = '';
      if ($row->ignorecol) {
        $ignoreenable[] = $colname;
      }
      $form['empty'][$colname] = array('#value' => $row->isempty ? t('Yes') : '');
      $pks[$colname] = '';
      if ($row->primarykey) {
        $pksenable[] = $colname;
      }
      $availablefks[$colname] = '';
      if ($row->availablefk) {
        $availablefkenable[] = $colname;
      }

      $form['currtype'][$colname] = array('#value' => $row->coltype);

      if (tw_column_type($row->coltype) == 'text') {
        $form['lengths'][$colname] = array('#value' =>
          $row->maxlength ? $row->minlength . '-' . $row->maxlength : ''
        );

        $form['values'][$colname] = array(
          '#attributes' => array('style' => 'white-space: normal'),
          '#prefix' => '<div style="white-space: normal">',
          '#value' =>
            $row->maxlength ? substr(check_plain($row->minstring), 0, 40) . '<hr />' .
              substr(check_plain($row->maxstring), 0, 40) : '',
          '#suffix' => '</div>',
        );
      }
      else {
        $form['lengths'][$colname] = array('#value' => '');
        $form['values'][$colname] = array('#value' =>
          $row->maxvalue ? $row->minvalue . '-' . $row->maxvalue : ''
        );
      }
      $form['comments'][$colname] = array(
        '#type' => 'textarea',
        '#default_value' => $row->comments,
        '#cols' => 45,
        '#rows' => 3,
        '#resizable' => FALSE,
      );
    }
  }

  $form['primarykey'] = array(
    '#type' => 'checkboxes',
    '#options' => $pks,
    '#default_value' => $pksenable,
  );

  $form['availablefk'] = array(
    '#type' => 'checkboxes',
    '#options' => $availablefks,
    '#default_value' => $availablefkenable,
  );

  $form['ignorecol'] = array(
    '#type' => 'checkboxes',
    '#options' => $ignoredcols,
    '#default_value' => $ignoreenable,
  );

  $form['cols'] = array(
    '#type' => 'value',
    '#value' => $cols,
  );

  $form['colcounts'] = array('#value' =>
    t('%emptycount of %colcount fields have no data for any row.',
      array('%emptycount' => $emptycount, '%colcount' => $colcount)));
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit changes'),
  );

  // Don't check for PK in the NOIGNORE case, it won't be there
  if ($flag != TW_COLS_IGNORE) {
    if (count($pksenable) == 0) {
      drupal_set_message(t('%tablename has no primary key defined. A single-field primary
        key is necessary to use this table as the base table for a view.',
        array('%tablename' => $tablename)));
    }
    elseif (count($pksenable) > 1) {
      drupal_set_message(t('%tablename has a multiple-field primary key. A single-field primary
        key is necessary to use this table as the base table for a view.',
        array('%tablename' => $tablename)));
    }
  }

  if (strlen($tablename) > 32) {
    drupal_set_message(t('%tablename is more than 32 characters long. Although the default
      view for this table works, in versions of Views up through at least 2.5 you cannot
      create your own views based on this table. See
      <a href="@issuelink">http://drupal.org/node/437070</a> for
      more information.',
      array('%tablename' => $tablename, '@issuelink' => 'http://drupal.org/node/437070')));
  }

  return $form;
}

/**
 * Theme analysis form.
 */
function theme_tw_analysis($form) {
  $title = drupal_render($form['title']);
  $twtid = $form['twtid']['#value'];
  $tablename = $form['tablename']['#value'];
  $provide_view = $form['provide_view']['#value'];
  $view_name = $form['view_name']['#value'];
  drupal_set_title($title);
  $output = '<div class="tw_analyze_links">';
  $output .= '<b>Operations on this table: </b>';
  $output .= l(t('Reanalyze'),
               "admin/content/tw/analyze/$twtid/",
               array('html' => TRUE, 'query' => 'reanalyze=1'));
  if ($provide_view) {
    $output .=  ' | ' . l(t('View table contents'),
                 "admin/content/tw/view/$view_name/",
                 array('html' => TRUE));
  }
  $output .= '</div>';
  $output .= '<div>' . drupal_render($form['colcounts']) . '</div>';

  $output .= drupal_render($form['provide_view']);
  $output .= drupal_render($form['view_name']);

  $output .= drupal_render($form['help']);

  if (isset($form['colname']) && is_array($form['colname'])) {
    foreach (element_children($form['colname']) as $colname) {
      $row = array();
      $row[] = drupal_render($form['colname'][$colname]);
      // Remove ignore toggle for the primary key
      if ($form['primarykey'][$colname]['#value']) {
        unset($form['ignorecol'][$colname]);
      }
      $row[] = drupal_render($form['ignorecol'][$colname]);
      $row[] = drupal_render($form['empty'][$colname]);
      $row[] = drupal_render($form['primarykey'][$colname]);
      $row[] = drupal_render($form['availablefk'][$colname]);
      $row[] = drupal_render($form['currtype'][$colname]);
      $row[] = drupal_render($form['lengths'][$colname]);
      $row[] = drupal_render($form['values'][$colname]);
      $row[] = drupal_render($form['comments'][$colname]);
      $rows[] = $row;
    }
  }

  $header = $form['header']['#value'];
  if (!isset($rows)) {
    $rows[] = array(array('data' => t('There are no fields to display.'),
                          'colspan' => count($header)));
  }

  $output .= theme('table', $header, $rows);
  $output .= drupal_render($form);

  return $output;
}

/**
 * Implementation of hook_submit().
 */
function tw_analysis_submit($form, &$form_state) {
  $twtid = $form_state['values']['twtid'];
  $provide_view = $form_state['values']['provide_view'];
  $view_name = $form_state['values']['view_name'];
  foreach ($form_state['values']['cols'] as $key => $colname) {
    $newignore = $form_state['values']['ignorecol'][$colname] ? 1 : 0;
    $newprimarykey = $form_state['values']['primarykey'][$colname] ? 1 : 0;
    $newavailablefk = $form_state['values']['availablefk'][$colname] ? 1 : 0;
    $newcomment = $form_state['values'][$colname];
    db_query("UPDATE {tw_columns}
              SET ignorecol=%d, primarykey=%d, availablefk=%d, comments='%s'
              WHERE twtid=%d AND colname='%s'",
             $newignore, $newprimarykey, $newavailablefk, $newcomment, $twtid, $colname);
  }

  db_query("UPDATE {tw_tables}
            SET provide_view=%d, view_name='%s'
            WHERE twtid=%d",
           $provide_view, $view_name, $twtid);

  // The views cache needs to be flushed to make new tables and default views available.
  views_invalidate_cache();

  // And also rebuild menus, so links to the default view work
  menu_rebuild();

  drupal_set_message(t('Your changes have been saved'));
}

/**
 * Page callback for relationships form.
 */
function tw_relationships() {
  return drupal_get_form('tw_relationships_form');
}

/**
 * Relationships form definition.
 */
function tw_relationships_form($form_state) {
  $form['description'] = array(
    '#prefix' => '<div>',
    '#value' => t('Define relationships between tables, enabling the creation
      of views joining those tables. Each relationship is based on matching a field
      in an initial (base) table to a field in a related table. To make a field
      available for use in relationships, visit the analysis page for the table and
      check the <b>Available key</b> checkbox for that field.'),
    '#suffix' => '</div>',
  );

  // To add the "select all" checkbox to the following tables, we call
  // theme_table_select_header_cell.
  // This will include the tableselect.js file. We don't need the output.
  theme('table_select_header_cell');

  $form['header'] = array(
    '#type' => 'value',
    '#value' => array(
      array('data' => '', 'class' => 'select-all'),
      array('data' => t('Base table field'), 'field' => 'lefttable', 'sort' => 'asc'),
      array('data' => t('Related table field'), 'field' => 'righttable', 'sort' => 'asc'),
      array('data' => t('Relationship type'), 'field' => 'automatic'),
    ),
  );

  $sql = "SELECT COUNT(*) FROM {tw_tables} WHERE dbconnection <> 'default'";
  $use_connection = db_result(db_query($sql));

  $sql = "SELECT twr.twrid, twtleft.tablename AS lefttable, twcleft.colname AS leftcol,
                 twtright.tablename AS righttable, twcright.colname AS rightcol,
                 twtleft.dbconnection AS leftconn, twtright.dbconnection AS rightconn,
                 twr.automatic
          FROM {tw_relationships} twr
          INNER JOIN {tw_columns} twcleft ON twr.leftcol=twcleft.twcid
          INNER JOIN {tw_tables} twtleft ON twcleft.twtid=twtleft.twtid
          INNER JOIN {tw_columns} twcright ON twr.rightcol=twcright.twcid
          INNER JOIN {tw_tables} twtright ON twcright.twtid=twtright.twtid";
  $sql .= tablesort_sql($form['header']['#value']);
  $result = db_query($sql);
  $checks = array();
  while ($row = db_fetch_object($result)) {
    $leftcol = $row->lefttable . '.' . $row->leftcol;
    $rightcol = $row->righttable . '.' . $row->rightcol;
    $checks[$row->twrid] = '';
    $form['twrid'][$row->twrid] = array('#value' => $row->twrid);
    if ($use_connection) {
      $leftcol = $row->leftconn . '.' . $leftcol;
    }
    $form['leftcol'][$row->twrid] = array('#value' => $leftcol);
    if ($use_connection) {
      $rightcol = $row->rightconn . '.' . $rightcol;
    }
    $form['rightcol'][$row->twrid] = array('#value' => $rightcol);
    $form['automatic'][$row->twrid] = array('#value' =>
      $row->automatic ? t('Automatic') : t('Manual'));
  }

  $form['checks'] = array('#type' => 'checkboxes', '#options' => $checks);
  $form['#theme'] = 'tw_relationships';
  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete selected relationships'),
  );
  $form['autochange'] = array(
    '#type' => 'submit',
    '#value' => t('Change type of selected relationships'),
  );

  $form['addrel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add a relationship'),
    '#collapsible' => TRUE,
  );
  $sql = "SELECT twc.twcid, twc.colname, twt.tablename, twt.dbconnection
          FROM {tw_columns} twc
          INNER JOIN {tw_tables} twt ON twc.twtid=twt.twtid
          WHERE twc.availablefk=1
          ORDER BY dbconnection, tablename, colname";
  $result = db_query($sql);
  $options = array();
  while ($row = db_fetch_array($result)) {
    if ($use_connection) {
      $options[$row['twcid']] = $row['dbconnection'] . '.' . $row['tablename'] .'.'. $row['colname'];
    }
    else {
      $options[$row['twcid']] = $row['tablename'] . '.' . $row['colname'];
    }
  }

  if (count($options) > 0) {
    $form['addrel']['newleftcol'] = array(
      '#type' => 'select',
      '#title' => t('Field from the base table of the relationship'),
      '#options' => $options,
    );
    $form['addrel']['newrightcol'] = array(
      '#type' => 'select',
      '#title' => t('Corresponding field from a table to be joined to the base table'),
      '#options' => $options,
    );
    $form['addrel']['automatic'] = array(
      '#type' => 'select',
      '#title' => t('Incorporate related table into views automatically'),
      '#description' => t('If you choose <strong>Automatic</strong>, then views
        of the base table will automatically include fields from the related table.
        If you choose <strong>Manual</strong>, then to bring fields from the related
        table into the view, you must explicitly add the relationship to the view.'),
      '#options' => array(1 => t('Automatic'), 0 => t('Manual')),
      '#default_value' => 1,
    );
    $form['addrel']['add'] = array(
      '#type' => 'submit',
      '#value' => t('Add'),
    );
  }
  else {
    $form['addrel']['message'] = array(
      '#prefix' => '<div>',
      '#value' => t('To define relationships between tables, you first
      need to add tables to the Table Wizard, and define Available Keys via the
      analysis pages for the tables.'),
      '#suffix' => '</div>',
    );
  }
  return $form;
}

/**
 * Theme relationships form.
 */
function theme_tw_relationships($form) {
  $output = drupal_render($form['description']);

  if (isset($form['twrid']) && is_array($form['twrid'])) {
    foreach (element_children($form['twrid']) as $twrid) {
      $row = array();
      // Don't show the row ID
      $null = drupal_render($form['twrid']);
      $row[] = drupal_render($form['checks'][$twrid]);
      $row[] = drupal_render($form['leftcol'][$twrid]);
      $row[] = drupal_render($form['rightcol'][$twrid]);
      $row[] = drupal_render($form['automatic'][$twrid]);
      $rows[] = $row;
    }
  }
  $header = $form['header']['#value'];
  if (!isset($rows)) {
    $rows[] = array(array('data' => t('No relationships have been defined.'),
                          'colspan' => count($header)));
  }
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($form['delete']);
  $output .= drupal_render($form['autochange']);
  $output .= drupal_render($form['addrel']);
  $output .= drupal_render($form);

  return $output;
}

/**
 * Submit handler for tw_relationships_form().
 */
function tw_relationships_form_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#parents'][0] == 'delete') {
    $count = 0;
    foreach ($form_state['values']['checks'] as $twrid => $value) {
      if ($value) {
        tw_delete_relationship($twrid);
        $count++;
      }
    }
    if ($count) {
      drupal_set_message(format_plural($count, '1 relationship deleted', '@count relationships deleted'));
    }
  }
  else if ($form_state['clicked_button']['#parents'][0] == 'autochange') {
    $count = 0;
    foreach ($form_state['values']['checks'] as $twrid => $value) {
      if ($value) {
        // Flip the value 0 <--> 1
        $sql = "UPDATE {tw_relationships}
                SET automatic = ABS(automatic-1)
                WHERE twrid=%d";
        db_query($sql, $twrid);
        $count++;
      }
    }
    if ($count) {
      drupal_set_message(format_plural($count, '1 relationship changed', '@count relationships changed'));
    }
  }
  else {
    $leftcol = $form_state['values']['newleftcol'];
    $rightcol = $form_state['values']['newrightcol'];
    $automatic = $form_state['values']['automatic'];
    tw_add_relationship($leftcol, $rightcol, $automatic);
  }
  return;
}

function tw_export($twtids = array()) {
  require_once drupal_get_path('module', 'tw') . '/tw_tablebuild.inc';
  if (empty($twtids)) {
    return drupal_access_denied();
  }
  $twtids = explode(',', check_plain($twtids));
  foreach ($twtids as $twtid) {
    if (!is_numeric($twtid)) {
      // Crude but effecive security measure
      return drupal_not_found();
    }
  }
  return drupal_get_form('tw_export_form', $twtids);
}

function tw_export_form(&$form_state, $twtids) {
  $tables = _tw_generate_views_table_data($twtids, TRUE);
  $tables = _tw_generate_views_relationship_data($tables, $twtids, TRUE);
  $code = tw_data_export($tables);
  $lines = substr_count($code, "\n");
  $form['code'] = array(
    '#type' => 'textarea',
    '#title' => t('Table Wizard generated code for hook_views_data() implementation'),
    '#default_value' => $code,
    '#rows' => $lines + 1,
  );
  return $form;
}

function tw_data_export($tables) {
  $output = '  $data = array();' . "\n";
  foreach ($tables as $table => $data) {
    $output .= '  $data[\'' . $table . '\'] = ';
    $output .= _tw_data_export($data, '  ');
    $output .= ";\n";
  }
  $output .= '  return $data;';
  return $output;
}

function _tw_data_export($var, $prefix = '') {
  if (is_array($var)) {
    if (empty($var)) {
      $output = 'array()';
    }
    else {
      $output = "array(\n";
      foreach ($var as $key => $value) {
        $output .= "  '$key' => " . _tw_data_export($value, '  ') . ",\n";
      }
      $output .= ')';
    }
  }
  else if (is_bool($var)) {
    $output = $var ? 'TRUE' : 'FALSE';
  }
  // Special case for the t() function.
  else if (substr($var, 0, 2) == 't(') {
    $output = $var;
  }
  else {
    $output = var_export($var, TRUE);
  }

  if ($prefix) {
    $output = str_replace("\n", "\n$prefix", $output);
  }

  return $output;
}

/**
 * Wraps strings that would normally be immediately translated via t() with the
 * t() call as a string, in a format appropriate for export.
 *
 * @param string $string
 * @param array $args
 * @return string
 */
function _tw_t_wrap($string, $args = array()) {
  if (empty($args)) {
    return "t('$string')";
  }
  else {
    // Transform arguments before inserting them.
    foreach ($args as $key => $value) {
      switch ($key[0]) {
        case '@':
          // Escaped only.
          $args[$key] = check_plain($value);
          break;

        case '%':
        default:
          // Escaped and placeholder.
          $args[$key] = theme('placeholder', $value);
          break;

        case '!':
          // Pass-through.
      }
    }
    return "t('". strtr($string, $args) ."')";
  }
}
