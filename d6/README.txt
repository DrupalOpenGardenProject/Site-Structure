Check out Drupal 6 git mirror and put in this folder.

For reference
GitHub Repository for Drupal, located at
http://github.com/drupal/drupal/tree/DRUPAL-6


###Get Drupal Source Files

A. The easy way
Download Drupal 6 from drupal.org.
Unzip & place the folder in this d6 folder.
Make sure the drupal files sit in a folder called 'drupal'

B. Using the Drupal git mirror  (fancy/interesting/slow method)

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


___________
Now configure your Drupal site to use the correct 'sites' folder.

We are using a version of Drupal that already has a bunch of modules selected, and we
have a database that has modules enabled & many configurations. You need to
set up the 'sites' folder on your machine so that the database that you use
will find all the files it needs.


A. set up .gitignore
We want to make sure that we do not commit our settings, passwords, or other 
custom files to the repository everyone else is sharing. To do this, 
we create a .gitignore file. Anything in that file will not be tracked 
by Git, and therefore will not get committed.



1. Create a new file called .gitignore

touch .gitignore

Edit that file, include the following:

sites/default/settings.php
sites/default/files
.gitignore





B. Remove the 'sites' folder.
The core version of Drupal comes with a 'sites' folder. We don't want it, we have our own
special version that Chach already set up. You don't want to physically move that file because
it is already versioned. Also, when you upgrade Drupal, you would have to worry about overwriting
the sites folder...so this aliasing method is really much easier to deal with.


That sites folder is in this repository, in its own special location. 
Site-Strucutre/sites

We are going to replace the Site-Strucutre/d6/drupal/sites folder with an alias, or symbolic link.
The alias is going to point to Site-Strucutre/sites folder.

1. In the command line, make sure you are at the top level of the github directory 
(what you cloned from here: http://github.com/DrupalOpenGardenProject/Site-Structure)
if you list (ls) your files, you should see d6, mn, sites etc.

How Symbolic Link Command works:
ln -s (make a symbolic link)  files_location_relative_to_target  location_alias_should_show_up

What you will input:
ln -s ../../sites d6/drupal/sites


Check that it works:
This will work on a Mac: 
In your Finder, an alias will appear like a little icon that has a little arrow on it.
When you click the alias, it should take you to a folder that has the contents of the sites directory.
You might be able to use the Finder interface to make an alias...but it's handy to try to do it with the 
command line and learn how to use symbolic links.


7. Make your first commit for your Drupal repository.
It is possible to have your Drupal install & settings be versioned. For this project it isn't totally necessary.

This only applies if you have used Git to download Drupal. Mainly it is a suggestion so that you can use Git to upgrade
versions of Drupal by doing git pull & switching branches. (Instead of downloading & replacing files when you upgrade.)

You have just customized your repository. This means you now have untracked changes.
Your whole Site-Strucutre/d6/drupal should already be ignored by git because Chach told it to specifically not track the 'drupal' folder.

git add .

git commit -m "Created a master branch from DRUPAL-6-17. Sites folder replaced with symbolic link to sites from a different git repository."



###Next steps
You should now have the necessary codebase for your Drupal site.
You will also need to

* create a local database
* get the database dump (from the email that had your password,
 or login to the site & go to /admin/content/backup_migrate to download a recent version of the database)
* set up your settings.php file to point to your database
Two methods:
1. Edit the settings.php to use your proper credentials, then visit the homepage of your drupal site.
2. Copy default.settings.php to settings.php; visit your Drupal site in the web browser and follow instructions to install the Drupal site.
You will need to give it configuration for your mysql server. Full instructions on drupal.org.

Where is your Drupal site?
You would go in your web browser to the directory that contains your drupal files.
If you cloned Site-Structure into the root of your web folder (i.e. put it in 'htdocs')

http://localhost/Site-Structure/d6/drupal
http://localhost:8888/Site-Structure/d6/drupal  (default MAMP install address on some systems)



_____________


SPECIAL THANKS
to Karoline Daneheart, James Stone & Kristin Antin for being the first to set up this system using Git & their vital feedback. 
(^_^)

