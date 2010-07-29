<?php
// $Id: views-cloud-style.tpl.php,v 1.4 2009/11/18 02:08:20 quicksketch Exp $
/**
 * @file views-cloud-style.tpl.php
 * Outputs a view as a weighted cloud.
 *
 * - $view: The view in use.
 * - $font_size: The amount to adjust the font size as a decimal.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<div class="views-cloud"<?php print $font_size ? ' style="font-size: ' . $font_size . 'em"' : '' ?>>
  <?php foreach ($rows as $row): ?>
    <span class="views-cloud-size-<?php print $row->cloud_size; ?>"><?php print $row->output; ?></span>
  <?php endforeach; ?>
</div>
