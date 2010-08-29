<?php
// $Id: page-node-lightbox2.tpl.php,v 1.1.2.2 2008/06/11 22:16:38 snpower Exp $

/**
 * @file
 * Template file for displaying the node content, associated with an image, in
 * the lightbox.  It displays it without any sidebars, etc.
 */
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <title><?php print $head_title ?></title>
    <?php print $head ?>
    <?php print $styles ?>
    <?php print $scripts ?>
    <!--[if lt IE 7]>
      <?php print phptemplate_get_ie_styles(); ?>
    <![endif]-->
  </head>
  <body>

<!-- Layout -->

    <div id="wrapper">
    <div id="container" class="clear-block">

</div> <!-- close container -->
</div> <!-- close wrapper -->
</body>
</html>
