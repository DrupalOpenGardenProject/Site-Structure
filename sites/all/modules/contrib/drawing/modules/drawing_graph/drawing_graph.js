if(Drupal.jsEnabled) {
  $(document).ready(GraphAutoAttach);
}

function GraphAutoAttach() {
  var style = $('svg:circle').attr('style');
  /*var style = $('graph_point').attr('style');*/

  $('svg:circle').hover(function (event) {
  /*$('graph_point').hover(function (event) {*/
    $(this).attr("style", "fill: red"); 
    var point_id = $(this).attr('id');
    var label_id = point_id.replace(/point/, "label");
    var labelbg_id = point_id.replace(/point/, "labelbg");
    $('#' + label_id).show();
    $('#' + labelbg_id).show();
    }, 
    function() { 
    $(this).attr('style', style);
      var point_id = $(this).attr('id');
      var label_id = point_id.replace(/point/, "label");
      var labelbg_id = point_id.replace(/point/, "labelbg");
      $('#' + label_id).hide();
      $('#' + labelbg_id).hide();
    });
}
