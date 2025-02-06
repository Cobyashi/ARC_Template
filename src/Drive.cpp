#include "Drive.h"

/// @brief Constructor
/// @param leftDrive Left side motors of the drive base
/// @param rightDrive Right side motors of the drive base
/// @param gyro The Port where the inertial sensor is 
/// @param wheel_diameter The diameter size of the wheel in inches
/// @param max_voltage The maximum amount of the voltage used in the drivebase (1 - 12)
Drive::Drive(motor_group leftDrive, motor_group rightDrive, int gyro, float wheelDiameter, float wheelRatio, float maxVoltage) : 
leftDrive(leftDrive), 
rightDrive(rightDrive),
gyro(inertial(gyro))
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
float Drive::degToInches(float deg)
{
    return (deg / 360) * pi() * wheelDiameter;
}

/// @brief Gets the current position of the drive base
/// @return Returns the position in inches
float Drive::getCurrentMotorPosition()
{
    float left_position = degToInches(rightDrive.position(degrees));
    float right_position = degToInches(rightDrive.position(degrees));

    return (left_position + right_position) / 2;
}

/// @brief Spins the drive train motors given the values, this function defaults to using volts
/// @param leftUnit Units of movement in volts for the left side of the drive train
/// @param rightUnit Units of movement in volts for the right side of the drive train
void Drive::driveMotors(float leftUnit, float rightUnit)
{
    driveMotors(leftUnit, rightUnit, VOLTS);
}

/// @brief Spins depending on the spin type with the given values
/// @param leftUnit Units of movement for the left side of the drive train
/// @param rightUnit Units of movement for the right side of the drive train
/// @param spinType The type used to spin the motors, can be: VOLTS, PERCENTAGE, DPS, or RPM
void Drive::driveMotors(float leftUnit, float rightUnit, MotorSpinType spinType)
{
    if(spinType == VOLTS)
    {
        leftDrive.spin(forward, leftUnit, volt);
        rightDrive.spin(forward, rightUnit, volt);
    }
    else if(spinType == PERCENTAGE)
    {
        leftDrive.spin(forward, leftUnit, pct);
        rightDrive.spin(forward, rightUnit, pct);
    }
    else if(spinType == DPS)
    {
        leftDrive.spin(forward, leftUnit, dps);
        rightDrive.spin(forward, rightUnit, dps);
    }
    else if(spinType == RPM)
    {
        leftDrive.spin(forward, leftUnit, rpm);
        rightDrive.spin(forward, rightUnit, rpm);
    }
}

/// @brief Brakes the drivetrain 
void Drive::brake()
{
    brake(true, true);
}

/// @brief Brakes the drivetrain
/// @param type The type of brakeType
void Drive::brake(brakeType type)
{
    brake(true, true, type);
}

/// @brief Brakes individual sides of the drive train using hold by default
/// @param left Left side of the drive train brake
/// @param right Right side of the drive train brake
void Drive::brake(bool left, bool right)
{
    brake(left, right, hold);
}

/// @brief Brakes individual sides of the drive train using braketype
/// @param left Left side of the drive train brake
/// @param right Right side of the drive train brake
/// @param type The type of brakeType
void Drive::brake(bool left, bool right, brakeType type)
{
    if(left)
        leftDrive.stop(type);
    if(right)
        rightDrive.stop(type);
}

/// @brief Uses the drivetrain to drive the given distance in inches
/// @param distance The distance to drive in inches
void Drive::driveDistance(float distance)
{
    // Creates PID objects for linear and angular output
    PID linearPID(2, 0.0, 1.5, 1.5, 300);
    PID angularPID(0.4, 0, 1, 1, 300);
    
    // Sets the starting variables for the Position and Heading
    float startPosition = getCurrentMotorPosition();
    float currentPosition = startPosition;
    float startHeading = gyro.heading();

    // Updates the distance to match the current position of the robot
    distance = distance + currentPosition;

    //  Loops while the linear PID has not yet settled
    while(!linearPID.isSettled())
    {
        // Updates the Error for the linear values and the angular values
        float linearError = distance - getCurrentMotorPosition();
        float angularError = degTo180(startHeading - gyro.heading());

        // Sets the linear output and angular output to the output of the error passed through the PID compute functions
        float linearOutput = linearPID.compute(linearError);
        float angularOutput = angularPID.compute(angularError);

        // Clamps the values of the output to fit within the -12 to 12 volt limit of the vex motors
        linearOutput = clamp(linearOutput, -maxVoltage, maxVoltage);
        angularOutput = clamp(angularOutput, -maxVoltage, maxVoltage);

        // Drives motors according to the linear Output and includes the linear Output to keep the robot in a straight path relative to is start heading
        driveMotors(linearOutput - angularOutput, linearOutput + angularOutput);

        wait(10, msec);
    }

    // Stops the motors once PID has settled
    brake();
}

void Drive::turnAngle(){}

void Drive::turnToAngle(){}