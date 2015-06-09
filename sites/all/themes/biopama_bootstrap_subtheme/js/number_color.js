(function ($) {

	$( document ).ready(function() {
		numbercolor();
	});

	function numbercolor() {
		var $PLtrafficlight2 =  $('span.PLtrafficlight').text();
		var $PLtrafficlight = $PLtrafficlight2.replace("%", "");
		var $TStrafficlight2 =  $('span.TStrafficlight').text();
		var $TStrafficlight = $TStrafficlight2.replace("%", "");
		var $PMtrafficlight2 =  $('span.PMtrafficlight').text();
		var $PMtrafficlight = $PMtrafficlight2.replace("%", "");
		var $MStrafficlight2 =  $('span.MStrafficlight').text();
		var $MStrafficlight = $MStrafficlight2.replace("%", "");
		//alert($PLtrafficlight);
		
		if(-30 < $TStrafficlight && $TStrafficlight < 0){
			$( "span.TStrafficlight" ).addClass( "green" );
		}
		else if(0 < $TStrafficlight && $TStrafficlight < 10){
			$( "span.TStrafficlight" ).addClass( "yellow" );
		}
		else{
			$( "span.TStrafficlight" ).addClass( "red" );
		}
		if(-2 < $MStrafficlight && $MStrafficlight < 0){
			$( "span.MStrafficlight" ).addClass( "green" );
		}
		else if(0 < $MStrafficlight && $MStrafficlight < 7){
			$( "span.MStrafficlight" ).addClass( "yellow" );
		}
		else{
			$( "span.MStrafficlight" ).addClass( "red" );
		}
	}

})(jQuery);
