#pragma once

typedef struct __BMS__
{
	float temperature;
	float chargingCurrent;
}BMS batteryParams;

void convertSensorDataToJson (BMS sensor_data, char *jsonData);
void streamDataToConsole (char *dataStream);
void postProcessingSensorData (BMS sensor_data, char *jsonData);