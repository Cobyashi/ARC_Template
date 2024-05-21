#pragma once
#include "vex.h"

class Drive
{
    private:
    //Variables
    ///////////////////////////////

    //Drive PID
        //Turn Constants
        float turn_Kp;
        float turn_Ki;
        float turn_Kd;
        float turn_starti;
        float turn_settle;
        float turn_settle_error;
        float turn_max_voltage;

        //Drive Constants
        float drive_Kp;
        float drive_Ki;
        float drive_Kd;
        float drive_starti;
        float drive_settle;
        float drive_settle_error;
        float drive_max_voltage;

        //Swing Constants
        float swing_Kp;
        float swing_Ki;
        float swing_Kd;
        float swing_starti;
        float swing_settle;
        float swing_settle_error;
        float swing_max_voltage;

        //Arch Constants
        float arch_Kp;
        float arch_Ki;
        float arch_Kd;
        float arch_starti;
        float arch_settle;
        float arch_settle_error;
        float arch_max_voltage;

        //Heading Constants
        float heading_Kp;
        float heading_Ki;
        float heading_Kd;
        float heading_starti;
        float heading_settle;
        float heading_settle_error;
        float heading_max_voltage;
        
        //States
        float current_heading;
        float wheel_diameter;
        float wheel_ratio;

    ///////////////////////////////

    motor_group right_motor_drive;
    motor_group left_motor_drive;

    inertial Gyro;

    public:

    Drive(motor_group right_motor_drive, motor_group left_motor_drive, inertial & Gyro, float wheel_diameter, float wheel_ratio);

    //Setters
    void set_turn_constants(float turn_Kp, float turn_Ki, float turn_Kd, float turn_starti, float turn_settle, float turn_settle_error, float turn_max_voltage);
    void set_drive_constants(float drive_Kp, float drive_Ki, float drive_Kd, float drive_starti, float drive_settle, float drive_settle_error, float drive_max_voltage);
    void set_swing_constants(float swing_Kp, float swing_Ki, float swing_Kd, float swing_starti, float swing_settle, float swing_settle_error, float swing_max_voltage);
    void set_arch_constants(float arch_Kp, float arch_Ki, float arch_Kd, float arch_starti, float arch_settle, float arch_settle_error, float arch_max_voltage);
    void set_heading_constants(float heading_Kp, float heading_Ki, float heading_Kd, float heading_starti, float heading_settle, float heading_settle_error, float heading_max_voltage);

    //Getters
    float get_left_drive_position();
    float get_right_drive_position();

    //Drives with voltage
    void drive_with_voltage(float left_voltage, float right_voltage);

    //Brakes Drive train
    void brake_drive_train();
    void brake_drive_train(bool left, bool right);

    //Turns to the given angle
    void turn_to_angle(float angle);
    void turn_to_angle(float angle, float turn_max_voltage);

    //Turns with the amount of angle given
    void turn_angle_amount(float angle);
    void turn_angle_amount(float angle, float turn_max_voltage);

    //Drives to the given distance
    void drive_distance(float distance);
    void drive_distance(float distance, float drive_max_voltage, float heading_max_voltage);

    //Swings with left drive
    void left_swing_to_angle(float angle);
    void left_swing_to_angle(float angle, float swing_max_voltage);

    //Swings with right drive
    void right_swing_to_angle(float angle);
    void right_swing_to_angle(float angle, float swing_max_voltage);

    //Drives in an arch leftwards
    void drive_left_arch(float distance, float angle, float arch_speed);
    void drive_left_arch(float distance, float angle, float arch_speed, float arch_max_voltage);

    //Drives in an arch rightwards
    void drive_right_arch(float distance, float angle, float arch_speed);
    void drive_right_arch(float distance, float angle, float arch_speed, float arch_max_voltage);

    //Drives distance and runs function during drive
    void drive_with_function(float distance, void (*func)());
    void drive_with_function(float distance, void (*func)(), float drive_max_voltage);

    //Turns to angle and runs function during turn
    void turn_with_function(float angle, void (*func)());
    void turn_with_function(float angle, void (*func)(), float turn_max_voltage);

};