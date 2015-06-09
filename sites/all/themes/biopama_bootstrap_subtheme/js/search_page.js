(function($) {
  Drupal.behaviors.bef_live_filter = {
    attach: function(context, settings) {
      // Hide the apply button.
      $('.views-exposed-form input:submit', context).hide();
    
      // When the change event fires, run the submit handler
      $('.views-exposed-form input, .views-exposed-form select', context).change(function(event) {
        $(this).parents('form').find('.views-exposed-form input:submit').click();
      });
    }
  }
})(jQuery);

if (Drupal.jsEnabled) {
  Drupal.behaviors.test = function() {
    // NOTE: the exposed filter was given a filter identifier of "slider_filter".  Views
    // adds the "edit-" and "-min/-max" parts.  
    var min = $('input#edit-slider-filter-min');
    var max = $('input#edit-slider-filter-max');
    
    if (!min.length || !max.length) {
      // No min/max elements on this page
      return;
    }
    
    // Set default values or use those passed into the form
    var init_min = ('' == min.val()) ? 0 : min.val();
    var init_max = ('' == max.val()) ? 10 : max.val();
     // Set initial values of the slider 
    min.val(init_min);
    max.val(init_max);


    // Insert the slider before the min/max input elements 
    min.parents('div.views-widget').before(
      $('<div></div>').slider({
        range: true,
        min: 0,     // Adjust slider min and max to the range 
        max: 10,    // of the exposed filter.
        values: [init_min, init_max],
        slide: function(event, ui){
          // Update the form input elements with the new values when the slider moves
          min.val(ui.values[0]);
          max.val(ui.values[1]);
        }
      })
    );      // Add .hide() before the ';' to remove the input elements altogether.
  };
}