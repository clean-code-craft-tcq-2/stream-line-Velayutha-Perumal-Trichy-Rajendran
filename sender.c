#include "dataAquisition.h"
#define DATA_SIZE	50


float batteryTemperature [DATA_SIZE] = {23.0,42.0,50.0,48.0,39.0,38.0,49.0,1.0,40.0,5.0,
								 45.0,44.0,41.0,37.0,35.0,33.0,31.0,7.0,32.0,2.0,
								 29.0,27.0,25.0,22.0,21.0,20.0,12.0,8.0,13.0,14.0,
								 11.0,4.0,3.0,26.0,47.0,9.0,10.0,15.0,17.0,18.0,
								 16.0,22.0,6.0,24.0,28.0,19.0,43.0,36.0,50.0,30.0};
										 
float batteryChargingCurrent [DATA_SIZE] = {6.7,6.9,7.0,7.2,8.4,8.6,5.8,4.5,5.6,9.9,
									 1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,2.2,
									 2.6,1.6,3.6,4.6,5.6,6.6,7.6,8.6,9.6,3.1,
									 4.4,4.1,1.4,2.4,5.4,6.4,7.4,8.4,9.4,1.7,
									 1.9,2.9,3.9,4.9,5.9,6.9,8.9,9.9,7.7,3.1};


int main ()
{
	char dataStream[64];
	BMS sensor_data;
	
	for (int readIndex = 0; readIndex < DATA_SIZE; readIndex ++)
	{
		sensor_data.temperature = batteryTemperature[readIndex];
		sensor_data.chargingCurrent = batteryChargingCurrent[readIndex];
		postProcessingSensorData (sensor_data, dataStream);
		streamDataToConsole(jsonData);
	}
	
	return 0;
}
												