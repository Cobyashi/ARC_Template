#include "util.h"

/// @brief Clamps the input in between the min and max value
/// @param input The value being clamped
/// @param min The minimum value that the output can be
/// @param max The maximum value that the output can be
/// @return Returns the input that has been clamped between min and max
float clamp(float input, float min, float max)
{
    if(input < min)
        return min;
    if(input > max)
        return max;
    return input;
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
    return (deg / 360) * M_PI * wheelDiameter;
}

/// @brief Converts degrees to inches
/// @param degrees 
/// @return Radians
float degToRad(float degrees){
    return degrees*(M_PI/180.0);
}

float inTermsOfNegative180To180(float angle) 
{
    while(!(angle >= -180 && angle < 180)) 
    {
        if( angle < -180 )
            angle += 360;
        if(angle >= 180)
            angle -= 360;
    }

    return angle;
}

/// @brief Saves information to the SD card
/// @param filename
/// @param text Text to save
// template <typename T>
void writeToCard(std::string filename, std::string text)
{
    std::fstream file;
    file.open(filename, std::ios::out | std::ios::app);
    file << text << std::endl;
    file.close();
}

void writeToCard(std::string filename, float number)
{
    std::fstream file;
    file.open(filename, std::ios::out | std::ios::app);
    file << number << ",";
    file.close();
}