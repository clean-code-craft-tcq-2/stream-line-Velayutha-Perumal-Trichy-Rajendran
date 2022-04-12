#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <string>
#include <iomanip>
#include <math.h>
#include <fstream>

typedef struct  {
    std::vector<float> chargingCurrent;
    std::vector<float> temperature;
} batteryParameters;

using outputFunctionPtr = void (*)(std::string);
using inputFunctionPtr = std::vector<std::string> (*)(void);

std::vector<std::string> readFromConsole();
batteryParameters processSensorDataVector(std::vector<std::string>);
std::vector<float> extractReadingsFromString(std::string);
std::vector<std::string> splitStringByDelimiter(std::string, std::string);
float findMinumumValue(std::vector<float>);
float findMaximumValue(std::vector<float>);
float calculateMovingAverage(std::vector<float>);
std::string convertFloatToString(float ,int);
std::string formatOutput(float, float, float, float, float, float);
void printToConsole(std::string);
bool receiveAndProcessSensorData(inputFunctionPtr, outputFunctionPtr);