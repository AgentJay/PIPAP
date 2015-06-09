function pad(n) {
    return n < 10 ? '0' + n.toString() : n.toString()
}

var g_dates = function(raw_date) {
    //converting date (dd-mm-yyyy) to milliseconds
    var date = raw_date.toString();
    //console.log(raw_date)

    var day = date.substring(0, 2);
    var month = date.substring(3, 5);
    var year = date.substring(6, 10);

    return Date.parse(year + '-' + month + '-' + day) / 1000
}

var g_month_year = function(raw_date) {
    var date = raw_date.toString();
    var year = date.substring(0, 4);
    var month = date.substring(4, 6)

    return year + '_' + month;
}
var g_year = function(raw_date) {
    var date = raw_date.toString();
    //console.log(raw_date)
    var year = date.substring(0, 4);
    var month = date.substring(4, 6)

    //console.info(year+'-'+month+'-'+day)
    return year;
}

var datepicker_to_ajax = function(raw_date) {

    var day = raw_date.substring(0, 2);
    var month = raw_date.substring(3, 5);
    var year = raw_date.substring(6, 10);

    return year + month + day;
}

var monthNames = {
    '01': 'Jan',
    '02': 'Feb',
    '03': 'Mar',
    '04': 'Apr',
    '05': 'May',
    '06': 'Jun',
    '07': 'Jul',
    '08': 'Aug',
    '09': 'Sep',
    '10': 'Oct',
    '11': 'Nov',
    '12': 'Dec'
};

var fire_records;
var heat;

(function($) {

    var datepicker_dates = {};
    var slider_dates = {};

    $(document).bind('leaflet.map', function(e, map, lMap) {
        function get_from(slider_dates) {
            if (typeof(slider_dates.d_inicial) == 'undefined') {
                slider_dates.d_inicial = datepicker_dates.d_inicial;
                return slider_dates.d_inicial;
            } else {
                return slider_dates.d_inicial;
            }
        }

        function slider_options() {

            var slider_obj = {
                type: "double",
                min: g_dates(datepicker_dates.d_inicial),
                max: g_dates(datepicker_dates.d_final),
                from: get_from(slider_dates),
                grid: true,
                prettify: function(num) {
                    return moment(num, "X").format("LL");
                },

                onStart: function(data) {
                    //console.log("onStart");
                },
                onChange: function(data) {
                    var min = data.from;
                    var max = data.to;

                    var user_min_date = new Date();
                    //data is in SECONDS
                    user_min_date.setTime(min * 1000)

                    //final!!!!!
                    var this_min_date = pad(user_min_date.getDate()) + '-' + pad(user_min_date.getMonth() + 1) + '-' + user_min_date.getFullYear();
                    $('#datetimepicker_inicial input').val(this_min_date)

                    var user_max_date = new Date();
                    //data is in SECONDS
                    user_max_date.setTime(max * 1000)

                    var this_max_date = pad(user_max_date.getDate()) + '-' + pad(user_max_date.getMonth() + 1) + '-' + user_max_date.getFullYear();

                    $('#datetimepicker_final input').val(this_max_date);
                },
                onFinish: function(data) {

                    d_inicial = $('#datetimepicker_inicial input').val()
                    d_final = $('#datetimepicker_final input').val();

                    $('#ex_fires').trigger('click');
                    //console.warn(data);
                },
                onUpdate: function(data) {
                    //console.log("onUpdate");
                }
            }
            return slider_obj;
        }


        heat = L.heatLayer({
            radius: 12,
            gradient: {
                0.4: 'green',
                0.65: 'yellow',
                0.9: 'red'
            }
        }).addTo(lMap);

        var max_x = $('.field-name-field-bbox-max-x').text();
        var max_y = $('.field-name-field-bbox-max-y').text();
        var min_x = $('.field-name-field-bbox-min-x').text();
        var min_y = $('.field-name-field-bbox-min-y').text();
        var bounds = lMap.getBounds();
		
		$('a#quicktabs-tab-protected_area_tabs-5').click(function() {

            $('#datetimepicker_inicial').add('#datetimepicker_final').datepicker({
                //   format: 'yyyymmdd',
                format: 'dd-mm-yyyy',
                language: 'en',
                viewMode: "months",
                minViewMode: "months"

            }).on('changeDate', function(e) {
                datepicker_dates.d_inicial = $('#datetimepicker_inicial input').val();
                datepicker_dates.d_final = $('#datetimepicker_final input').val();
                $(this).parents().find('.dropdown-menu').hide();
            });
			var today = new Date();
			var dd = today.getDate();
			var mm = today.getMonth()+1; //January is 0!
			var yyyy = today.getFullYear();

			if(dd<10) {
				dd='0'+dd
			} 

			if(mm<10) {
				mm='0'+mm
			} 
			
			today = dd+'-'+mm+'-'+yyyy;

            //var d_final = yyyy+mm+dd;
            //var d_inicial = 20140601;

            datepicker_dates.d_inicial = '01-06-2014';
            datepicker_dates.d_final = today;
            lMap.spin(true);

            slider = $("#rangedate").data("ionRangeSlider");

            $("#rangedate").ionRangeSlider(slider_options()); //end rangedate slider

            var url = 'http://lrm-maps.jrc.ec.europa.eu/fireproxy/fireproxy/urlproxy.jsp?url=http://dopa-services.jrc.ec.europa.eu/services/fire/estation/getfireheatmapdata?minx=' + min_x + '&miny=' + min_y + '&maxx=' + max_x + '&maxy=' + max_y + '&startdate=' + datepicker_to_ajax(datepicker_dates.d_inicial) + '&enddate=' + datepicker_to_ajax(datepicker_dates.d_final);
            //executed when loading page
            $.ajax({

                url: url,
                dataType: 'json',
                success: function(d) {

                    var first = true;
                    update_map(d, first);
                    //console.warn(d)
                    lMap.spin(false);


                }
            })
        })

        var plot_options = {

            series: {
                bars: {
                    hoverable: true,
                    clickable: true,
                    autoHighlight: true,
                    show: true,
                    barWidth: 0.6,
                    align: "left"
                }
            },
            xaxis: {
                mode: "categories",
                tickLength: 0,
				labelAngle: 120,
				labelWidth: 50,
				labelHeight: 50
            },
            grid: {
                hoverable: true,
                clickable: true
            },

            tooltip: true,
            tooltipOpts: {
                content: 'hoooola',
                shifts: {
                    x: -60,
                    y: 25
                }
            }
        }

        function update_map(d, first) {

            var graph_data = [];
            arr = []
            arr2 = []
            var p_count = d.records.length;
            months_data = []
            arr_months = []
            var arr_obj = {}
            months_group = [];

            if (first == true) {

                $.each(d.records, function(i, d) {
                    //get month 
                    var _month_year = g_month_year(d.stamp);
                    if ($.inArray(_month_year, arr_months) == -1) {
                        arr_months.push(_month_year)
                        months_data.push({
                            _year: g_year(d.stamp),
                            _month_year: _month_year,
                            data: new L.FeatureGroup(),
                            count: 0
                        })
                    }
                })

                fire_records = d.records;
                $.each(d.records, function(i, d) {

                    arr2.push([d.y, d.x, 45]);

                    var _month_year = g_month_year(d.stamp);
                    for (var p in months_data) {
                        if (months_data[p]._month_year == _month_year) {
                            //console.info(month+' ====== '+months_data[p]._month)
                            L.circle([d.y, d.x], 3, {

                                    fillColor: '#EA5BE3',

                                    fillOpacity: 0.7,
                                    ms_date: g_dates(d.stamp),
                                    month: _month_year
                                }).bindPopup('Date of fire: <b>' + d.stamp + '</b>').addTo(months_data[p].data)
                                ++months_data[p].count;
                            //console.info(months_data[p]._month)
                        }
                    }
                })

                $('#months .fires_month_count').html('<b>' + p_count + '</b> fires found<br><br>');
                heat.setLatLngs(arr2);
                heat.setOptions({
                    radius: 12,
                    gradient: {
                        0.4: 'green',
                        0.65: 'yellow',
                        0.9: 'red'
                    }
                });
                lMap.spin(false);

                $('#months ul').empty()

                for (var p in months_data) {
                    var t_month = months_data[p]._month_year;

                    var n_date = t_month.split('_');

                    var month_text = monthNames[n_date[1]];
                    var year_text = n_date[0];

                    var t_data = months_data[p].data;
                    t_data._month_year = t_month;
                    t_data.addTo(lMap)

                    $('#months ul').append('<li><input type="checkbox" checked><span class="' + months_data[p]._month_year + '">' + month_text + ' ' + n_date[0] + ' (' + months_data[p].count + ' records)</span></input></li>');

                    graph_data.push([month_text + ' ' + year_text, months_data[p].count])
                }

                var dataset = [{
                    data: graph_data,
                    color: "#d46965"
                }];

                $.plot("#fires_flot_placeholder", dataset, plot_options);

                jQuery('#months').show();

                $('#months ul').click(function(e) {
                    if ($(e.target).is('input')) {
                        $input = $(e.target);

                        var this_month = $input.next().attr('class');
                        var checked = $input.is(':checked')

                        for (var p in lMap._layers) {

                            if (lMap._layers[p]._month_year == this_month) {
                                if (checked)
                                    lMap._layers[p].setStyle({
                                        color: '#EAE71E',
                                        fillColor: '#2338DB',
                                        'opacity': 1,
                                        'fillOpacity': 1
                                    })
                                else
                                    lMap._layers[p].setStyle({
                                        color: '#EAE71E',
                                        fillColor: '#2338DB',
                                        'opacity': 0,
                                        'fillOpacity': 0
                                    })
                            }
                        };
                    }
                })

                $('#fire_heatmap').click(function() {
                    if ($(this).hasClass('show_heatmap')) //create the points
                    {
                        $(this).removeClass('show_heatmap').addClass('hide_heatmap').text('HIDE heatmap');
                        //console.log(arr2);
                        create_heatmap(arr2);
                    } else {
                        $(this).removeClass('hide_heatmap').addClass('show_heatmap').text('SHOW heatmap');
                        //console.warn(heat)
                        lMap.removeLayer(heat);
                    }
                })
            } else 
			{

                for (var p in lMap._layers) {
                    var this_layer = lMap._layers[p];
                    //console.log(this_layer[p])
                    if (typeof(this_layer._month_year) !== 'undefined' || typeof(this_layer._mRadius) !== 'undefined') {
                        lMap.removeLayer(this_layer)
                    }
                }

                var graph_data = [];
                arr = []
                arr2 = []
                var p_count = d.records.length;
                months_data = []
                arr_months = []
                var arr_obj = {}
                months_group = [];

                $.each(d.records, function(i, d) {
                    var _month_year = g_month_year(d.stamp);
                    if ($.inArray(_month_year, arr_months) == -1) {
                        arr_months.push(_month_year)
                        months_data.push({
                            _year: g_year(d.stamp),
                            _month_year: _month_year,
                            data: new L.FeatureGroup(),
                            count: 0
                        })
                    }
                })

                fire_records = d.records;
                $.each(d.records, function(i, d) {

                    arr2.push([d.y, d.x, 45]);

                    var _month_year = g_month_year(d.stamp);
                    for (var p in months_data) {
                        if (months_data[p]._month_year == _month_year) {
                            //console.info(month+' ====== '+months_data[p]._month)
                            L.circle([d.y, d.x], 3, {

                                    fillColor: '#EA5BE3',

                                    fillOpacity: 0.7,
                                    ms_date: g_dates(d.stamp),
                                    month: _month_year
                                }).bindPopup('Date of fire: <b>' + d.stamp + '</b>').addTo(months_data[p].data)
                                ++months_data[p].count;
                            // console.info(months_data[p]._month)
                        }
                    }
                })

                $('#months .fires_month_count').html('<b>' + p_count + '</b> fires found<br><br>');
                heat.setLatLngs(arr2);
                heat.setOptions({
                    radius: 12,
                    gradient: {
                        0.4: 'green',
                        0.65: 'yellow',
                        0.9: 'red'
                    }
                });
                lMap.spin(false);


                $('#months ul').empty()

                for (var p in months_data) {
                    var t_month = months_data[p]._month_year;

                    var n_date = t_month.split('_');

                    var month_text = monthNames[n_date[1]];
                    var year_text = n_date[0];
                    // .substr(1,1);

                    // setDia(n_date[0]);
                    var t_data = months_data[p].data;
                    t_data._month_year = t_month;
                    t_data.addTo(lMap)

                    // var size=
                    $('#months ul').append('<li><input type="checkbox" checked><span class="' + months_data[p]._month_year + '">' + month_text + ' ' + n_date[0] + ' (' + months_data[p].count + ' records)</span></input></li>');

                    graph_data.push([month_text + ' ' + year_text, months_data[p].count])
                }

                var dataset = [{
                    //label: "Fires",
                    data: graph_data,
                    color: "#d46965"
                }];


                $.plot("#fires_flot_placeholder", dataset, plot_options);

                jQuery('#months').show();
				
                var d_inicial = $('#datetimepicker_inicial input').val()
                var d_final = $('#datetimepicker_final input').val();

                slider = $("#rangedate").data("ionRangeSlider");

                slider.update({
                    min: g_dates(datepicker_dates.d_inicial),
                    max: g_dates(datepicker_dates.d_final),
                    from: g_dates(d_inicial),
                    to: g_dates(d_final)
                })
            }
        }

        function create_heatmap(arr2) {
            heat.setLatLngs(arr2);
            heat.addTo(lMap);
        }

        $('#ex_fires').click(function(e) {

            d_inicial = datepicker_to_ajax($('#datetimepicker_inicial input').val());
            d_final = datepicker_to_ajax($('#datetimepicker_final input').val());
            if (d_inicial == '' || d_final == '') {
                alert('enter a date range!');
                e.preventDefault();
            } else {
                var url = 'http://lrm-maps.jrc.ec.europa.eu/fireproxy/fireproxy/urlproxy.jsp?url=http://dopa-services.jrc.ec.europa.eu/services/fire/estation/getfireheatmapdata?minx=' + min_x + '&miny=' + min_y + '&maxx=' + max_x + '&maxy=' + max_y + '&startdate=' + d_inicial + '&enddate=' + d_final;
                $.ajax({
                    url: url,
                    dataType: 'json',
                    success: function(d) {

                        lMap.fitBounds(bounds)

                        lMap.spin(true);
                        var first = false;
                        update_map(d, first);
                    }
                })

            }
        })

    }); //end leaflet attachment
})(jQuery);