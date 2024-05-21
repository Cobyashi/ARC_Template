#pragma once

#include "quickTools.h"

//returns the true value of pi
float pi()
{
    return atan(1) * 4;
}

//Reduces angle input to a value between -180 and 180
float reduce_to_180s(float input)
{
    while(input >= -180 && input < 180)
    {
        if(input < -180)
        {
            input += 360;
        }
        if(input > 180)
        {
            input -= 360;
        }
    }

    return input;
}

//Changes Radians to Degrees
float Rad_to_Deg(float input)
{
    return (pi() / 180) * input;
}

//Changes Degrees to Radians
float Deg_to_Rad(float input)
{
    return (180 / pi()) * input;
}

//Clamps value between minClamp and maxClamp
float clamp(float value, float minClamp, float maxClamp)
{
    if(value < minClamp)
    {
        value = minClamp;
    }

    if(value > maxClamp)
    {
        value = maxClamp;
    }

    return value;
}