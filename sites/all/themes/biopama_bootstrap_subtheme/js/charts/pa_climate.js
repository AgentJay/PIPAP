jQuery(document).ready(function($) {
    var $paid = $('.wdpa-id').text();
    var $paname = $('.field-name-field-protected-area-name > div.field-items > div').text();
    //alert($paname);
    var url = 'http://dopa-services.jrc.ec.europa.eu/services/ibex/ehabitat/get_climate_pa?wdpaid=' + $paid;
    $.ajax({
        url: url,
        dataType: 'json',
        success: function(d) {
            if (d.metadata.recordCount == 0) {
				jQuery('#climate-chart.rest-good').switchClass( "rest-good", "rest-bad", 100 );
                jQuery('#climate-chart').append('There is no Climate data for ' + $paname)
            } else {
                var precip = [];
                var tmax = [];
                var tmin = [];
                var tmean = [];
                $(d.records).each(function(i, data) {
                    //	console.warn(i)

                    switch (data.type) {
                        case 'prec':
                            for (var prop in data) {
                                if (prop !== 'type' && prop !== 'uom') {
                                    precip.push(data[prop])
                                }
                            }

                            break;
                        case 'tmin':
                            for (var prop in data) {
                                if (prop !== 'type' && prop !== 'uom')
                                    tmin.push(data[prop])
                            }

                            break;

                        case 'tmax':
                            for (var prop in data) {
                                if (prop !== 'type' && prop !== 'uom')
                                    tmax.push(data[prop])
                            }
                            break;

                        case 'tmean':

                            for (var prop in data) {
                                if (prop !== 'type' && prop !== 'uom')
                                    tmean.push(data[prop])
                            }
                            break;
                        default:
                            break;
                    }


                })

                $('#climate-chart').highcharts({
                    chart: {
                        zoomType: 'xy',
						height: 400,
                        width: 800
                    },
                    title: {
                        text: 'Monthly climate averages for ' + $paname
                    },
                    subtitle: {
                        // text: 'Source: WorldClimate.com'
                    },
                    xAxis: [{
                        categories: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
                            'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'
                        ]
                    }],
                    yAxis: [{ // Primary yAxis
                        labels: {
                            format: '{value}°C',
                            color: '#3E576F',
                            style: {
                                //color: Highcharts.getOptions().colors[2]
                                color: '#3E576F'
                            }
                        },
                        title: {
                            text: 'Temperature',
                            color: '#3E576F',
                            style: {
                                color: '#3E576F'
                            }
                        },
                        opposite: false

                    }, { // Secondary yAxis
                        gridLineWidth: 0,
                        title: {
                            text: 'Precipitation (mm)',
                            style: {
                                color: '#3E576F'
                            }
                        },
                        labels: {
                            format: '{value} mm',
                            style: {
                                color: '#3E576F'
                            }
                        },
                        opposite: true


                    }],
                    tooltip: {
                        shared: true
                    },
                    credits: {
                        enabled: true,
                        text: 'WorldClim',
                        href: 'http://www.worldclim.org/'
                    },
                    series: [{
                        name: 'Precipitation',
                        type: 'column',
                        color: '#649ab2',
                        yAxis: 1,
                        data: precip,
                        tooltip: {
                            valueSuffix: ' mm'
                        }

                    }, {
                        name: 'Max Temperature',
                        type: 'spline',
                        color: '#B26464',
                        data: tmax,
                        marker: {
                            enabled: true
                        },
                        dashStyle: 'shortdot',
                        tooltip: {
                            valueSuffix: ' °C'
                        }
                    }, {
                        name: 'Mean Temperature',
                        type: 'spline',
                        color: '#B2AE64',
                        yAxis: 0,
                        data: tmean,
                        marker: {
                            enabled: true
                        },
                        dashStyle: 'shortdot',
                        tooltip: {
                            valueSuffix: ' °C'
                        }
                    }, {
                        name: 'Min Temperature',
                        type: 'spline',
                        color: '#81AFD5',
                        yAxis: 0,
                        data: tmin,
                        marker: {
                            enabled: true
                        },
                        dashStyle: 'shortdot',
                        tooltip: {
                            valueSuffix: ' °C'
                        }
                    }]
                });

            }
        },
        error: function() {
            jQuery('#climate-chart.rest-good').switchClass( "rest-good", "rest-error", 100 );
            jQuery('#climate-chart').append('The climate services are down.')
        }
    });

});