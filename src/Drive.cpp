#include "Drive.h"

/// @brief Constructor
/// @param left_drive Left side motors of the drive base
/// @param right_drive Right side motors of the drive base
/// @param wheel_diameter The diameter size of the wheel in inches
/// @param max_voltage The maximum amount of the voltage used in the drivebase (1 - 12)
Drive::Drive(motor_group left_drive, motor_group right_drive, float wheel_diameter, float max_voltage) : 
left_drive(left_drive), 
right_drive(right_drive), 
wheel_diameter(wheel_diameter), 
max_voltage(max_voltage)
{}


void Drive::arcade()
{
    
}


void Drive::tank(){}

/// @brief Changes a the degree of a wheel rotation to inches driven
/// @param deg The degree of rotation of a wheel
/// @return The inches driven
float Drive::deg_to_inches(float deg)
{
    return (deg / 360) * pi() * wheel_diameter;
}

/// @brief Brakes the drivetrain 
void Drive::brake()
{
    brake(true, true);
}

/// @brief Brakes individual sides of the drive train
/// @param left Left side of the drive train brake
/// @param right Right side of the drive train brake
void Drive::brake(bool left, bool right)
{
    if(left)
        left_drive.stop();
    if(right)
        right_drive.stop();
}

/// @brief Uses the drivetrain to drive the given distance in inches
/// @param distance The distance to drive in inches
void Drive::drive_distance(float distance)
{
    PID drive_PID(1.25, 0.01, .35, 100);
    
    float start_left_position = deg_to_inches(left_drive.position(degrees));
    float start_right_position = deg_to_inches(right_drive.position(degrees));

    float current_left_position = deg_to_inches(left_drive.position(degrees));
    float current_right_position = deg_to_inches(right_drive.position(degrees));

    float average_distance = (current_left_position + current_right_position) / 2;

    distance = distance + average_distance;

    //  While loop should end when PID is complete
    while(!drive_PID.isSettled())
    {
        current_left_position =  deg_to_inches(left_drive.position(degrees)) - start_left_position;
        current_right_position = deg_to_inches(right_drive.position(degrees)) - start_right_position;

        average_distance = (current_left_position + current_right_position) / 2;
        float error = distance - average_distance;

        Brain.Screen.clearScreen();

        float output = drive_PID.compute(error);

        Brain.Screen.setCursor(1,1);
        Brain.Screen.print(error);
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print(output);

        output = clamp(output, -max_voltage, max_voltage);

        left_drive.spin(forward, output, volt);
        right_drive.spin(forward, output, volt);


        wait(15, msec);

    }

    brake();
}

/// @brief Turns the robot a set amount of degrees using odometry
/// @param turnDegrees The number of degrees the robot turns (0-359)
void Drive::turn(float turnDegrees){
    
    Odom sensors(forward1, forward2, lateral, 3.25);
    PID turn_PID(1.00, 0.00, 0.00, 100);

    float output;
    float angle;
    int numRotations;

    while(true){
        
        angle = lateral.position(degrees);
        numRotations = lateral.position(rev);
        angle = angle - (numRotations*360);

        output = turn_PID.compute(angle);
        output = clamp(output, -max_voltage, max_voltage);

        if(fabs(angle/4.0) >= (fabs(turnDegrees))){
            break;
        }
            
        if(turnDegrees > 0){
            right_drive.spin(forward, output, volt);
            left_drive.spin(reverse, output, volt);
        }
        else{
            left_drive.spin(forward, output, volt);
            right_drive.spin(reverse, output, volt);
        }

        task::sleep(20);

    }
}


/// @brief Drives the robot to a set position on the field
/// @param newY Desired ending y-position
/// @param newX Desired ending x-position
/// @param facingDir Desired ending facing direction
void Drive::moveTurn(float newY, float newX, float facingDir){

    Odom sensors(forward1, forward2, lateral, 3.25);
    
    float curX = sensors.get_current_X_rotation(lateral);
    float curY = sensors.get_current_Y_rotation(forward1, forward2);

    float distX = newX - curX;
    float distY = newY - curY;
    
    float driveDist = sqrt(pow(distY,2.0) + pow(distX,2.0));
    float driveAngle = (atan(distX/distY))*180/M_PI;

    //Turn initial angle
    turn(driveAngle);
    //Drive hypotenuse
    drive_distance(driveDist);
    //Turn to ending facing
    turn((-1.0*driveAngle) + facingDir);


}

void Drive::move_to_position(){
    
}