#pragma once

#include "vex.h"

using namespace vex;

class Odom
{
    private:
        float lateral_degrees;
        float forward_degreesR;
        float forward_degreesL;

        float x_position;
        float y_position;
        float heading;

        rotation forwardR;
        rotation forwardL;
        rotation lateral;
    
    public:
        float forward_right_wheel_diameter;
        float forward_left_wheel_diameter;
        float lateral_wheel_diameter;

        float forward_right_rotation_distance;
        float forward_left_rotation_distance;
        float lateral_rotation_distance;

        Odom(rotation forwardR, rotation forwardL, rotation lateral, float forward_right_wheel_diameter, float forward_left_wheel_diameter, float lateral_wheel_diameter, float forward_right_rotation_distance, float forward_left_rotation_distance, float lateral_rotation_distance);

        void reset_rotation();

        float get_x_position();
        float get_y_position();
        float get_heading();

        float get_lateral_degrees();
        float get_forward_right_degrees();
        float get_forward_left_degrees();

        void update_heading(rotation forwardR, rotation forwardL, rotation lateral);
        void update_position_two_forward(rotation forwardR, rotation forwardL, rotation lateral);
        void update_position_one_forward(rotation forward, rotation lateral, inertial heading_gyro);

        void set_position(float x_position, float y_position, float heading = 0.0);
        void set_heading(float heading);


};