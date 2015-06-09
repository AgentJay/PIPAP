
# World Bank API module for Drupal (wbapi)

This module provides a Drupal side interface for the World Bank's data API. The
goal of the module is to simplify retrieving data from the API for use within a
Drupal site. See this module in action on data.worldbank.org!

If you just want to build some views, you may never have to work
at all with the wbapi module directly: see the description of the
World Bank Query module below!

The API spec is located at http://data.worldbank.org/developers/api-overview.
It is a simple API that works over HTTP GET, receiving a URL and returning
either an XML or JSON response. wbapi.request.inc basically creates a few
request object wrappers that turn parameters into URLs, sends them to the
World Bank API url (configurable, but the only API implementing server is
probably at the default) and then turns the result into an array.

The module does not offer full access to all the methods and parameters that the
API offers. Specifically:

* None of the `photo` related methods are implemented.
* Simple queries are supported in place of more complex ones where ever
  possible.

## Caching

The module aggresively caches any data it recieved, and is designed with the
idea that you want to make as few external calls as possible. The module
handles paged responses, and will make up to 10 requests to attempt to
retrieve the full result set.

On the `admin > settings > world bank api` page you can configure a minimum
cache lifetime. Options are 'One day', 'Two days', 'One week', 'Two weeks' and
'permanent'.

Additionally module will cache API calls that are not sucessful for 5 minutes.
This behavior is designed to prevent denial of service situations.

## Changes from the API

The module implements two methods that are missing for the API. Many of these
were implemented for the sake of the wbquery views integration.

* `regions` Get all the regions the API is aware of
* `languages` Get all the languages the API is aware of.
* `data` Retrieves data series, as distinct from the `indicators` method which
   retrieves indicator meta-data.

# World Bank Query module (wbquery)

The wbquery module utilizes the wbapi module and provides Views integration
atop it. If you use wbquery, you may never have to learn anything about
the actual API. This module requires Views 3 and creates a WB API
implementing views query back-end plugin as well as some basic field,
sort, and filter handlers.

Because the query backend is NOT at all related to MySQL, you can't join
to non WBAPI tables or do most of the usual Views tomfoolery. If you want
more complex stuff, your best bet is extending this module using custom
handlers that run their own subqueries or creating some snazzy custom
style plugins and display logic. Creating views is done through the
standard interface, just pick one of the WBAPI base tables. These are:

* Countries: Lists all the countries in the WBAPI database, includes fields
such as region, name, code, capital, location, etc. Has an argument for
region ID.
* Regions: List IDs and names for World Bank standard regions.
* Topics: Lists names and descriptions of topics, which are groups of indicators.
* Indicators: Lists indicators, which are different pieces of data, including
their name and description. There are arguments to filter by topic.
* Data: Actually extract data. This view MUST be filtered by indicator AND
country/region. Has arguments and fields that deal with filtering by year and
displaying series of data points. When filtering by region you receive the
data for that region overall, NOT a listing for all countries in that region.

If you want to return all listings, use the "countries" keyword to return all
countries (will exclude regions). Use the "regions" keyword to return only
all region listings. You STILL NEED the argument to be present, perhaps with
this as a default value.

Most of the fields, filters, and arguments are pretty straightforward. The data
view has some gotchas, in that it needs the two above mentioned filters to work,
and the Meta: Series field reorganizes/renames the values and thus can break
the simple value fields. Any such problems should be apparent when previewing.

Arguments for country code, region, etc can usually accept multiple options by
using a : syntax, as explained in the API online docs. For instance, "SAS:MNA"
returns results for South Asia and Middle East & North Africa. For dates, the
: sytax specifies a range, ie "2004:2008" returns values from 2004-2008, inclusive.

When you use an argument provided by the wbapi module, such as the indicator
id argument, be sure to add the corresponding argument validator to the argument 
when you create that argument.  For example, if you add the Country ID argument
to you view, when you set that argument handler up you should choose from the
"Validaor options" fieldset the validator "World Bank API: Country" which will
ensure that the argument passed to the view is a valid country.

## Default views

The wbquery module comes with a few default views which are disabled by default.
Enable these default views and use them as a starting point or for reference
as to how to go about contructing your own views.
