<?php
// $Id: iframe.tpl.php,v 1.1.2.1 2009/08/02 02:30:06 jtsnow Exp $
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <title><?php print $head_title ?></title>
    <?php print $head ?>
    <?php print $styles ?>
    <?php print $scripts ?>
    <style type="text/css">
      .widget-container {
        height: <?php print $height - 12 ?>px;
      }
    </style>
  </head>
  <body class="<?php print $body_classes; ?>">

<!-- Layout -->


    <div id="container" class="clear-block widget-container">
          <?php //print $breadcrumb; ?>
          <?php if ($tabs): print '<div id="widget-tabs-wrapper" class="clear-block">'; endif; ?>
          <?php if ($title): print '<h3 id="widget-title"'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h3>'; endif; ?>
          <?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul></div>'; endif; ?>
          <?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
          <?php if ($show_messages && $messages): print $messages; endif; ?>
          <?php print $help; ?>
          <div class="clear-block">
            <?php print $content ?>
          </div>
          
          <?php print $feed_icons ?>
    </div> <!-- /container -->
    <div id="share-container">
      <?php print $share_widget ?>
    </div>

<!-- /layout -->

  <?php print $closure ?>
  </body>
</html>
