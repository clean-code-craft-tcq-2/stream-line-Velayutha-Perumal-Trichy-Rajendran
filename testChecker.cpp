#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "dataAquisition.h"
#include <string.h>
#include <stdio.h>

SCENARIO("Validate JSON Data format")
{
    GIVEN("sensor data of battery temperature and charging current")
    {
		char actualData[64];
		char *expectedData = "{\"Temperature\": 23.7, \"ChargingCurrent\": 5.6}";
		BMS sensor_data;
		sensor_data.temperature = 23.7;
		sensor_data.chargingCurrent = 5.6;

        WHEN("postProcessingSensorData() is called with given sensor data")
        {
            postProcessingSensorData (sensor_data, actualData);
            THEN("raw sensor data will be converted to Json format")
            {
                REQUIRE(strcmp(actualData, expectedData) == 0);
            }
        }
    }
}
