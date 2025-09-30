#include "util.h"

/// @brief Clamps the input inbetween the min and max value
/// @param input The value being clamped
/// @param min The minimum value that the output can be
/// @param max The maximum value that the output can be
/// @return Returns the input that has been clamped between min and max
float clamp(float input, float min, float max)
{
    return input < min ? min : input;

    return input > max ? max : input;
    
    // if(input < min)
    //     return min;
    // if(input > max)
    //     return max;
    // return input;
}

/// @brief Gives the accurate value of pi, probably not neccessary but cool :)
/// @return Returns pi
const float pi()
{
    return atan(1.0) * 4.0;
}

float degTo360(float angle)
{
    return fmod(angle, 360);
}

float degTo180(float angle) 
{
    angle = degTo360(angle);

    if(angle < -180)
        angle += 360;
    if(angle >= 180)
        angle -= 360;
    return angle;
}

/// @brief Transforms a wheels rotation into inches traveled
/// @param deg Current Degree of the motor.
/// @param wheelDiameter The Diameter of the wheel that is attached to the motor or rotation sensor.
/// @return Returns the distance in Inches.
float degToInches(float deg, float wheelDiameter)
{
    return (deg / 360) * pi() * wheelDiameter;
}