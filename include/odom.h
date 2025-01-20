#pragma once

#include "vex.h"

using namespace vex;

class Odom
{
    private:
        //Variables to hold the degrees turned
        float lateral_degrees;
        float forward_degreesR;
        float forward_degreesL;

        //Variables to store the current position and heading
        float x_position;
        float y_position;
        float heading;

        //Hardware variables
        rotation forwardR;
        rotation forwardL;
        rotation lateral;
        inertial heading_gyro;
    
    public:
        //Wheel diameters for the odometry pods
        float forward_right_wheel_diameter;
        float forward_left_wheel_diameter;
        float lateral_wheel_diameter;

        //Distance the odometry wheels are from the center of the robot
        float forward_right_rotation_distance;
        float forward_left_rotation_distance;
        float lateral_rotation_distance;

        Odom(rotation forwardR, rotation forwardL, rotation lateral, float forward_right_wheel_diameter, float forward_left_wheel_diameter, float lateral_wheel_diameter, float forward_right_rotation_distance, float forward_left_rotation_distance, float lateral_rotation_distance);
        Odom(rotation forward, rotation lateral, inertial heading_gyro, float forward_wheel_diameter, float lateral_wheel_diameter, float forward_rotation_distance, float lateral_rotation_distance);

        void reset_rotation();

        //Accessors
        float get_x_position();
        float get_y_position();
        float get_heading();

        float get_lateral_degrees();
        float get_forward_right_degrees();
        float get_forward_left_degrees();

        //Mutators
        void set_position(float x_position, float y_position, float heading = 0.0);
        void set_heading(float heading);

        void set_forward_right_degrees(float forward_degreesR);
        void set_forward_left_degrees(float forward_degreesL);
        void set_lateral_degrees(float lateral_degrees);

        //Updaters
        void update_position_two_forward(rotation forwardR, rotation forwardL, rotation lateral);
        void update_position_one_forward(rotation forward, rotation lateral, inertial heading_gyro);

        


};