Check out Drupal 6 git mirror and put in this folder.


1. git clone frome here:

git clone http://github.com/drupal/drupal.git  

* this will create a new 'drupal' folder

2. Check out the current version of Drupal 6

git checkout DRUPAL-6-17

* checkout the most current version of Drupal 6

3. set up .gitignore

sites/default/settings.php
sites/default/files
.gitignore

4. Remove the 'sites' folder.

5. Make a symbolic link from the github sites folder to where sites should go

from the top level of the github directory

format
ln -s (make a symbolic link)  files_location_relative_to_target  location_alias_should_show_up

ln -s ../../sites d6/drupal/sites




GitHub Repository for Drupal.
http://github.com/drupal/drupal/tree/DRUPAL-6