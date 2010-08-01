Drupal.behaviors.embedWidgetsBehavior = function (context) {
  $("#edit-embed-widgets-override").ready(embed_widgets_override_load);
  $("#edit-embed-widgets-override").change(embed_widgets_override_values);

}; 

embed_widgets_override_load = function () {
  var checked = $("#edit-embed-widgets-override:checked").val();

  if(checked == 1){
    $('#embed-widgets-hide-wrapper').css("display","block");
  }
  else {
    $('#embed-widgets-hide-wrapper').css("display","none");
  }
}


embed_widgets_override_values = function () {
  var checked = $("#edit-embed-widgets-override:checked").val();

  if(checked == 1){
    $('#embed-widgets-hide-wrapper').show('slow');
  }
  else {
    $('#embed-widgets-hide-wrapper').hide('slow');
  }
}
