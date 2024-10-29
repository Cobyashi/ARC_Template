#pragma once

#include "vex.h"

using namespace vex;

class Odom
{
    private:
    float x_pos, y_pos;
    rotation forward1;
    rotation forward2;
    rotation lateral;

    public:

    float get_current_X_position(rotation lateral);
    float get_current_Y_position(rotation forward);
    void go_to_position(float x_pos, float y_pos, rotation forward1, rotation forward2, rotation lateral);
    
    void reset_position(rotation lateral);
    void reset_position(rotation forward1, rotation forward2);

    Odom(rotation forward1, rotation forward2, rotation lateral);

};