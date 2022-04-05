#include "dataAquisition.h"
#include <stdio.h>

void convertSensorDataToJson (BMS sensor_data, char *jsonData)
{
	sprintf (jsonData, "{\"Temperature\": %.1f, \"ChargingCurrent\": %.1f}", sensor_data.temperature, sensor_data.chargingCurrent);
	return;
}

void streamDataToConsole (char *dataStream)
{
	printf ("%s\n", dataStream);
	return;
}

void postProcessingSensorData (BMS sensor_data, char *jsonData)
{
	convertSensorDataToJson(sensor_data, jsonData);
	return;
}