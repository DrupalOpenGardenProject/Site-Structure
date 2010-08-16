// $Id: README.TXT,v 1.1.2.2 2010/03/12 14:46:55 publicmind Exp $

Feeds Image Grabber (FIG), an addon module for Feeds module, grabs (downloads) image for each feed-item from their respective webpages and maps to an image field in the node created by Feeds (Node Processor).

Visit:
Project page: http://drupal.org/project/feeds_imagegrabber
Release page: http://publicmind.in/blog/drupal-feeds-image-grabber
Tutorial: http://publicmind.in/blog/tutorial-for-feeds-image-grabber


Dependencies:
-------------
Feeds
ImageField

Installation
------------

1) Place this module directory in your modules folder (this will usually be "sites/all/modules/").
2) Download the UrlToAbsolute package (http://sourceforge.net/projects/absoluteurl) and copy the "url_to_absolute.php" file to the feeds_imagegrabber directory.
3) Enable the module.

Usage
------

Whenever you create a new feeds content type, you will see extra options for Feeds Image Grabber:

1) Enable Feeds Image Grabber: Check this box, if you want to enable FIG for the feed in concern.
2) and 3) Id/Class: select the identifying tag and enter its id/class (see tutorial[http://publicmind.in/blog/tutorial-for-feedapi-imagegrabber] for details.)
4) Feeling Lucky
5) Execution time: Percentage of Maximum PHP execution time to take while grabbing image for each feed-item.

After these settings, go to mappings setting for FeedsNodeProcessor and map Item URL(Link) to the image field of your choice. ImageFields will be appended with "(FIG)" which are processed by Feeds Image Grabber.

Maximum size, Minimum resolution, Maximum resolution settings for FIG can be set for each imagefield on their "Manage Fields" page. FIG considers the settings of individual fields while grabbing images for each feed-item.

For detailed explanation: http://publicmind.in/blog/tutorial-for-feeds-image-grabber/

Author
------

publicmind wrote and maintains this module. The author can be contacted for paid customizations of this module as well as
Drupal consulting and development at http://drupal.org/user/472412
