// $Id: extractor.js,v 1.1 2010/03/01 16:31:36 rsoden Exp $

/**
 * Conditional show behavior for Feeds importer form.
 * @todo: simplify.
 */
Drupal.behaviors.extractor = function() {
  if ($('#edit-extractors-placemaker').attr('checked')) {
    $('#edit-placemaker-key-wrapper').show();
    $('#edit-language-wrapper').show();
  }
  else {
    $('#edit-placemaker-key-wrapper').hide();
    $('#edit-language-wrapper').hide();
  }
  $('#edit-extractors-extractor-simple').click(function() {
    $('#edit-placemaker-key-wrapper').hide(100);
    $('#edit-language-wrapper').hide(100);
  });
  $('#edit-extractors-placemaker').click(function() {
    $('#edit-placemaker-key-wrapper').show(100);
    $('#edit-language-wrapper').show(100);
  });
}