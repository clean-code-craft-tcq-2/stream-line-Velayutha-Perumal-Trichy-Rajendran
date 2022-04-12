#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"
#include "receiveBatteryParameters.h"

TEST_CASE("test case for checking processSensorData function") {
    std::string inputString = "{\"Temperature\": 50.0, \"ChargingCurrent\": 6.7}\n{\"Temperature\": 55.0, \"ChargingCurrent\": 6.9}";
    batteryParameters expectedOutput, output;
    expectedOutput.temperature = {50.0, 55.0};
    expectedOutput.chargingCurrent = {6.7, 6.9};
    output = processSensorData(inputString);
    REQUIRE(expectedOutput.temperature == output.temperature);
    REQUIRE(expectedOutput.chargingCurrent == output.chargingCurrent);
}

TEST_CASE("test case for findMinumumValue & findMaximumValue functions") {
    std::vector<float> inputVector = {0.0, 5.4, 7.5, -9 ,10};
    float expectedOutput = -9;
    float output = findMinumumValue(inputVector);
    REQUIRE(expectedOutput == output);
    expectedOutput = 10;
    output = findMaximumValue(inputVector);
    REQUIRE(expectedOutput == output);
}

TEST_CASE("test case for calculateMovingAverage function") {
    std::vector<float> inputVector = {0.0, 5.4, 7.5, 9.0 ,10.8};
    float expectedOutput = 6.54;
    float output = calculateMovingAverage(inputVector);
    REQUIRE(expectedOutput == output);
}