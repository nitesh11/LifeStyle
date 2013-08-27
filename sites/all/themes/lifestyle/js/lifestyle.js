jQuery(document).ready(function() {	
	jQuery('.pane-panels-ajax-tab-tabs .item-list li.last a').click(function() {
	alert('hello');
		jQuery('.pane-brand-view-for-background-image li.jcarousel-item .views-field-field-image1').hover(function(){
		alert('hello');
	});

	$.ajax({
  url: "/panels_ajax_tab/exclusive_product_image",
  context: document.body
}).done(function() {
	alert('hey');
});
});

});	
 
