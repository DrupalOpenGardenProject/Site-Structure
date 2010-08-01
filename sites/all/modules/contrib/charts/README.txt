// $Id: README.txt,v 1.1 2008/07/07 10:59:51 brmassa Exp $


Charts
======

Charts module provides a unified data scheme to build any kind of charts of any
chart provider.

Each chart solution found on internet, like Google Charts and Open Flash Chart,
have a specific data scheme. Its very hard and even impossible to build a unique
chart data that would be used in more that one chart provider. Or users get
binded to a solution forever or they have to rewrite all exported data again.

Thats why Charts is so great. It uses a standard data scheme do describe charts
data and thru filters, it converts automatically to each solution. You might
change to another solution at anytime.

The Chart schema is very similiar to Drupal's Form API schema.



Chart Providers
===============

Out of the Box, you will be able to use 3 chart solutions. Which one of them
has particular advantages and disadvantages.

* Google Charts: Google solution is very peculiar since it's charts are static
images generated in their servers. Its the most simple one but it will work without
any further configuration. Note: Google limits the number of generated charts
per day. The number is very big, but it might not be a good solution for heavy
sites.

* Open Flash Chart: This open source project have a single Flash file tha generates
several types of charts. These charts also have some special effects. Note:
the flash file is not included with this module. It should be downloaded separatedly.

* FusionCharts: FusionCharts also uses Flash and it has the most complete set
of chart types and effects. The FusionCharts filter works with both free and
complete versions. Note: the flash file is not included with this module. It should
be downloaded separatedly.



HELP!
=====

If you need some assistance, doubt or problem, go to the module's page on Drupal
site: http://drupal.org/modules/charts. There you can find a link to the
documentation, some tutorials to help you integrate your module and the issues
system to post bugs and ask for more features.
