<?php
// $Id: views-cloud-summary-style.tpl.php,v 1.4 2009/11/18 02:08:20 quicksketch Exp $
/**
 * @file views-cloud-summary-style.tpl.php
 * View template to display a list summaries as a weighted cloud
 *
 * - $font_size: The amount to adjust the font size as a decimal.
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 *
 * @ingroup views_templates
 */
?>
<div class="views-cloud"<?php print $font_size ? ' style="font-size: ' . $font_size . 'em"' : '' ?>>
  <?php foreach ($rows as $row): ?>
    <span class="views-cloud-size-<?php print $row->cloud_size; ?>">
      <a href="<?php print $row->url; ?>"><?php print $row->link; ?></a>
      <?php if (!empty($options['count'])): ?>
        <span class="views-cloud-count">(<?php print $row->count?>)</span>
      <?php endif; ?>
    </span>
  <?php endforeach; ?>
</div>
