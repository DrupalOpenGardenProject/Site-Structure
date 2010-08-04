<?php
// $Id: nws-weather-forecast-element.tpl.php,v 1.1 2010/01/22 21:21:03 dwaine Exp $
/**
 * @file
 * Template to display one day of nws_weather.
 * Available variables:
 *
 * @see template_preprocess_nws_weather_forecast_element()
 */
?>
<div class="nws-weather-element <?php print $class ?>">
  <?php if ($title) :?><span class="element-title"><?php print $title ?>: </span><?php endif?>
  <span class="element-value"><?php if (drupal_strlen($value) > 0) :?><?php print $value ?><?php else :?><?php print t('N/A') ?><?php endif ?></span>
  <?php if (isset($value) && $units) :?><span class="element-units"><?php print $units ?></span><?php endif?>
</div>
