#pragma once

#include "vex.h"

using namespace vex;

class inertial_group
{
    private:

    struct Node
    {
        inertial * value;
        inertial * nextNode;
        bool isHead;
        bool isTail;
    };

    Node* sensors;
    int size = 0;


    public:
    
    inertial_group(inertial * sensorArray, int arraySize);
    ~inertial_group();

    void addNode();

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