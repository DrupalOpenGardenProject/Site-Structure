$Id: README.txt,v 1.1.4.4 2009/05/09 05:54:53 danielb Exp $

Drawing API README

CONTENTS OF THIS FILE
----------------------

  * Introduction
  * Installation
  * Drawing demo usage
  * SVG browser support
  * SVG javascript support


INTRODUCTION
------------

This module provides a layer to render drawings using a Forms API like syntax
(using drupal_render itself). In addition there is a graphing extension. 
The Drawing API uses plugin modules such as Drawing SVG and Drawing GD to 
provide the method by which to render the images.
Detailed documentation on the drawing module: http://drupal.org/node/161562

Module creator: snufkin (http://drupal.org/user/58645)
6.x maintainer: Daniel Braksator (http://drupal.org/user/134005)

Project page: http://drupal.org/project/drawing.


INSTALLATION
------------
1. Copy drawing folder to modules directory (usually sites/all/modules).
2. At admin/build/modules enable the Drawing API module, as well as at least
   one toolkit module packaged with Drawing such as SVG or GD, and you may also
   choose to enable the Drawing graph module for plotting charts. 
3. Configure the module at admin/settings/drawing.


DRAWING DEMO USAGE
------------------
Enable the Drawing demo module and browse to the path 'drawing_demo' which
should also be available in the main navigation menu as 'Drawing demo'.
You are encouraged to browse and modify the drawing_demo.module source code
to help in understanding this module.  Familiarity with the Forms API will
also go a long way to understanding how to use this module.


SVG BROWSER SUPPORT
-------------------
This is table about the browser support towards inline (SVG in HTML) or embed
(SVG file as <object>, <embed>) type SVG. Additions are welcome, please use
the projects issue queue for that: http://drupal.org/project/issues/drawing. 
Thank you.

		    inline   embed
ie6                 plugin   plugin
ie7                   -        -
ff1.x                 x        x
ff2                   x        x
opera9                x        x
konqueror3            -        x
konqueror4            x        x
safari2 (rosetta)   plugin  plugin
safari2 (native)      -        -
safari3 (native)      x        x


SVG JAVASCRIPT SUPPORT
----------------------
There is no official jQuery support for SVG. With the namespaces the previously
working $('ellipse') syntax is not working anymore. There is id and class
support in the module, therefore the elements can be manipulated via regular
JavaScript.