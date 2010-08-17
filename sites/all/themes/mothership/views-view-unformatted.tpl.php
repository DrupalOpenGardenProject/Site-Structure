<?php
// $Id$
/**
 * @file
 * views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 * The $classes are defined in template_preprocess_views_view_list()
 */
?>
<!-- views-view-unformatted.tpl.php -->
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php
  foreach ($rows as $id => $row) {
    print "  <div";
    if ($classes[$id]) {
      print ' class="' . $classes[$id] . '"';
    }
    print ">";

    print $row;
    print "  </div>\n";
  }
?>
<!-- / views-view-unformatted.tpl.php -->
