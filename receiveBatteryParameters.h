#pragma once

#include <iostream>
#include <vector>

typedef struct  {
    std::vector<float> chargingCurrent;
    std::vector<float> temperature;
} batteryParameters;


std::string readFromConsole();
batteryParameters processSensorData(std::string);
float findMinumumValue(std::vector<float>);
float findMaximumValue(std::vector<float>);
float calculateMovingAverage(std::vector<float>);
std::string formatOutput(float, float, float, float, float);
void printToConsole(std::string);