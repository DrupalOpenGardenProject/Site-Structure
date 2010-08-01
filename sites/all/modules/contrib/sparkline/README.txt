$Id: README.txt,v 1.3 2007/12/30 20:21:22 chris Exp $

Welcome to sparkline.module.  This module is designed as a Drupal wrapper
for the PHP Sparkline library[1].  It allows other modules to generate
sparklines[2], and provides a filter for users to embed them in posts.

FEATURES
--------
* Creates cool sparkline images.
* Filters nodes to display embedded sparklines.
* More to be written.


INSTALL REQUIREMENTS
--------------------
1.  Requires the PHP Sparkline graphic library to be somewhere in the PHP
    include path - http://sparkline.org/.
2.  Requires the PHP binary to have been built with the GD library, which is
    used by the PHP Sparkline library for generating the sparklines images.

BUGS / TO DO
------------
* No known bugs -- yet.  :-)
* Lots of things to do, no doubt.

CONTRIBUTORS
------------
* Original prototype developed by Jeff Eaton (#drupal:eaton).
* Further development by Chris Johnson (#drupal:chrisxj, http://drupal.org/user/2794).
