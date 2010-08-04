<?php
// $Id: nws-weather-forecast-period.tpl.php,v 1.1.2.1 2010/04/08 21:44:11 dwaine Exp $
/**
 * @file
 * Template to display one time period of nws_weather output.
 * Available variables:
 * - $data - the weather data
 * - $display - the list of weather elements to display, in display order
 * - $period_start - label for starting time of forecast period
 * - $period_end - label for starting time of forecast period 
 *
 * @see template_preprocess_nws_weather_forecast_period()
 */
?>
<?php if (!empty($data)) :?>
<div class="nws-weather-period <?php print $first ? 'first' : ''?><?php print $last ? 'last' : ''?>">
<?php if ($data && $period_start) : ?>
<h4 class="period-name"><?php print $period_start ?></h4>
<?php endif ?>
<?php foreach ($display as $name) : ?>
  <?php if ($data && array_key_exists($name, $data)) : ?>
    <?php print $data[$name]['html'] ?>
    <?php endif ?>
<?php endforeach ?>
</div>
<?php
endif;