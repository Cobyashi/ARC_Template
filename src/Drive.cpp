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

        float output = drive_PID.compute(error, 1);

        Brain.Screen.setCursor(2,1);
        Brain.Screen.print(output);

        output = clamp(output, -max_voltage, max_voltage);

        left_drive.spin(forward, output, volt);
        right_drive.spin(forward, output, volt);


        wait(15, msec);

    }

    brake();
}

void Drive::turn_angle(){}

void Drive::turn_to_angle(){}