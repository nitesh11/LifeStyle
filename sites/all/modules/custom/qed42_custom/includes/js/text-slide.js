(function ($) {
  Drupal.behaviors.slide = {
    attach: function(context, settings) {
      $('#user-testimonials ul').innerfade({
        animationtype: 'fade',
        speed: 'slow',
        timeout: 2000,
        type: 'random',
      });
    }
  }
})(jQuery);
