#include "Odom.h"

Odom::Odom(rotation forward1, rotation forward2, rotation lateral):
forward1(forward1),
forward2(forward2),
lateral(lateral)
{}

float Odom::get_current_X_position(rotation lateral){
    return lateral.position(degrees);
}

float Odom::get_current_Y_position(rotation forward){
    return forward.position(degrees);
}

void Odom::go_to_position(float x_pos, float y_pos, rotation forward1, rotation forward2, rotation lateral){
    float avgFwdPos;

}

void Odom::reset_position(rotation lateral){
    lateral.setPosition(0, degrees);
}

void Odom::reset_position(rotation forward1, rotation forward2){
    forward1.setPosition(0, degrees);
    forward2.setPosition(0, degrees);
}

