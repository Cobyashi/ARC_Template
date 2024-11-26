#include "Odom.h"

Odom::Odom(rotation forward1, rotation forward2, rotation lateral, const float ODOM_WHEEL_DIAMETER):
forward1(forward1),
forward2(forward2),
lateral(lateral),
ODOM_WHEEL_DIAMETER(3.25)
{}

float Odom::get_current_X_rotation(rotation lateral){
    return lateral.position(degrees);
}

float Odom::get_current_Y_rotation(rotation forward1, rotation forward2){
    return (forward1.position(degrees) + forward2.position(degrees))/2.0;
}

void Odom::reset_position(rotation lateral){
    lateral.setPosition(0, degrees);
}

void Odom::reset_position(rotation forward1, rotation forward2){
    forward1.setPosition(0, degrees);
    forward2.setPosition(0, degrees);
}

void Odom::set_starting_position(float x_pos, float y_pos, float angle){
    LDriveOld = y_pos;
    RDriveOld = y_pos;
    current_Y_position = y_pos;
    current_X_position = x_pos;
    current_heading = angle; 
}

void Odom::update_field_position(){
    headingForwardLeftDist = change_in_heading*(M_PI/180.0)*forwardLeftDistFromCenter;
    headingForwardRightDist = change_in_heading*(M_PI/180.0)*forwardRightDistFromCenter;
    headingLateralDist = change_in_heading*(M_PI/180.0)*lateralDistFromCenter;

    current_X_position = get_current_X_rotation(lateral)/(360.0*(ODOM_WHEEL_DIAMETER*M_PI));
    current_Y_position = get_current_Y_rotation(forward1, forward2)/(360.0*(ODOM_WHEEL_DIAMETER*M_PI));

    current_X_position -= headingLateralDist;
    current_Y_position -= ((headingForwardLeftDist+headingForwardRightDist)/2.0);
}

/// @brief Updates the heading given two forward rotation sensors
void Odom::update_heading_2_fwd(){
    // (change in left wheel movement - change in right wheel movement)/
    // (dist L pod is from center + dist R pod is from center)
    float changeL = forward1.position(degrees)/(360.0*(ODOM_WHEEL_DIAMETER*M_PI)) - LDriveOld;
    float changeR = forward2.position(degrees)/(360.0*(ODOM_WHEEL_DIAMETER*M_PI)) - RDriveOld;
    change_in_heading = (changeL-changeR)/(forwardLeftDistFromCenter+forwardRightDistFromCenter);
    change_in_heading *= (180.0/M_PI);
    LDriveOld = forward1.position(degrees)/(360.0*(ODOM_WHEEL_DIAMETER*M_PI));
    RDriveOld = forward2.position(degrees)/(360.0*(ODOM_WHEEL_DIAMETER*M_PI));
}

/// @brief Updates the heading given one lateral rotation sensor
void Odom::update_heading(){
    
}

/// @brief Gets the current X position of the robot
/// @return current_X_position
float Odom::getX(){
    return current_X_position;
}

/// @brief Gets the current Y position of the robot
/// @return current_Y_position 
float Odom::getY(){
    return current_Y_position;
}

/// @brief Gets the current heading of the robot
/// @return change_in_heading
float Odom::getHeading(){
    return change_in_heading;
}