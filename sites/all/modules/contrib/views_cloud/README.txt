// $Id: README.txt,v 1.2 2009/11/18 02:54:47 quicksketch Exp $

Views Cloud allows you to build Web 2.0 style tag-clouds of any data retrieved
by Views. It features:

 * A summary display style for displaying clouds as summary listings.
 * A view display style for display clouds based on any arbitrary integer value.

Views Cloud was written Jeff Eaton.

This Module Made by Robots: http://www.lullabot.com

Dependencies
------------
 * views

Install
-------

1) Copy the views_cloud folder to the modules (sites/all/modules) folder in your
   installation.

2) Enable the module using Administer -> Site Building -> Modules
   (/admin/build/modules)

3) Configure a view to use Views Cloud. Note that Views Cloud comes with two
   default views that are disabled by default. They may help you get started
   with your own clouds.

   These two sample default views are:
   - cloud_tags: A common tag cloud.
   - cloud_user_posts: A cloud of user names, weighted by the user's # of posts.

Configuration for a Tag Cloud (most common)
-------------------------------------------

1) Create a new View at Administer -> Site Building -> Views
   (admin/build/views). Give it a name like "tagcloud".

2) Add a field by clicking the "+" (plus) icon under the "Fields" section.
   Note that any fields you add will NOT be part of the tag cloud, they are
   part of the listing the user will see when they click on a tag. You may
   choose to not add any fields at all but instead change the view "Row Style"
   to "Node" instead of "Fields".

3) Add an argument by clicking the "+" (plus) icon under the "Arguments"
   section. Add a "Taxonomy: Term ID" argument. For the "Action to take if
   argument is not present" option, choose "Summary, sorted ascending".
   After saving the argument, you may then choose "Cloud" as the summary
   display style.

  IMPORTANT NOTE: The view in the preview may not look very much like a "cloud"
  because the Views Cloud CSS may not be loaded on the page.

4) Add a filter by clicking the "+" (plus) icon under the "Filters" section.
   Add the "Taxonomy: Vocabulary" filter, and restrict the list to items within
   whatever vocabularies you would like the cloud to include.

5) Add a "Page" display from the left-hand side of the view configuration.
   Give it a path to where you would like the tag links to direct.

6) Add a "Block" display from the left-hand side of the view configuration.

7) Save your view.

8) Enable your new block at Administer -> Site Building -> Blocks
   (admin/build/block).

Configuration for a Cloud based on arbitrary integers
-----------------------------------------------------

(Instructions abbreviated, see the instructions above for full steps.)

1) Create a new View.

2) Add fields you would like to be in the cloud. Add a field that will be used
   as the weight for each item (such as number of comments).

3) Click the "Style" option under the "Basic settings" option and change it to
   "Cloud".

4) Create a block display and save your view.

Support
-------
If you experience a problem with Views Cloud or have a problem, file a
request or issue on the Views Cloud queue at
http://drupal.org/project/issues/views_cloud. DO NOT POST IN THE FORUMS. Posting
in the issue queues is a direct line of communication with the module authors.