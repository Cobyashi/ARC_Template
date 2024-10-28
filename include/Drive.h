#pragma once

#include "vex.h"

using namespace vex;

class Drive
{
    private:

    motor_group left_drive, right_drive;
    //gyro Gyro;
    float wheel_diameter;
    float max_voltage;

    public:

    Drive(motor_group left_drive, motor_group right_drive, float wheel_diameter, float max_voltage);

    void arcade();
    void tank();

    float deg_to_inches(float deg);
    void brake();
    void brake(bool left, bool right);

    void drive_distance(float distance);

    void turn_angle();
    void turn_to_angle();
};