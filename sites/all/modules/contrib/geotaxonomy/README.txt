$Id: README.txt,v 1.3.2.2 2009/10/13 21:45:58 alexb Exp $

GEO-TAXONOMY

Attaches geo information (latitude, longitude, bounding boxes, etc.) to
taxonomy terms. Provides views integration.

FEATURES

- Attach geo information to taxonomy terms
- UI for editing geo information on taxonomy terms
- Import terms with Feeds
  http://drupal.org/project/feeds
- Show geotagged content on OpenLayers maps (use OpenLayers 6.x 0.x).

USAGE

1. Install module
2. Create vocabulary, check "Store geo data for this vocabulary"
3. Add term to vocabulary, configure latitude, longitude, etc.

IMPORT GEO TERMS WITH FEEDS MODULE

1. Install geotaxonomy and feeds.
2. Go to admin/buid/feeds and create a new importer configuration.
3. Edit the configuration, pick "Taxonomy term processor" as processor.
4. Edit the settings of "Taxonomy term processor" and select the vocabulary that
   is Geo data enabled (see USAGE 2.).
5. Edit the mapping of the Taxonomy term processor and map which sources should
   map to which geo fields. The available sources are going to depend on the
   parser that is selected.