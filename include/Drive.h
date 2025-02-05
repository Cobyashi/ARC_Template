#pragma once

#include "vex.h"

using namespace vex;

class Drive
{
    private:

    motor_group left_drive, right_drive;
    //gyro Gyro;
    float maxVoltage;
    float wheelRatio, wheelDiameter;

    public:

    Drive(motor_group left_drive, motor_group right_drive, float wheelDiameter, float wheelRatio, float maxVoltage);

    void arcade();
    void tank();

    float deg_to_inches(float deg);
    float getCurrentPosition();

    void brake();
    void brake(bool left, bool right);

    void drive_distance(float distance);

    void turn_angle();
    void turn_to_angle();
};