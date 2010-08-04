$Id

-- SUMMARY --

NWS_weather provides a daily weather forecast utilizing the National Weather Service's SOAP interface. SOAP
calls are cached with the standard Drupal caching mechanism to minimize server workload.


-- REQUIREMENTS --

SOAP must be enabled in PHP.


-- INSTALLATION --

Install as usual, see http://drupal.org/node/70151 for further information.


-- CONFIGURATION --

Configure weather block in Administer >> Site Configuration >> NWS_Weather

These options should be self explanatory. Use Administer >> Site Building >> Blocks to enable and place the 
'NWS weather forecast' block.


-- ADVANCED USAGE --

The block defined by NWS_weather allows simple access to weather forecast data for one point. Developers
who would like to retrieve data for multiple points or who wish to retrieve more data (wind speed, wind direction, etc.) 
can utilize this module by calling this function:

$forecast=nws_weather_NDFDgen($lat, $lon, array('wdir', 'temp', 'maxt', 'mint'), "time-series", "2009-12-08T12:00", "2009-12-09T12:00");

None of the configuraton options exposed on the Administer >> Site Configuration >> NWS_Weather admin page are 
utilized by this function. The various parameters are discussed here:

http://www.nws.noaa.gov/xml/#use_it

The third parameter, a list of valid forecast data types, is defined in funtion nws_weather_NDFDgen which
is contained in nws_weather.module. Please notice that the passed array is weather values only, not key/value pairs like
the array of options in the code. It is left to the developer to parse the array that is returned.


-- CONTACT --

Current maintainers:
* Dwaine Trummert (dwaine) - http://drupal.org/user/595304


This project has been sponsored by:
* DND COMMUNICATIONS
