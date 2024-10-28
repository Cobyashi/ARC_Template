#pragma once

#include "vex.h"

using namespace vex;

class inertial_group
{
    private:

    inertial* sensors;
    int size = 0;


    public:
    
    inertial_group(inertial * sensorArray, int arraySize);

    float average();

    void calibrate();
    bool isCalibrating();

    void resetHeading();
    void setHeading(float heading, rotationUnits unit);
    float getHeading();

    void resetRotation();
    void setRotation(float rotation, rotationUnits units);
    float getRotation(rotationUnits units);

    float acceleration(axisType axis);

};