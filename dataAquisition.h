#pragma once
#include <stdio.h>
typedef struct __BMS__
{
	float temperature;
	float chargingCurrent;
}BMS;

void convertSensorDataToJson (BMS sensor_data, char *jsonData);
void streamData (char *dataStream, FILE *endPoint);
void postProcessingSensorData (BMS sensor_data, char *jsonData);