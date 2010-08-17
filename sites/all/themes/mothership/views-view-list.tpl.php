<?php
// $Id$
/**
 * @file
 * views-view-list.tpl.php
 */
?>
<!-- views-view-list.tpl.php -->
<?php if (!empty($title)) { ?>
  <h3><?php print $title; ?></h3>
<?php } ?>

  <<?php print $options['type']; ?>>
  <?php foreach ($rows as $id => $row) {
    print '  <li';
    if ($classes[$id]) {
      print ' class="' . $classes[$id] .'"';
    }
    print '>';
    print $row;
    print '  </li>';
    print "\n";
  }
?>
</<?php print $options['type']; ?>>
<!-- /views-view-list.tpl.php -->