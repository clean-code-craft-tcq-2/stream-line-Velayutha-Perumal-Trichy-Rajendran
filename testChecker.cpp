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
			printf ("actual is %s\nexpected is %s\n", actualData, expectedData);
            THEN("raw sensor data will be converted to Json format")
            {
                REQUIRE(strcmp(actualData, expectedData) == 0);
            }
        }
    }
}

SCENARIO("Validate data stream in newline")
{
    GIVEN("sensor data in json format")
    {
		FILE *endPoint = fopen("./output.txt", "w");
		char *sensorData = "{\"Temperature\": 23.7, \"ChargingCurrent\": 5.6}";
		char outputBuf[64];
		char *expectedData = "{\"Temperature\": 23.7, \"ChargingCurrent\": 5.6}\n";
        WHEN("streamData() is called with given sensor data")
        {
            streamData (sensorData, endPoint);
			fclose(endPoint);
			endPoint = fopen("./output.txt", "r");
			fgets(outputBuf, strlen(sensorData)+2, endPoint);
			fclose(endPoint);
			
			printf ("%lu:%lu\n", strlen(expectedData), strlen(outputBuf));
            THEN("output sensor data will be generated with new line")
            {
                REQUIRE(strlen(outputBuf) == strlen(expectedData));
            }
        }
    }
}
