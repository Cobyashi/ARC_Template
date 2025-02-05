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

    void turn(float turnDegrees);
    void turn_degrees(float degrees);
    void turn_to_angle(float desired_heading, float current_heading);
    void move_to_position(float, float);
    void bezier_turn(float, float, float, float, float, float, int);
};