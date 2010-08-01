<?php
// $Id: widget.tpl.php,v 1.3.2.1 2009/07/24 02:18:35 jtsnow Exp $
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


    <div id="container" class="clear-block widget-container">

      <div id="center"><div id="squeeze"><div class="right-corner"><div class="left-corner">
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
          <div id="footer"><?php //print $footer_message . $footer ?></div>
      </div></div></div></div> <!-- /.left-corner, /.right-corner, /#squeeze, /#center -->

    </div> <!-- /container -->

<!-- /layout -->

  <?php print $closure ?>
  </body>
</html>
