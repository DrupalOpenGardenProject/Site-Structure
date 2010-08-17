<?php
// $Id$
/* *
 * @file
 * page.tpl.php
 */

/**
 * documentation:
 * http://api.drupal.org/api/file/modules/system/page.tpl.php
 * -------------------------------------
 * page vars dsm(get_defined_vars())
 * -------------------------------------
 * <?php print $base_path; ?>
 * <?php print $is_front ?>
 */
?>
<?php // dsm(get_defined_vars()) ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
<!--
  mothership FTW
  http://drupal.org/projects/moshpit
-->
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; //can be modified in template.php mothership_preprocess_page or though the theme settings + http://drupal.org./node/171906 ?>">

<?php if (!empty($admin)) print $admin; ?>
<div class="header">
  <<?php print $site_name_element; // defined in template.php  mothership_preprocess_page ?> id="site-name">
    <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
  </<?php print $site_name_element; ?>>

  <?php print $site_slogan ?>
  <?php print $mission ?>

  <?php if ($header) { ?>
    <?php print $header; ?>
  <?php } ?>

  <?php if ($primary_links) { ?>
    <?php print theme('links', $primary_links); ?>
  <?php } ?>

  <?php if ($breadcrumb) { ?>
    <?php print $breadcrumb; // themename_breadcrumb in template.php?>
  <?php } ?>

</div>
<div class="body clearfix">
  <div class="left">
    <?php if ($left) { ?>
      <?php print $left; ?>
    <?php } ?>

  </div>
  <div class="main">
      <?php if ($help OR $messages) { ?>
          <?php print $help ?>
          <?php print $messages ?>
      <?php } ?>

      <?php if ($tabs) { ?>
        <?php print $tabs; ?>
      <?php }; ?>

      <?php if ($title AND (arg(0) != "node")) {  ?><h1><?php print $title; ?></h1><?php } ?>

      <?php print $content; ?>

  </div>
  <div class="right">
    <?php if ($right) { ?>
      <?php print $right; ?>
    <?php } ?>

  <?php print mothership_userprofile($user); ?>

  </div>
</div>

<div class="footer">

  <?php if ($footer_message) { ?>
    <?php print $footer_message; ?>
  <?php } ?>

  <?php print $footer; ?>

  <?php print $feed_icons ?>
</div>

<?php print $closure; ?>

</body>
</html>