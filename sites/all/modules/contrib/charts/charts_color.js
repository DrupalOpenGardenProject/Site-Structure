// $Id: charts_color.js,v 1.5 2009/05/15 05:22:57 brmassa Exp $
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @file
 * Set the color palette to Charts.
 */
Drupal.behaviors.chartsColor = function (context) {
  var chartsColor = function() {
    var colors = $("#edit-color-color-palette").val().split(",");
    var series = ["background", "text", 0, 1, 2, 3, 4, 5, 6, 7];
    var disabled = ($("#edit-color-color-palette").children("option:selected").text() == Drupal.settings.chartsColorCustom);
    for (var s = 0, len = series.length; s < len; ++s) {
      if (colors[s]) {
        $("#edit-color-"+ series[s]).val(colors[s]);
      }
      if (disabled) {
        $("#edit-color-"+ series[s]).removeAttr("readonly");
      }
      else {
        $("#edit-color-"+ series[s]).attr("readonly", "readonly");
      }
    }
  };

  $("#edit-color-color-palette").change(chartsColor);
  chartsColor();
};
