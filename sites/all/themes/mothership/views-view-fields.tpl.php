<?php
// $Id$
/**
 * @file
 * views-view-grid.tpl.php
 */
?>
<!-- views-view-fields.tpl.php -->
<?php
foreach ($fields as $id => $field) {
  if (!empty($field->separator)) {
    print "\n";
    print "      " . $field->separator;
    print "\n";
  }

  //start tag
  print '      <' . $field->inline_html . ' class="'. $field->class . '">';
  //label
  if ($field->label) {
    print "\n";
    print "        <label>" . $field->label . "</label>";
  }
  //content
  if ($field->label) {
    print "\n";
    print "        <" . $field->element_type . ">" . $field->content . "</" . $field->element_type . ">";
  }
  else{
    print "\n";
    print "\t" . $field->content;
  }

  //end tag
  print "\n";
  print "      </" . $field->inline_html .">";
  print "\n";
}

?>
<!--/ views-view-fields.tpl.php -->
