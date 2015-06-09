jQuery(document).ready(function($) {
    var $paid = $('.wdpa-id').text();
    var $paname = $('.field-name-field-protected-area-name > div.field-items > div').text();
    var url = 'http://dopa-services.jrc.ec.europa.eu/services/ibex/ehabitat/get_wdpa_lc_stats_glc2000?wdpaid=' + $paid;
    $.ajax({
        url: url,
        dataType: 'json',
        success: function(d) {
            if (d.metadata.recordCount == 0) {
				jQuery('#glc2000-chart.rest-good').switchClass( "rest-good", "rest-bad", 100 );
                jQuery('#glc2000-chart').append('There is no GLC2000 data for '+ $paname)
            } else {
                var obj = {};
                var colors_array = [];
                var obj_array = [];
                $(d.records).each(function(i, data) {
                    var lclass = data.lclass;
                    obj[lclass] = data;

                    for (var p in obj[lclass]) {
                        //adapt object labels to highcharts requirements (name and y)
                        if (p == 'label') {
                            obj[lclass]['name'] = obj[lclass][p];
                            delete obj[lclass][p];
                        }

                        if (p == 'percent') {
                            obj[lclass]['y'] = obj[lclass][p];
                            delete obj[lclass][p];
                        }

                        colors_array.push(obj[lclass].color);

                    }
                    obj_array.push(obj[lclass])

                });

                $('#glc2000-chart').highcharts({
                    chart: {
                        plotBackgroundColor: null,
                        plotBorderWidth: null,
                        plotShadow: false,
                        height: 400,
                        width: 500
                    },
                    credits: {
                        enabled: false,
                        text: 'DOPA',
                        href: 'http://www.example.com'
                    },
                    title: {
                        text: 'GLC 2000 stats for ' + $paname
                    },
                    legend: {
                        floating: true,
                        width: 500,
                        itemWidth: 500,
                        maxHeight: 100,
                        backgroundColor: 'rgba(255,255,255,0.5)',
                    },
                    tooltip: {
                        formatter: function() {
                            return '<b>' + this.point.name + '<br>Area ' + this.point.area + ' sqlkm<br>Landcover code :' + this.point.lclass;
                        },
                        positioner: function() {
                            return {
                                x: 0,
                                y: 30
                            };
                        },
                        shadow: false,
                        borderWidth: 0,
                        backgroundColor: 'rgba(255,255,255,0.5)'
                    },
                    plotOptions: {
                        pie: {
                            allowPointSelect: true,
                            cursor: 'pointer',
                            dataLabels: {
                                enabled: false
                            },
                            showInLegend: true,
                            colors: colors_array
                        }
                    },
                    series: [{
                        type: 'pie',
                        name: 'Landcover STATS',
                        //the order of colors array and series data has to be the SAME
                        data: obj_array
                    }]
                });
            }
        },
        error: function() {
			jQuery('#glc2000-chart.rest-good').switchClass( "rest-good", "rest-error", 100 );
            jQuery('#glc2000-chart').append('The glc2000 services are down.')
        }
    });
});