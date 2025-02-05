#include "Drive.h"

/// @brief Constructor
/// @param left_drive Left side motors of the drive base
/// @param right_drive Right side motors of the drive base
/// @param wheel_diameter The diameter size of the wheel in inches
/// @param max_voltage The maximum amount of the voltage used in the drivebase (1 - 12)
Drive::Drive(motor_group left_drive, motor_group right_drive, float wheelDiameter, float wheelRatio, float maxVoltage) : 
left_drive(left_drive), 
right_drive(right_drive)
{
    this->wheelDiameter = wheelDiameter;
    this->wheelRatio = wheelRatio;
    this->maxVoltage = maxVoltage;
}


void Drive::arcade()
{
    
}


void Drive::tank(){}

/// @brief Changes a the degree of a wheel rotation to inches driven
/// @param deg The degree of rotation of a wheel
/// @return The inches driven
float Drive::deg_to_inches(float deg)
{
    return (deg / 360) * pi() * wheelDiameter;
}

/// @brief Gets the current position of the drive base
/// @return Returns the position in inches
float Drive::getCurrentPosition()
{
    float left_position = deg_to_inches(right_drive.position(degrees));
    float right_position = deg_to_inches(right_drive.position(degrees));

    return (left_position + right_position) / 2;
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
        left_drive.stop(hold);
    if(right)
        right_drive.stop(hold);
}

/// @brief Uses the drivetrain to drive the given distance in inches
/// @param distance The distance to drive in inches
void Drive::drive_distance(float distance)
{
    PID drivePID(2, 0.0, 1.5, 1.5, 300);
    PID angularPID(0.4, 0, 1, 1, 300);
    
    float startPosition = getCurrentPosition();
    float currentPosition = startPosition;

    distance = distance + currentPosition;

    //  While loop should end when PID is complete
    while(!drivePID.isSettled())
    {
        currentPosition = getCurrentPosition();
        float error = distance - currentPosition;

            Brain.Screen.clearScreen();

        float output = drivePID.compute(error);

            Brain.Screen.setCursor(1,1);
            Brain.Screen.print("ERROR: ");
            Brain.Screen.print(error);
            Brain.Screen.setCursor(2,1);
            Brain.Screen.print("Output: ");
            Brain.Screen.print(output);

        output = clamp(output, -maxVoltage, maxVoltage);

        left_drive.spin(forward, output, volt);
        right_drive.spin(forward, output, volt);

        wait(10, msec);
    }

    brake();
}

void Drive::turn_angle(){}

void Drive::turn_to_angle(){}