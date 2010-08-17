var fontyourfaceSampleText = '';

Drupal.behaviors.fontyourfaceAddForm = function(context) {

  fontyourfaceSampleText = $('#edit-sample-text').val();

  $('#edit-sample-text').keyup(
    function() {

      var markup = $('.fontyourface-view').html();
      var updatedText = $('#edit-sample-text').val();

      if (updatedText != fontyourfaceSampleText) {

        markup = markup.replace(new RegExp(fontyourfaceSampleText, 'g'), updatedText);  
        $('.fontyourface-view').html(markup);
        fontyourfaceSampleText = updatedText;

      } // if

    } // function
  );

} // Drupal.behavior.fontyourfaceAddForm
