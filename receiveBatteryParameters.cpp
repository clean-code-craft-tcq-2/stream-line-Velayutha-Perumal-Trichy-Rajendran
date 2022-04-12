#include "receiveBatteryParameters.h"

std::vector<std::string> readFromConsole() {
    std::vector<std::string> sensorDataStringVector;
    std::string sensorDataString;
    for (int itr = 0; itr < 50; itr ++) {
        std::getline(std::cin, sensorDataString);
        sensorDataStringVector.push_back(sensorDataString);
    }
    return sensorDataStringVector;
}

batteryParameters processSensorDataVector(std::vector<std::string> sensorDataStringVector) {
    batteryParameters batteryParameters;
    std::vector<float> sensorData;
    for (auto itr : sensorDataStringVector) {
        sensorData = extractReadingsFromString(itr);
        if (sensorData.empty() != true) {
            batteryParameters.temperature.push_back(sensorData.at(0));
            batteryParameters.chargingCurrent.push_back(sensorData.at(1));
        }
    }
    return batteryParameters;
}

std::vector<float> extractReadingsFromString(std::string inputString) {
    std::string inputStringCopy = inputString;
    std::string digits = "0123456789.+-eE";
    float sensorReading = 0.0;
    std::vector<float> sensorReadingVector;
    std::stringstream stringStream(inputString);

    while (stringStream.rdbuf()->in_avail()) {
        stringStream >> sensorReading;
        if (stringStream.good() || stringStream.eof()) 
            sensorReadingVector.push_back(sensorReading);
        else if (stringStream.bad()) 
            return {};
        else if (stringStream.fail()) {
            stringStream.clear();
            stringStream.rdbuf()->sbumpc();
        }
    }
    return sensorReadingVector;
}

float findMinumumValue(std::vector<float> sensorData) {
    if(sensorData.empty())
        return NAN;
    return *std::min_element(sensorData.begin(), sensorData.end());
}

float findMaximumValue(std::vector<float> sensorData) {
    if(sensorData.empty())
        return NAN;
    return *std::max_element(sensorData.begin(), sensorData.end());
}

float calculateMovingAverage(std::vector<float> sensorData) {
    if (sensorData.size() >= 5) {
        std::vector<float> slicedSensorData(sensorData.end() - 5, sensorData.end());
        return std::accumulate(slicedSensorData.begin(), slicedSensorData.end(), 0.0) / slicedSensorData.size();
    } else {
        return NAN;
    }
}

std::string formatOutput(
    float minimumTemperature,
    float maximumTemperature,
    float minimumChargingCurrent,
    float maximummChargingCurrent,
    float averageTemperature,
    float averageChargingCurrent) {
    std::string stringToPrint;
    stringToPrint = "Temperature Data\n\tMinimum : " + convertFloatToString(minimumTemperature, 2);
    stringToPrint += "\n\tMaximum : " + convertFloatToString(maximumTemperature, 2);
    stringToPrint += "\n\tAverage : " + convertFloatToString(averageTemperature, 2);
    stringToPrint += "\nCharging Current Data\n\tMinimum : " + convertFloatToString(minimumChargingCurrent, 2);
    stringToPrint += "\n\tMaximum : " + convertFloatToString(maximummChargingCurrent, 2);
    stringToPrint += "\n\tAverage : " + convertFloatToString(averageChargingCurrent, 2);
    return stringToPrint;
}

std::string convertFloatToString(float number, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << number;
    std::string convertedString = stream.str();
    return convertedString;
}

void printToConsole(std::string stringToPrint) {
    std::cout<<stringToPrint<<std::endl;
}

bool receiveAndProcessSensorData(inputFunctionPtr inputFPtr, outputFunctionPtr outputFPtr) {
    std::string outputString;
    std::vector<std::string> inputSensorDataStringVector;
    inputSensorDataStringVector = (*inputFPtr)();
    if (inputSensorDataStringVector.empty())
        return false;
    batteryParameters batteryParameters;
    batteryParameters = processSensorDataVector(inputSensorDataStringVector);
    float minimumTemperature = findMinumumValue(batteryParameters.temperature);
    float maximumTemperature = findMaximumValue(batteryParameters.temperature);
    float averageTemperature = calculateMovingAverage(batteryParameters.temperature);
    float minimumChargingCurrent = findMinumumValue(batteryParameters.chargingCurrent);
    float maximummChargingCurrent = findMaximumValue(batteryParameters.chargingCurrent);
    float averageChargingCurrent = calculateMovingAverage(batteryParameters.chargingCurrent);
    bool isInvalidData = (isnan(minimumTemperature) || isnan(minimumChargingCurrent) || 
        isnan(maximumTemperature) || isnan(maximummChargingCurrent) ||
        isnan(averageTemperature) || isnan(averageChargingCurrent));
    if (isInvalidData)
        return false;
    outputString = formatOutput(
        minimumTemperature, maximumTemperature, minimumChargingCurrent,
        maximummChargingCurrent, averageTemperature, averageChargingCurrent);
    (*outputFPtr)(outputString);
    return true;
}