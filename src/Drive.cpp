#include "Drive.h"

/* ================= */
/* DRIVE CONSTRUCTOR */
/* ================= */

/// @brief Constructor
/// @param leftDrive Left side motors of the drive base
/// @param rightDrive Right side motors of the drive base
/// @param inertialPort The Port where the inertial sensor is 
/// @param wheelDiameter The diameter size of the wheel in inches
/// @param wheelRatio   
/// @param max_voltage The maximum amount of the voltage used in the drivebase (1 - 12)
Drive::Drive(motor_group leftDrive, motor_group rightDrive, int inertialPORT, float wheelDiameter, float wheelRatio, float maxVoltage, int odomType, float odomWheelDiameter, float odomPod1Offset, float odomPod2Offset ) : 
leftDrive(leftDrive), 
rightDrive(rightDrive),
inertialSensor(inertial(inertialPORT))
{
    this->wheelDiameter = wheelDiameter;
    this->wheelRatio = wheelRatio;
    this->driveMaxVoltage = maxVoltage;
    this->turnMaxVoltage = maxVoltage;
    this->odomType = odomType;

    switch(odomType){
        case NO_ODOM:
            this->chassisOdometry = Odom(wheelDiameter, wheelDiameter, 0, odomPod1Offset, odomPod2Offset, 0);
            break;
        case HORIZONTAL_AND_VERTICAL:
            this->chassisOdometry = Odom(odomWheelDiameter, odomWheelDiameter, odomPod1Offset, odomPod2Offset);
            break;
        case TWO_VERTICAL:
            // Not yet implemented
            break;
        case TWO_AT_45:
            this->chassisOdometry = Odom(odomWheelDiameter, odomPod1Offset, odomPod2Offset);
            break;
    }
}


/* ============ */
/* SET VOLTAGES */
/* ============ */

/// @brief 
/// @param maxVoltage Maximum voltage for the drive base
void Drive::setDriveMaxVoltage(float maxVoltage)
{
    driveMaxVoltage = maxVoltage;
}

/// @brief 
/// @param maxVoltage Maximum voltage for turning
void Drive::setTurnMaxVoltage(float maxVoltage)
{
    turnMaxVoltage = maxVoltage;
}


/* ============= */
/* SET CONSTANTS */
/* ============= */

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


/* =========== */
/* DRIVE TYPES */
/* =========== */

/// @brief Arcade drive control, uses the left joystick for forward/backward and the right joystick for turning
void Drive::arcade()
{
    int leftY = 0;
    int rightX = 0;
    if(Controller1.Axis3.position(percent) >= 0)
        leftY = pow(Controller1.Axis3.position(percent),2)/100;
    else
        leftY = pow(Controller1.Axis3.position(percent),2)/-100;
    
    if(Controller1.Axis1.position(percent) >= 0)
        rightX = pow(Controller1.Axis1.position(percent),2)/100;
    else
        rightX = pow(Controller1.Axis1.position(percent),2)/-100;

    leftDrive.spin(forward, leftY+rightX, percent);
    rightDrive.spin(forward, leftY-rightX, percent);
}

/// @brief Tank drive control, uses the left joystick for the left side of the drive train and the right joystick for the right side of the drive train
void Drive::tank(){
    int leftY = 0;
    int rightX = 0;
    if(Controller1.Axis3.position(percent) >= 0)
        leftY = pow(Controller1.Axis3.position(percent),2)/100;
        //leftY = Controller1.Axis3.position(percent);
    else
        leftY = pow(Controller1.Axis3.position(percent),2)/-100;
        //leftY = Controller1.Axis3.position(percent);
    
    if(Controller1.Axis2.position(percent) >= 0)
        rightX = pow(Controller1.Axis2.position(percent),2)/100;
        //rightX = Controller1.Axis2.position(percent);
    else
        rightX = pow(Controller1.Axis2.position(percent),2)/-100;
        //rightX = Controller1.Axis2.position(percent);

    leftDrive.spin(forward, leftY, percent);
    rightDrive.spin(forward, rightX, percent);
}


/* ======== */
/* STOPPING */
/* ======== */

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

/* ======= */
/* TURNING */
/* ======= */

/// @brief Turns the robot a set amount of degrees
/// @param turnDegrees A number in degrees the robot should rotate
void Drive::turn(float turnDegrees){
    turnToAngle(turnDegrees + inertial1.heading());
}

/// @brief Turns the robot a set amount of degrees with a max voltage
/// @param turnDegrees A number in degrees the robot should rotate
/// @param maxVoltage The max amount of voltage used to turn
void Drive::turn(float turnDegrees, float maxVoltage){
    turnToAngle(turnDegrees + inertial1.heading(), maxVoltage);
}

/// @brief Turns to an absolute specific angle
/// @param angle The angle to turn to in degrees (0 - 360)
void Drive::turnToAngle(float angle)
{
    turnToAngle(angle, turnMaxVoltage);
}

/// @brief Turns to an absolute specific angle with a max voltage
/// @param angle The angle to turn to in degrees (0 - 360)
/// @param maxVoltage The max amount of voltage used to turn
void Drive::turnToAngle(float angle, float maxVoltage)
{
    updatePosition();
    angle = inTermsOfNegative180To180(angle);
    PID turnPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);
    do
    {
        float error = inTermsOfNegative180To180(inertial1.heading()-angle);
        float output = turnPID.compute(error);

        //Minimum output threshold for turning
        if(fabs(output) < 0.85)
            if(output < 0)
                output = -1.4;
            else
                output = 1.4;
        else if (fabs(output) < 1.5)
             if(output < 0)
                output = -3.4;
            else
                output = 3.4;
        else if (fabs(output) < 5)
            if(output < 0)
                output = -5.4;
            else
                output = 5.4;
        else
            output = clamp(output, -maxVoltage, maxVoltage);

        driveMotors(-output, output);
        task::sleep(10);
    }while(!turnPID.isSettled());
    brake();
    updatePosition();
}

/// @brief Turns to an absolute specific angle with max voltage and end time
/// @param angle The angle to turn to in degrees (0-360)
/// @param maxVoltage The max amount of voltage used to turn
/// @param endTime The maximum time allowed to turn
void Drive::turnToAngle(float angle, float maxVoltage, float endTime){
    updatePosition();
    angle = inTermsOfNegative180To180(angle);
    PID turnPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, endTime);
    do
    {
        float error = inTermsOfNegative180To180(inertial1.heading()-angle);
        float output = turnPID.compute(error);

        //Minimum output threshold for turning
        if(fabs(output) < 0.85)
            if(output < 0)
                output = -1.4;
            else
                output = 1.4;
        else if (fabs(output) < 1.5)
             if(output < 0)
                output = -3.4;
            else
                output = 3.4;
        else if (fabs(output) < 5)
            if(output < 0)
                output = -5.4;
            else
                output = 5.4;
        else
            output = clamp(output, -maxVoltage, maxVoltage);

        driveMotors(-output, output);
        task::sleep(10);
    }while(!turnPID.isSettled());
    brake();
    updatePosition();
}

/// @brief 
/// @param desX Target X position
/// @param desY Target Y position
void Drive::turnToPosition(float desX, float desY){
    updatePosition();
    float deltaX = desX-chassisOdometry.getXPosition();
    float deltaY = desY-chassisOdometry.getYPosition();
    float angle = atan2(deltaX, deltaY) * (180.0/M_PI);
    turnToAngle(angle);
    updatePosition();
}


/* ================ */
/* STRAIGHT DRIVING */
/* ================ */

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
    float startHeading = inertial1.heading();

    // Updates the distance to match the current position of the robot
    distance += startPosition;

    //  Loops while the linear PID has not yet settled
    while(!linearPID.isSettled())
    {
        updatePosition();
        // Updates the Error for the linear values and the angular values
        float linearError = distance - getCurrentMotorPosition();
        float angularError = degTo180(startHeading - inertial1.heading());

        // Sets the linear output and angular output to the output of the error passed through the PID compute functions
        float linearOutput = linearPID.compute(linearError);
        float angularOutput = angularPID.compute(angularError);

        // Clamps the values of the output to fit within the -12 to 12 volt limit of the vex motors
        linearOutput = clamp(linearOutput, -maxVoltage, maxVoltage);
        angularOutput = clamp(angularOutput, -maxVoltage, maxVoltage);

        // Drives motors according to the linear Output and includes the linear Output to keep the robot in a straight path relative to is start heading
        driveMotors(linearOutput + angularOutput, linearOutput - angularOutput);
        wait(10, msec);
    }

    
    // Stops the motors once PID has settled
    //brake();
    updatePosition();
}

/// @brief Drive a certain distance using the odometry wheels
/// @param distance How far the robot (in inches) needs to drive
void Drive::driveDistanceWithOdom(float distance){
    //Creates PID objects for linear and angular output
    PID linearPID(driveKp, driveKi, driveKd, driveSettleError, driveTimeToSettle, driveEndTime);
    PID angularPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);

    updatePosition();

    //Starting pose (field coordinates & heading)
    float startHeadingDeg = inertial1.heading();
    float startHeadingRad = degToRad(startHeadingDeg);

    //Unit forward direction based on starting heading
    float dirX = sin(startHeadingRad);
    float dirY = cos(startHeadingRad);

    //Starting position in field coordinates
    float startX = chassisOdometry.getXPosition();
    float startY = chassisOdometry.getYPosition();

    //Target point in field coordinates (distance along starting heading)
    float targetX = startX + dirX * distance;
    float targetY = startY + dirY * distance;

    while (!linearPID.isSettled())
    {
        updatePosition();

        //Odom-based pose
        float curX = chassisOdometry.getXPosition();
        float curY = chassisOdometry.getYPosition();

        float dx = targetX - curX;
        float dy = targetY - curY;

        //Signed error along the original heading:
        float linearError  = dx * dirX + dy * dirY;
        float angularError = degTo180(startHeadingDeg - inertial1.heading());

        float linearOutput  = linearPID.compute(linearError);
        float angularOutput = angularPID.compute(angularError);

        linearOutput  = clamp(linearOutput,  -driveMaxVoltage, driveMaxVoltage);
        angularOutput = clamp(angularOutput, -driveMaxVoltage, driveMaxVoltage);

        driveMotors(linearOutput + angularOutput, linearOutput - angularOutput);

        updatePosition();
        wait(10, msec);
    }

    brake();
    driveMotors(0, 0);
    updatePosition();
}

/// @brief Drive a certain distance using the odometry wheels with a time limit
/// @param distance How far the robot (in inches) needs to drive
/// @param timeLimit The maximum time allowed to drive
void Drive::driveDistanceWithOdom(float distance, float timeLimit){
    // Creates PID objects for linear and angular output
    PID linearPID(driveKp, driveKi, driveKd, driveSettleError, driveTimeToSettle, timeLimit);
    PID angularPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);

    updatePosition();

    // --- Starting pose (field coordinates & heading) ---
    float startHeadingDeg = inertial1.heading();
    float startHeadingRad = degToRad(startHeadingDeg);

    // Unit forward direction based on starting heading
    float dirX = sin(startHeadingRad);
    float dirY = cos(startHeadingRad);

    // Starting position in field coordinates
    float startX = chassisOdometry.getXPosition();
    float startY = chassisOdometry.getYPosition();

    // Target point in field coordinates (distance along starting heading)
    float targetX = startX + dirX * distance;
    float targetY = startY + dirY * distance;

    while (!linearPID.isSettled())
    {
        updatePosition();

        // Odom-based pose
        float curX = chassisOdometry.getXPosition();
        float curY = chassisOdometry.getYPosition();

        float dx = targetX - curX;
        float dy = targetY - curY;

        // Signed error along the original heading:
        float linearError  = dx * dirX + dy * dirY;
        float angularError = degTo180(startHeadingDeg - inertial1.heading());

        float linearOutput  = linearPID.compute(linearError);
        float angularOutput = angularPID.compute(angularError);

        linearOutput  = clamp(linearOutput,  -driveMaxVoltage, driveMaxVoltage);
        angularOutput = clamp(angularOutput, -driveMaxVoltage, driveMaxVoltage);

        driveMotors(linearOutput + angularOutput, linearOutput - angularOutput);

        updatePosition();
        wait(10, msec);
    }

    // Make absolutely sure we stop
    brake();
    driveMotors(0, 0);
    updatePosition();
}

/// @brief Drive a certain distance using the odometry wheels with a time limit and max voltage
/// @param distance  How far the robot (in inches) needs to drive
/// @param timeLimit The maximum time allowed to drive
/// @param maxVoltage The maximum voltage the robot can run at
void Drive::driveDistanceWithOdom(float distance, float timeLimit, float maxVoltage){
    // Creates PID objects for linear and angular output
    PID linearPID(driveKp, driveKi, driveKd, driveSettleError, driveTimeToSettle, timeLimit);
    PID angularPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);

    updatePosition();

    // --- Starting pose (field coordinates & heading) ---
    float startHeadingDeg = inertial1.heading();
    float startHeadingRad = degToRad(startHeadingDeg);

    // Unit forward direction based on starting heading
    float dirX = sin(startHeadingRad);
    float dirY = cos(startHeadingRad);

    // Starting position in field coordinates
    float startX = chassisOdometry.getXPosition();
    float startY = chassisOdometry.getYPosition();

    // Target point in field coordinates (distance along starting heading)
    float targetX = startX + dirX * distance;
    float targetY = startY + dirY * distance;

    while (!linearPID.isSettled())
    {
        updatePosition();

        // Odom-based pose
        float curX = chassisOdometry.getXPosition();
        float curY = chassisOdometry.getYPosition();

        float dx = targetX - curX;
        float dy = targetY - curY;

        // Signed error along the original heading:
        float linearError  = dx * dirX + dy * dirY;
        float angularError = degTo180(startHeadingDeg - inertial1.heading());

        float linearOutput  = linearPID.compute(linearError);
        float angularOutput = angularPID.compute(angularError);

        linearOutput  = clamp(linearOutput,  -maxVoltage, maxVoltage);
        angularOutput = clamp(angularOutput, -maxVoltage, maxVoltage);

        driveMotors(linearOutput + angularOutput, linearOutput - angularOutput);

        updatePosition();
        wait(10, msec);
    }

    // Make absolutely sure we stop
    brake();
    driveMotors(0, 0);
    updatePosition();
}

/// @brief Drive a certain distance using the odometry wheels with a time limit, max voltage, settle time, and settle error
/// @param distance How far the robot (in inches) needs to drive
/// @param timeLimit The maximum time allowed to drive
/// @param maxVoltage The maximum voltage the robot can run at
/// @param settleTime How long the robot is allowed to settle
/// @param settleError How big the settle error is to allow the robot to settle
void Drive::driveDistanceWithOdom(float distance, float timeLimit, float maxVoltage, float settleTime, float settleError){
    // Creates PID objects for linear and angular output
    PID linearPID(driveKp, driveKi, driveKd, settleError, settleTime, timeLimit);
    PID angularPID(turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime);

    updatePosition();

    // --- Starting pose (field coordinates & heading) ---
    float startHeadingDeg = inertial1.heading();
    float startHeadingRad = degToRad(startHeadingDeg);

    // Unit forward direction based on starting heading
    float dirX = sin(startHeadingRad);
    float dirY = cos(startHeadingRad);

    // Starting position in field coordinates
    float startX = chassisOdometry.getXPosition();
    float startY = chassisOdometry.getYPosition();

    // Target point in field coordinates (distance along starting heading)
    float targetX = startX + dirX * distance;
    float targetY = startY + dirY * distance;

    while (!linearPID.isSettled())
    {
        updatePosition();

        // Odom-based pose
        float curX = chassisOdometry.getXPosition();
        float curY = chassisOdometry.getYPosition();

        float dx = targetX - curX;
        float dy = targetY - curY;

        // Signed error along the original heading:
        float linearError  = dx * dirX + dy * dirY;
        float angularError = degTo180(startHeadingDeg - inertial1.heading());

        float linearOutput  = linearPID.compute(linearError);
        float angularOutput = angularPID.compute(angularError);

        linearOutput  = clamp(linearOutput,  -maxVoltage, maxVoltage);
        angularOutput = clamp(angularOutput, -maxVoltage, maxVoltage);

        driveMotors(linearOutput + angularOutput, linearOutput - angularOutput);

        updatePosition();
        wait(10, msec);
    }

    // Make absolutely sure we stop
    brake();
    driveMotors(0, 0);
    updatePosition();
}


/* ============= */
/* OTHER DRIVING */
/* ============= */

/// @brief Turns sharply to a specific location and moves to it
/// @param desX Desired X position
/// @param desY Desired Y position
void Drive::moveToPosition(float desX, float desY){
    // Calculate the angle to turn to
    float deltaX = desX - chassisOdometry.getXPosition();
    float deltaY = desY - chassisOdometry.getYPosition();

    // Turn to the target angle
    turnToPosition(desX, desY);

    // Calculate the distance to the target position
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    // Drive the calculated distance
    driveDistanceWithOdom(distance);
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



/* =========== */
/* POSITIONING */
/* =========== */

/// @brief Gets the current position of the drive base
/// @return Returns the position in inches
float Drive::getCurrentMotorPosition()
{
    float leftPosition = degToInches(leftDrive.position(degrees), wheelDiameter);
    float rightPosition = degToInches(rightDrive.position(degrees), wheelDiameter);

    return (leftPosition + rightPosition) / 2;
}

/// @brief Returns what odom type the robot is using
/// @return Returns odom type
int Drive::getOdomType() const {return odomType;}

/// @brief Sets brakes to coast and displays position location to the robot brain
void Drive::moveable(){
    //updates odom and printx x and y position
    while (true) {
        brake(coast);
        updatePosition();
        float x = chassisOdometry.getXPosition();
        float y = chassisOdometry.getYPosition();
        float heading = chassisOdometry.getHeading();
        // float x = rotation1.position(degrees);
        // float y = rotation2.position(degrees);
        // std::cout << "X: " << x << ", Y: " << y << std::endl;
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("X: ");
        Brain.Screen.print(x);
        Brain.Screen.newLine();
        Brain.Screen.print("Y: ");
        Brain.Screen.print(y);
        Brain.Screen.print(heading);
        //std::cout << "\nHeading: " << chassisOdometry.getHeading();
        //std::cout << "\nx: " << x;
        //std::cout << "\ny: " << y;
        wait(50, msec); 
    }
}

/// @brief Updates the position of the robot
void Drive::updatePosition(){
    switch(odomType){
        float left, right, heading;
        case NO_ODOM:
            left = leftDrive.position(degrees);
            right = rightDrive.position(degrees);
            heading = inertial1.heading();
            chassisOdometry.updatePositionTwoForward(right, left, heading);
            break;
        case HORIZONTAL_AND_VERTICAL:
            left = rotation1.position(degrees);
            right = rotation2.position(degrees);
            heading = inertial1.heading();
            chassisOdometry.updatePositionOneForward(left, right, heading);
            break;
        case TWO_VERTICAL:
            left = rotation1.position(degrees);
            right = rotation2.position(degrees);
            heading = inertial1.heading();
            chassisOdometry.updatePositionTwoForward(right, left, heading);
            break;
        case TWO_AT_45:
            left = rotation1.position(degrees);
            right = rotation2.position(degrees);
            heading = inertial1.heading();
            chassisOdometry.updatePositionTwoAt45(left, right, heading);
            break;
    }
}

/// @brief Sets the current location of the robot
/// @param x Current X location
/// @param y Current Y location
/// @param heading Current heading
void Drive::setPosition(float x, float y, float heading){
    // Reset odom pose
    chassisOdometry.setPosition(x, y, heading);
    inertial1.setHeading(heading, degrees);

    // Sync odom encoder baselines with the actual sensors
    switch (odomType) {
        case NO_ODOM:
            // Using drive motors as odom
            chassisOdometry.setForwardRightDegrees(rightDrive.position(degrees));
            chassisOdometry.setForwardLeftDegrees(leftDrive.position(degrees));
            chassisOdometry.setLateralDegrees(0);
            break;

        case HORIZONTAL_AND_VERTICAL:
            // Using rotation1 and rotation2
            chassisOdometry.setForwardLeftDegrees(rotation1.position(degrees));
            chassisOdometry.setLateralDegrees(rotation2.position(degrees));
            // If you have a second forward sensor, set it here too
            break;

        case TWO_AT_45:
            // Whatever sensors you're using in this mode
            // Example (if both are vertical tracking wheels):
            chassisOdometry.setForwardRightDegrees(rotation1.position(degrees));
            chassisOdometry.setForwardLeftDegrees(rotation2.position(degrees));
            chassisOdometry.setLateralDegrees(0);
            break;

        default:
            break;
    }
}