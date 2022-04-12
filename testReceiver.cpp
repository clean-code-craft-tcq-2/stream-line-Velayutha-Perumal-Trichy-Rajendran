#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"
#include "receiveBatteryParameters.h"

TEST_CASE("test case for extractReadingsFromString function") {
    std::string inputString = "{\"Temperature\": 50.0, \"ChargingCurrent\": 6.7}\n{\"Temperature\": 55.0, \"ChargingCurrent\": 6.9}";
    std::vector<float> expectedOutput, output;
    expectedOutput = {50.0, 6.7, 55.0, 6.9};
    output = extractReadingsFromString(inputString);
    REQUIRE(expectedOutput == output);
}

TEST_CASE("test case for checking processSensorData function") {
    std::vector<std::string>  inputStringVector = {"{\"Temperature\": 50.0, \"ChargingCurrent\": 6.7}", "{\"Temperature\": 55.0, \"ChargingCurrent\": 6.9}"};
    batteryParameters expectedOutput, output;
    expectedOutput.temperature = {50.0, 55.0};
    expectedOutput.chargingCurrent = {6.7, 6.9};
    output = processSensorDataVector(inputStringVector);
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

TEST_CASE("test case for convertFloatToString function") {
    float number = 3.145;
    int precision = 2;
    std::string output, expectedOutput = "3.14";
    output = convertFloatToString(number, precision);
    REQUIRE(expectedOutput == output);
}

TEST_CASE("test case for formatOutput function") {
    float minTemp = 24.0, maxTemp = 84.5, minCharge = 1.3, MaxCharge = 9.4, avgTemp = 60.87, avgCharge = 7.2;
    std::string output = formatOutput(minTemp, maxTemp, minCharge, MaxCharge, avgTemp, avgCharge);
    std::string expectedOutput = "Temperature Data\n\tMinimum : 24.00\n\tMaximum : 84.50\n\tAverage : 60.87\nCharging Current Data\n\tMinimum : 1.30\n\tMaximum : 9.40\n\tAverage : 7.20";
    REQUIRE(expectedOutput == output);
}