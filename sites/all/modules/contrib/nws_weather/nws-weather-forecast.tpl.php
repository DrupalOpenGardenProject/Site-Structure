<?php
// $Id: nws-weather-forecast.tpl.php,v 1.1 2010/01/22 21:21:03 dwaine Exp $
/**
 * @file
 * Template to display one nws_weather output.
 * Available variables:
 * - $location_lat - Latitude of forecast location (settable on admin page)
 * - $location_lon - Longitude of forecast location (settable on admin page)
 * - $location_name - Name of the forecast location (settable on admin page)
 *
 * @see template_preprocess_nws_weather_forecast()
 */
?>
<?php if (count($forecast_units) > 0) : ?>
  <div class="nws-weather-forecast">
    <?php foreach ($forecast_units as $data) : ?>
      <?php print $data['html'] ?>
    <?php endforeach ?>
  <span class='nws-weather-clear'></span>
  </div>
<?php 
endif;