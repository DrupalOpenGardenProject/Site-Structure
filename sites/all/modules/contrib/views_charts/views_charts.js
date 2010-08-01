// $Id: views_charts.js,v 1.1.2.2 2010/07/08 13:50:32 rsevero Exp $

Drupal.behaviors.views_charts_form = function(context) {
  
  $('#edit-style-options-engine', context).change(function() {
    
    var engine    = this.value,
        className = 'views_charts_' + engine + '_chart_types',
        hidden    = 'views_charts_chart_types_hidden';
    
    $('div.views_charts_chart_types', context).each(function() {
      
      $this = $(this);
      
      if ($this.hasClass(className)) {
        $this.removeClass(hidden);
      } else {
        $this.addClass(hidden);
      }
      
    });
    
  });
  
};
