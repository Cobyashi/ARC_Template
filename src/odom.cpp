#include "Odom.h"

Odom::Odom(rotation forwardR, rotation forwardL, rotation lateral, float forward_right_wheel_diameter, float forward_left_wheel_diameter, float lateral_wheel_diameter, float forward_right_rotation_distance, float forward_left_rotation_distance, float lateral_rotation_distance){
    this->forwardR = forwardR;
    this->forwardL = forwardL;
    this->lateral = lateral;

    this->forward_right_wheel_diameter = forward_right_wheel_diameter;
    this->forward_left_wheel_diameter = forward_left_wheel_diameter;
    this->lateral_wheel_diameter = lateral_wheel_diameter;
}

void Odom::reset_rotation(){
    forwardR.setPosition(0, degrees);
    forwardL.setPosition(0, degrees);
    lateral.setPosition(0, degrees);
}

float Odom::get_x_position(){
    return x_position;
}

float Odom::get_y_position(){
    return y_position;
}

float Odom::get_heading(){
    return heading;
}

float Odom::get_forward_right_degrees(){
    return forward_degreesR;
}

float Odom::get_forward_left_degrees(){
    return forward_degreesL;
}

float Odom::get_lateral_degrees(){
    return lateral_degrees;
}

void Odom::set_position(float x_position, float y_position, float heading = 0.0){
    this->x_position = x_position;
    this->y_position = y_position;
    this->heading = heading;
}

void Odom::set_heading(float heading){
    this->heading = heading;
}

void Odom::update_position_two_forward(rotation forwardR, rotation forwardL, rotation lateral){
    //Get current positions based on rotation sensors
    float current_forward_right_position = forwardR.position(degrees)/360.0*(M_PI*forward_right_wheel_diameter);
    float current_forward_left_position = forwardL.position(degrees)/360.0*(M_PI*forward_left_wheel_diameter);
    float current_lateral_position = lateral.position(degrees)/360.0*(M_PI*lateral_wheel_diameter);

    //Get positions since last update
    float old_forward_right_position = get_forward_right_degrees()/360.0*(M_PI*forward_right_wheel_diameter);
    float old_forward_left_position = get_forward_left_degrees()/360.0*(M_PI*forward_left_wheel_diameter);
    float old_lateral_position = get_lateral_degrees()/360.0*(M_PI*lateral_wheel_diameter);

    //Get the change based on rotations
    float delta_forward_right = current_forward_right_position - old_forward_right_position;
    float delta_forward_left = current_forward_left_position - old_forward_left_position;
    float delta_lateral = current_lateral_position-old_lateral_position;

    //Gives answer in radians
    float delta_heading = (delta_forward_left-delta_forward_right)/(forward_left_rotation_distance+forward_right_rotation_distance);
    float delta_y = 2.0*((delta_forward_right/delta_heading)+forward_right_rotation_distance)*sin(delta_heading/2.0);
    float delta_x = 2.0*((delta_lateral/delta_heading)+lateral_rotation_distance)*sin(delta_heading/2.0);

    //Update x and y positions and heading
    set_position((delta_x+get_x_position()), (delta_y+get_y_position()), ((delta_heading*180.0/M_PI)+get_heading()));

}

void Odom::update_position_one_forward(rotation forward, rotation lateral, inertial heading_gyro){
    //Get current positions based on rotation sensors
    float current_forward_position = forwardR.position(degrees)/360.0*(M_PI*forward_right_wheel_diameter);
    float current_lateral_position = lateral.position(degrees)/360.0*(M_PI*lateral_wheel_diameter);

    //Get positions since last update
    float old_forward_position = get_forward_right_degrees()/360.0*(M_PI*forward_right_wheel_diameter);
    float old_lateral_position = get_lateral_degrees()/360.0*(M_PI*lateral_wheel_diameter);

    //Get the change based on rotations
    float delta_forward = current_forward_position - old_forward_position;
    float delta_lateral = current_lateral_position-old_lateral_position;

    //Gives answer in radians
    float delta_heading = heading_gyro.heading()-get_heading();
    float delta_y = 2.0*((delta_forward/delta_heading)+forward_right_rotation_distance)*sin(delta_heading/2.0);
    float delta_x = 2.0*((delta_lateral/delta_heading)+lateral_rotation_distance)*sin(delta_heading/2.0);

    //Update x and y positions and heading
    set_position((delta_x+get_x_position()), (delta_y+get_y_position()), (delta_heading+get_heading()));

}

