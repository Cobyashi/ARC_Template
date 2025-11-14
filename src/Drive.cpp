#include "Drive.h"

/// @brief Constructor
/// @param leftDrive Left side motors of the drive base
/// @param rightDrive Right side motors of the drive base
/// @param inertialPort The Port where the inertial sensor is 
/// @param wheelDiameter The diameter size of the wheel in inches
/// @param wheelRatio   
/// @param max_voltage The maximum amount of the voltage used in the drivebase (1 - 12)
Drive::Drive(motor_group leftDrive, motor_group rightDrive, int inertialPORT, float wheelDiameter, float wheelRatio, float maxVoltage, int odomType) : 
leftDrive(leftDrive), 
rightDrive(rightDrive),
inertialSensor(inertial(inertialPORT))
{
    this->wheelDiameter = wheelDiameter;
    this->wheelRatio = wheelRatio;
    this->driveMaxVoltage = maxVoltage;
    this->turnMaxVoltage = maxVoltage;
    this->odomType = odomType;

    this->chassisOdometry = Odom(2, 1.5, 1.5);

    // switch(odomType){
    //     case NO_ODOM:
    //         // this->chassisOdometry = Odom(leftDriveWheelDiameter, rightDriveWheelDiameter, 0, leftDriveDistFromCenter, rightDriveDistFromCenter, 0);
    //         break;
    //     case HORIZONTAL_AND_VERTICAL:
    //         // this->chassisOdometry = Odom(forwardWheelDiameter, lateralWheelDiameter, forwardRotationDistance, lateralRotationDistance);
    //         break;
    //     case TWO_VERTICAL:
    //         // Not yet implemented
    //         break;
    //     case TWO_AT_45:
    //         this->chassisOdometry = Odom(wheelDiameter45, leftRotationDistance, rightRotationDistance);
    //         break;
    // }
}

void Drive::setDriveMaxVoltage(float maxVoltage)
{
    driveMaxVoltage = maxVoltage;
}

void Drive::setTurnMaxVoltage(float maxVoltage)
{
    turnMaxVoltage = maxVoltage;
}

/// @brief Sets the PID constants for the Drive distance 
/// @param Kp Proportion Constant
/// @param Ki Integral Constant
/// @param Kd Derivative Constant
/// @param settleError The Error reached when settle should start
/// @param timeToSettle The time in milliseconds to settle
/// @param endTime The total run time in milliseconds
void Drive::setDriveConstants(float Kp, float Ki, float Kd, float settleError, float timeToSettle, float endTime)
{
    driveKp = Kp;
    driveKi = Ki;
    driveKd = Kd;
    driveSettleError = settleError;
    driveTimeToSettle = timeToSettle;
    driveEndTime = endTime;
}

/// @brief Sets the PID constants for the turn angle
/// @param Kp Proportion Constant
/// @param Ki Integral Constant
/// @param Kd Derivative Constant
/// @param settleError The Error reached when settle should start
/// @param timeToSettle The time in milliseconds to settle
/// @param endTime The total run time in milliseconds
void Drive::setTurnConstants(float Kp, float Ki, float Kd, float settleError, float timeToSettle, float endTime)
{
    turnKp = Kp;
    turnKi = Ki;
    turnKd = Kd;
    turnSettleError = settleError;
    turnTimeToSettle = timeToSettle;
    turnEndTime = endTime;
}


void Drive::arcade()
{
    int leftY = Controller1.Axis3.position(percent);
    int rightX = Controller1.Axis1.position(percent);
    leftDrive.spin(forward, leftY-rightX, percent);
    rightDrive.spin(forward, leftY+rightX, percent);
}


void Drive::tank(){
    int leftY = Controller1.Axis3.position(percent);
    int rightY = Controller1.Axis2.position(percent);
    leftDrive.spin(forward, leftY, percent);
    rightDrive.spin(forward, rightY, percent);
}

/// @brief Gets the current position of the drive base
/// @return Returns the position in inches
float Drive::getCurrentMotorPosition()
{
    float leftPosition = degToInches(leftDrive.position(degrees), wheelDiameter);
    float rightPosition = degToInches(rightDrive.position(degrees), wheelDiameter);

    return (leftPosition + rightPosition) / 2;
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

/// @brief Brakes individual sides of the drive train using brake type
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
    driveDistance(distance, driveMaxVoltage);
}

/// @brief Uses the drivetrain to drive the given distance in inches
/// @param distance The distance to drive in inches
/// @param maxVoltage The max amount of voltage used to drive
void Drive::driveDistance(float distance, float maxVoltage)
{
    // Creates PID objects for linear and angular output
    //float Kp, float Ki, float Kd, float settleError, float timeToSettle, float endTime
    PID linearPID(driveKp, driveKi, driveKd, driveSettleError, driveTimeToSettle, driveEndTime);
    PID angularPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);
    
    updatePosition();
    // Sets the starting variables for the Position and Heading
    float startPosition = getCurrentMotorPosition();
    float startHeading = gyro1.heading();

    // Updates the distance to match the current position of the robot
    distance += startPosition;

    //  Loops while the linear PID has not yet settled
    while(!linearPID.isSettled())
    {
        updatePosition();
        // Updates the Error for the linear values and the angular values
        float linearError = distance - getCurrentMotorPosition();
        float angularError = degTo180(startHeading - gyro1.heading());

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
    //brake();
    updatePosition();
}

/// @brief Turns the robot a set amount of degrees
/// @param turnDegrees A number in degrees the robot should rotate
void Drive::turn(float turnDegrees){
    turnToAngle(turnDegrees + gyro1.heading());
}

/// @brief Turns the robot a set amount of degrees
/// @param turnDegrees A number in degrees the robot should rotate
/// @param maxVoltage The max amount of voltage used to turn
void Drive::turn(float turnDegrees, float maxVoltage){
    turnToAngle(turnDegrees + gyro1.heading(), maxVoltage);
}

/// @brief Turns to an absolute specific angle
/// @param angle The angle to turn to in degrees (0 - 360)
void Drive::turnToAngle(float angle)
{
    turnToAngle(angle, turnMaxVoltage);
}

/// @brief Turns to an absolute specific angle
/// @param angle The angle to turn to in degrees (0 - 360)
/// @param maxVoltage The max amount of voltage used to turn
void Drive::turnToAngle(float angle, float maxVoltage)
{
    updatePosition();
    angle = inTermsOfNegative180To180(angle);
    PID turnPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);
    do
    {
        float error = inTermsOfNegative180To180(gyro1.heading()-angle);
        float output = turnPID.compute(error);
        output = clamp(output, -maxVoltage, maxVoltage);
        driveMotors(output, -output);
        task::sleep(10);
    }while(!turnPID.isSettled());
    driveMotors(0,0);
    updatePosition();
}

/// @brief Turns sharply to a specific location and moves to it
/// @param desX Desired X position
/// @param desY Desired Y position
void Drive::moveToPosition(float desX, float desY){
    // Creates PID objects for linear and angular output
    //float Kp, float Ki, float Kd, float settleError, float timeToSettle, float endTime
    PID linearPID(driveKp, driveKi, driveKd, driveSettleError, driveTimeToSettle, driveEndTime);
    PID angularPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);

    turnToPosition(desX, desY);
    
    updatePosition();
    // Sets the starting variables for the Position and Heading
    float startX = chassisOdometry.getXPosition();
    float startY = chassisOdometry.getYPosition();
    float startHeading = gyro1.heading();

    //  Loops while the linear PID has not yet settled
    while(!linearPID.isSettled())
    {
        updatePosition();
        // Updates the Error for the linear values and the angular values
        float linearError = sqrt(pow(desX-chassisOdometry.getXPosition(), 2.0) + pow(desY-chassisOdometry.getYPosition(), 2.0));
        float angularError = degTo180(startHeading - gyro1.heading());

        // Sets the linear output and angular output to the output of the error passed through the PID compute functions
        float linearOutput = linearPID.compute(linearError);
        float angularOutput = angularPID.compute(angularError);

        // Clamps the values of the output to fit within the -12 to 12 volt limit of the vex motors
        linearOutput = clamp(linearOutput, -driveMaxVoltage, driveMaxVoltage);
        angularOutput = clamp(angularOutput, -driveMaxVoltage, driveMaxVoltage);

        // Drives motors according to the linear Output and includes the linear Output to keep the robot in a straight path relative to is start heading
        driveMotors(linearOutput - angularOutput, linearOutput + angularOutput);

        wait(10, msec);
    }
    // Stops the motors once PID has settled
    //brake();
    updatePosition();
}

void Drive::driveDistanceWithOdom(float distance){
    // Creates PID objects for linear and angular output
    //float Kp, float Ki, float Kd, float settleError, float timeToSettle, float endTime
    PID linearPID(driveKp, driveKi, driveKd, driveSettleError, driveTimeToSettle, driveEndTime);
    PID angularPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);
    
    updatePosition();
    // Sets the starting variables for the Position and Heading
    float xToGo = cos(degToRad(gyro1.heading()))* distance;
    float yToGo = sin(degToRad(gyro1.heading()))* distance;
    float startHeading = gyro1.heading();

    float targetX = chassisOdometry.getXPosition() + xToGo;
    float targetY = chassisOdometry.getYPosition() + yToGo;

    //  Loops while the linear PID has not yet settled
    while(!linearPID.isSettled())
    {
        updatePosition();
        // Updates the Error for the linear values and the angular values
        float linearError = sqrt(pow(targetX - chassisOdometry.getXPosition(), 2.0) + pow(targetY - chassisOdometry.getYPosition(), 2.0));
        float angularError = degTo180(startHeading - gyro1.heading());

        xToGo = cos(degToRad(gyro1.heading())) * linearError;
        yToGo = sin(degToRad(gyro1.heading())) * linearError;

        // Sets the linear output and angular output to the output of the error passed through the PID compute functions
        float linearOutput = linearPID.compute(linearError);
        float angularOutput = angularPID.compute(angularError);

        // Clamps the values of the output to fit within the -12 to 12 volt limit of the vex motors
        linearOutput = clamp(linearOutput, -driveMaxVoltage, driveMaxVoltage);
        angularOutput = clamp(angularOutput, -driveMaxVoltage, driveMaxVoltage);

        // Drives motors according to the linear Output and includes the linear Output to keep the robot in a straight path relative to is start heading
        driveMotors(linearOutput - angularOutput, linearOutput + angularOutput);

        wait(10, msec);
    }
    // Stops the motors once PID has settled
    //brake();
    updatePosition();
}

void Drive::turnToPosition(float desX, float desY){
    updatePosition();
    float deltaX = chassisOdometry.getXPosition()-desX;
    float deltaY = chassisOdometry.getYPosition()-desY;
    float angle = atan(deltaX/deltaY) * (180.0/M_PI);
    turnToAngle(angle);
    updatePosition();
}

/// @brief Turns along a set curve
/// @param curX The current X position of the robot
/// @param curY The current Y position of the robot
/// @param midX The X position of the middle point of the curve
/// @param midY The Y position of the middle point of the curve
/// @param desX The desired ending X position
/// @param desY The desired ending Y position
/// @param numPts The number of points along the curve to go to
void Drive::bezierTurn(float curX, float curY, float midX, float midY, float desX, float desY, int numPts){
    float* pts = new float[numPts+1];
    float nextX, nextY;
    
    //Populate the t-values (0-1)
    pts[numPts] = 1;
    for(int i=0;i<numPts;i++){
        pts[i] = (1.0/static_cast<float>(numPts+1)) * i;
    }

    //Calculate X and Y values along the curve based on pts[i] and move to that position
    for(int i=0;i<numPts+1;i++){
        nextX = (pow(1-pts[i], 2)*curX) + (2*(1-pts[i])*pts[i]*midX) + (pow(pts[i], 2)*desX);
        nextY = (pow(1-pts[i], 2)*curY) + (2*(1-pts[i])*pts[i]*midY) + (pow(pts[i], 2)*desY);  
        moveToPosition(nextX, nextY);
    }

    delete [] pts;

}

void Drive::updatePosition(){
    switch(odomType){
        float left, right, heading;
        case NO_ODOM:
            left = leftDrive.position(degrees);
            right = rightDrive.position(degrees);
            heading = gyro1.heading();
            chassisOdometry.updatePositionTwoForward(right, left, heading);
            break;
        case HORIZONTAL_AND_VERTICAL:
            left = forwardR.position(degrees);
            right = lateral.position(degrees);
            heading = gyro1.heading();
            chassisOdometry.updatePositionOneForward(left, right, heading);
            break;
        case TWO_VERTICAL:
            left = forwardR.position(degrees);
            right = lateral.position(degrees);
            heading = gyro1.heading();
            chassisOdometry.updatePositionTwoForward(right, left, heading);
            break;
        case TWO_AT_45:
            left = forwardR.position(degrees);
            right = lateral.position(degrees);
            heading = gyro1.heading();
            chassisOdometry.updatePositionTwoAt45(left, right, heading);
            break;
    }
}

void Drive::setPosition(float x, float y, float heading){
    chassisOdometry.setPosition(x, y, heading);
}
