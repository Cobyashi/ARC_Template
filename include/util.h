#pragma once

#include "vex.h"

using namespace vex;

/// @brief Clamps the input inbetween the min and max value
/// @param input The value being clamped
/// @param min The minimum value that the output can be
/// @param max The maximum value that the output can be
/// @return Returns the input that has been clamped between min and max
float clamp(float input, float min, float max);

/// @brief Gives the accurate value of pi, probably not neccessary but cool :)
/// @return Returns pi
float pi();