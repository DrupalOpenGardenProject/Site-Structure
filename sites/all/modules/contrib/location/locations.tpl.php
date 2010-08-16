<?php if (count($locations)) {?>
<h3 class="location-locations-header"><?php echo count($locations) > 1 ? t('Locations') : t('Location');?></h3>
<div class="location-locations-wrapper">
<?php
  foreach ($locations as $location) {
    echo $location;
  }
  echo '</div>';
} ?>
