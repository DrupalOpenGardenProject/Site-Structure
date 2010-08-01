<?php
// $Id: charts_system.inc,v 1.5 2009/05/15 03:52:44 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @author TJ (based on his Chart module)
 * @file
 * Use Charts for Drupal administration
 */

/**
 * Chart reports page
 */
function _charts_system_charts($ctype) {
  $output = '';

  switch ($ctype) {
    case 'nodes':
      $output  = _charts_system_generate(
        t('Total'),
        'SELECT COUNT(*) AS count, type AS name
        FROM {node}
        GROUP BY type
        ORDER BY type'
      );
      $output .= _charts_system_generate(
        t('Published'),
        "SELECT COUNT(*) AS count, type AS name
        FROM {node}
        WHERE status = '1'
        GROUP BY type
        ORDER BY type"
      );
      $output .= _charts_system_generate(
        t('Unpublished'),
        "SELECT COUNT(*) AS count, type AS name
        FROM {node}
        WHERE status = '0'
        GROUP BY type
        ORDER BY type"
      );
      $output .= _charts_system_node_activity();
      break;

    case 'users':
      $output  = _charts_system_generate(
        t('Users Per Role'),
        'SELECT COUNT(*) AS count, r.name AS name
        FROM {users_roles} ur
        LEFT JOIN {users} u ON ur.uid = u.uid
        LEFT JOIN {role} r ON r.rid = ur.rid
        GROUP BY r.rid, r.name
        ORDER BY r.name'
      );
      $output .= _charts_system_generate(
        t('Users Status'),
        'SELECT COUNT(*) AS count, status AS name
        FROM {users}
        WHERE uid != 0
        GROUP BY status
        ORDER BY status',
        '_charts_system_user_status_label'
      );
      break;

    case 'watchdog':
      $output  = _charts_system_generate(
        t('Watchdog Messages'),
        'SELECT COUNT(*) AS count, type AS name
        FROM {watchdog}
        GROUP BY type
        ORDER BY type'
      );
      $output .= _charts_system_generate(
        t('Message Severity'),
        'SELECT COUNT(*) AS count, severity AS name
        FROM {watchdog}
        GROUP BY severity
        ORDER BY severity',
        '_charts_system_watchdog_severity_label'
      );
      break;
  }

  return '<div id="charts-system">'. $output .'</div>';
}

/**
 * Generate some charts using a pre defined method.
 *
 * @param $title
 *   String. The chart title
 * @param $sql
 *   String. The SQL statement to be executed
 * @param $callback
 *   String (optional). When a string is given, use it as the
 *   parser of the results from SQL. Its important when the
 *   results are coded in to DB to ocupy less space, and should
 *   be decoded.
 * @return
 *   String. The HTML chart when all data is fine or a blank string
 */
function _charts_system_generate($title, $sql, $callback = NULL) {
  $results = db_query($sql);

  while ($result = db_fetch_array($results)) {
    if (!empty($callback)) {
      $result['name'] = $callback($result['name']);
    }

    $data[] = array(
      '#value'  => $result['count'],
      '#label'  => $result['name'] .': '. $result['count']
    );
  }

  if (!empty($data)) {
    $chart    = array();
    $chart[0] = $data;
    $chart['#title']    = $title;
    $chart['#type']     = 'pie2D';

    return charts_chart($chart);
  }

  return '';
}

/**
 * Show which kind of node type was created in the current month.
 *
 * @return
 *   String. The HTML chart when all data is fine or a blank string
 */
function _charts_system_node_activity() {
  $now   = time();

  $results = db_query('SELECT type, created
    FROM {node}
    WHERE created < %d AND created > %d
    ORDER BY created',
    $now, mktime(0, 0, 0, date('m', $now), 1, date('Y', $now))
  );

  $max    = array();
  $counts = array();
  $types  = array();

  while ($result = db_fetch_array($results)) {
    $day = ltrim(date('d', $result['created']), '0');
    $types[$result['type']] = $type++;
    $counts[$day][$result['type']]++;
  }

  // Generate data and labels
  if (!empty($counts)) {
    foreach ($types as $type => $index) {
      $chart[$type]['#legend'] = $type;
      for ($i = 1; $i <= date('d', $now); $i++) {
        $chart[$type][] = array(
          '#value'  => empty($counts[$i][$type]) ? 0 : $counts[$i][$type],
          '#label'  => $i
        );
      }
    }

    $chart['#title']    = t('Activity for !date', array('!date' => date('F Y', $now)));
    $chart['#type']     = 'line2D';

    return charts_chart($chart);
  }

  return '';
}

/**
 * Translate the user status label code to a string
 *
 * @param status
 *   Number. 1 for Active and 0 for Blocked
 * @return
 *   String. The given status
 */
function _charts_system_user_status_label($status) {
  return $status ? t('Active') : t('Blocked');
}

/**
 * Translate the message severity label code to a string
 *
 * @param status
 *   Number. According to watchdog constants, the severity level
 * @return
 *   String. The given severity
 */
function _charts_system_watchdog_severity_label($severity) {
  switch ($severity) {
    case WATCHDOG_NOTICE:
      return t('Notice');

    case WATCHDOG_WARNING:
      return t('Warning');

    case WATCHDOG_ERROR:
      return t('Error');
  }
}
