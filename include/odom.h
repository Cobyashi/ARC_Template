#pragma once

#include "vex.h"

using namespace vex;

class Odom
{
    private:
    float x_pos, y_pos;
    float forwardRightDistFromCenter, forwardLeftDistFromCenter, lateralDistFromCenter;
    rotation forward1;
    rotation forward2;
    rotation lateral;

    const float ODOM_WHEEL_DIAMETER;
    float current_heading, new_heading;
    float change_in_heading; 
    float headingForwardLeftDist, headingForwardRightDist; //Number of inches the rotation moved based on the change in heading
    float headingLateralDist; //Number of inches the rotation moved based on the change in heading

    float current_X_position, current_Y_position;
    float LDriveOld, RDriveOld;

    public:

    float get_current_X_rotation(rotation lateral);
    float get_current_Y_rotation(rotation forward1, rotation forward2);
    
    void reset_position(rotation lateral);
    void reset_position(rotation forward1, rotation forward2);

    void set_starting_position(float, float, float);
    void update_field_position();
    void update_heading();

    Odom(rotation forward1, rotation forward2, rotation lateral, const float ODOM_WHEEL_DIAMETER);

};