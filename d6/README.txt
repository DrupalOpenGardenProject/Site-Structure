Check out Drupal 6 git mirror and put in this folder.

For reference
GitHub Repository for Drupal, located at
http://github.com/drupal/drupal/tree/DRUPAL-6


1. Obtain entire git repository of Drupal 

git clone http://github.com/drupal/drupal.git  

* This will create a new 'drupal' folder

* When you download this git repository, it contains the ENTIRE history 
of Drupal releases, going back years. Think Drupal 4!



2. Check out the current version of Drupal 6

cd drupal

git checkout DRUPAL-6-17



* This will checkout the most current version of Drupal 6 (Drupal 6.17) based on a tag.

* This replaces all your files in the /drupal directory with the proper version of Drupal.

* DRUPAL-6-17 is a 'tag'

* To see which versions of Drupal are in the repository, do
git tag

* A tag is a point in the history of the code which was declared by the community to be
an official release of Drupal.


What is happening here:

* When you first clone the repository, you will be on a branch called 'CVS' 
(as opposed to 'master' which is normal for git repositories.)

* The repository comes with no actual branches except 'CVS'

* To see the list of branches
git branch

* CVS
is what it should look like by default.


* When you check out the 'tag' it is not on a branch, and you should see 
'Note: moving to 'DRUPAL-6-17' which isn't a local branch'

This is OK. We are about to make a working branch.

3. Make a brand new branch to store all your own customizations (such as
 deleting the sites folder):

git checkout -b master

* This will create a new working branch based on the current state of your files. 

* You shouldn't have to do much customization to Drupal core for this project,
but you can version the fact that you may replace your 'sites' folder with a
symbolic link to our shared 'sites' folder.

* If you were actually working on modifying/contributing to Drupal core, you might create 
branches as you work.


4. set up .gitignore

Create a new file called .gitignore

touch .gitignore

Edit that file, include the following:

sites/default/settings.php
sites/default/files
.gitignore

5. Remove the 'sites' folder.
We are going to replace it with an alias, or symbolic link, to a sites folder that is versioned elsewhere.

6. Make a symbolic link from the github sites folder to where sites should go

from the top level of the github directory 
(what you cloned from here: http://github.com/DrupalOpenGardenProject/Site-Structure)


How Symbolic Link Command works:
ln -s (make a symbolic link)  files_location_relative_to_target  location_alias_should_show_up


What you will input:
ln -s ../../sites d6/drupal/sites

7. Make your first commit

git add .

git commit -m "Created a master branch from DRUPAL-6-17. Sites folder replaced with symbolic link to sites from a different git repository."




