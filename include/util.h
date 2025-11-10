#pragma once
#include <ostream>
#include <math.h>


/// @brief Clamps the input inbetween the min and max value
/// @param input The value being clamped
/// @param min The minimum value that the output can be
/// @param max The maximum value that the output can be
/// @return Returns the input that has been clamped between min and max
float clamp(float input, float min, float max);

/// @brief Gives the accurate value of pi, probably not neccessary but cool :)
/// @return Returns pi
const float pi();

float degTo360(float angle);

float degTo180(float angle);

float degToInches(float deg, float wheelDiameter);

float degToRad(float degrees);

float inTermsOfNegative180To180(float angle);

void writeToCard(std::string filename, std::string text);
void writeToCard(std::string filename, float number);

enum ODOM_TYPE{NO_ODOM=0, HORIZONTAL_AND_VERTICAL=1, TWO_VERTICAL=2, TWO_AT_45=3};

float wheelDiameter45 = 2.0; 
float leftRotationDistance = 1.5;
float rightRotationDistance = 1.5;
