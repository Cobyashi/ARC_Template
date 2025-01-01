#include "util.h"

/// @brief Clamps the input inbetween the min and max value
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

/// @brief Gives the accurate value of pi, probably not neccessary but cool :)
/// @return Returns pi
const float pi()
{
    return atan(1.0) * 4.0;
}


//DeltaTime
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief DeltaTime Constructor
DeltaTime::DeltaTime() {preTime = 0; updateTime();}

/// @brief Updates the time values of DeltaTime
/// @return The value of DeltaTime
float DeltaTime::updateTime()
{
    time = clock.Timer.time() - preTime;
    preTime = time;

    return time;
}

//Operator Overrides
DeltaTime::operator float() {return updateTime();}
bool DeltaTime::operator==(DeltaTime&DELTATIME) {return updateTime() == DELTATIME.updateTime();}
bool DeltaTime::operator==(float DELTATIME) {return updateTime() == DELTATIME;}
bool DeltaTime::operator==(double DELTATIME) {return updateTime() == DELTATIME;}
bool DeltaTime::operator==(int DELTATIME) {return updateTime() == DELTATIME;}

std::ostream& operator<<(std::ostream& COUT, DeltaTime DELTATIME) {COUT << DELTATIME.updateTime(); return COUT;}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////