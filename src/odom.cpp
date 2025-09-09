#include "Odom.h"

/// @brief Constructor for odometry with two forward rotation sensors
/// @param forward_right_wheel_diameter Right side forward rotation wheel diameter
/// @param forward_left_wheel_diameter Left side forward rotation wheel diameter
/// @param lateral_wheel_diameter Lateral rotation wheel diameter
/// @param forward_right_rotation_distance Distance the forward right wheel is from the center (in)
/// @param forward_left_rotation_distance Distance the forward left wheel is from the center (in)
/// @param lateral_rotation_distance Distance the lateral wheel is from the center (in)
Odom::Odom(float forward_right_wheel_diameter, float forward_left_wheel_diameter, float lateral_wheel_diameter, float forward_right_rotation_distance, float forward_left_rotation_distance, float lateral_rotation_distance){
    this->forward_right_wheel_diameter = forward_right_wheel_diameter;
    this->forward_left_wheel_diameter = forward_left_wheel_diameter;
    this->lateral_wheel_diameter = lateral_wheel_diameter;
}

/// @brief Constructor for odometry with one forward rotation sensor
/// @param forward_wheel_diameter Forward rotation wheel diameter 
/// @param lateral_wheel_diameter Lateral rotation wheel diameter
/// @param forward_rotation_distance Distance the forward wheel is from the center (in)
/// @param lateral_rotation_distance Distance the lateral wheel is from the center (in)
Odom::Odom(float forward_wheel_diameter, float lateral_wheel_diameter, float forward_rotation_distance, float lateral_rotation_distance){
    this->forward_right_wheel_diameter = forward_wheel_diameter;
    this->lateral_wheel_diameter = lateral_wheel_diameter;
    this->forward_right_rotation_distance = forward_rotation_distance;
    this->lateral_rotation_distance = lateral_rotation_distance;
}


/// @brief Sets all rotation degrees to 0.0
void Odom::reset_rotation(){
    forward_degreesL = 0.0;
    forward_degreesR = 0.0;
    lateral_degrees = 0.0;
}

//Accessors
float Odom::get_x_position(){ return x_position; }
float Odom::get_y_position(){ return y_position; }
float Odom::get_heading(){ return heading;}
float Odom::get_forward_right_degrees(){ return forward_degreesR; }
float Odom::get_forward_left_degrees(){ return forward_degreesL; }
float Odom::get_lateral_degrees(){ return lateral_degrees; }

//Mutators
void Odom::set_position(float x_position, float y_position, float heading = 0.0){
    this->x_position = x_position;
    this->y_position = y_position;
    this->heading = heading;
}
void Odom::set_heading(float heading){
    this->heading = heading;
}
void Odom::set_forward_right_degrees(float forward_degreesR){
    this->forward_degreesR = forward_degreesR;
}
void Odom::set_forward_left_degrees(float forward_degreesL){
    this->forward_degreesL = forward_degreesL;
}
void Odom::set_lateral_degrees(float lateral_degrees){
    this->lateral_degrees = lateral_degrees;
}


/// @brief Updates the coordinate position of the robot with two forward rotation sensors and one lateral
/// @param forwardR Forward right rotation degrees
/// @param forwardL Forward left rotation degrees
/// @param lateral Lateral rotation degrees
void Odom::update_position_two_forward(float current_forward_right_position, float current_forward_left_position, float current_lateral_position){
    //Get current positions based on rotation sensors
    current_forward_right_position = current_forward_right_position/360.0*(M_PI*forward_right_wheel_diameter);
    current_forward_left_position = current_forward_left_position/360.0*(M_PI*forward_left_wheel_diameter);
    current_lateral_position = current_lateral_position/360.0*(M_PI*lateral_wheel_diameter);

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

    //Update variables to store new location information
    set_forward_left_degrees(current_forward_left_position);
    set_forward_right_degrees(current_forward_right_position);
    set_lateral_degrees(current_lateral_position);

}

/// @brief Updates the coordinate position of the robot with one forward and one lateral rotation sensor
/// @param forward Forward rotation degrees
/// @param lateral Lateral rotation degrees
/// @param heading_gyro Heading in degrees
void Odom::update_position_one_forward(float current_forward_position, float current_lateral_position, float heading_gyro){
    //Get current positions based on rotation sensors
    current_forward_position = current_forward_position/360.0*(M_PI*forward_right_wheel_diameter);
    current_lateral_position = current_lateral_position/360.0*(M_PI*lateral_wheel_diameter);

    //Get positions since last update
    float old_forward_position = get_forward_right_degrees()/360.0*(M_PI*forward_right_wheel_diameter);
    float old_lateral_position = get_lateral_degrees()/360.0*(M_PI*lateral_wheel_diameter);

    //Get the change based on rotations
    float delta_forward = current_forward_position - old_forward_position;
    float delta_lateral = current_lateral_position-old_lateral_position;

    //Gives answer in radians
    float delta_heading = heading_gyro-get_heading();
    float delta_y = 2.0*((delta_forward/delta_heading)+forward_right_rotation_distance)*sin(delta_heading/2.0);
    float delta_x = 2.0*((delta_lateral/delta_heading)+lateral_rotation_distance)*sin(delta_heading/2.0);

    //Update x and y positions and heading
    set_position((delta_x+get_x_position()), (delta_y+get_y_position()), (delta_heading+get_heading()));
    
    //Update variables to store new location information
    set_forward_right_degrees(current_forward_position);
    set_lateral_degrees(current_lateral_position);
    set_heading(heading_gyro);
}
