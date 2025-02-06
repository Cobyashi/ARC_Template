#pragma once

#include "vex.h"
#include <vector>

class inertial_group
{
    private:

    std::vector<inertial> group;

    public:
    
    template <typename... Args>
    inertial_group( vex::inertial &i1, Args &... i2 );

    void calibrate();
    bool isCalibrating();
    void resetHeading();
    void setHeading(float value, vex::rotationUnits units);
    float heading();
    void resetRotation();
    void setRotation(float value, vex::rotationUnits units);
    float rotation();
    float acceleration(vex::axisType type);
    bool installed();

};