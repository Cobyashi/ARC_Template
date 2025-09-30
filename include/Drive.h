#pragma once

#include "vex.h"
#include "util.h"

using namespace vex;

enum MotorSpinType {VOLTS, PERCENTAGE, DPS, RPM};

class Drive
{
    private:

    motor_group leftDrive, rightDrive;
    inertial inertialSensor;

    float maxVoltage;
    float wheelRatio, wheelDiameter;

    float driveKp, driveKi, driveKd, driveSettleError, driveTimeToSettle, driveEndTime;
    float turnKp, turnKi, turnKd, turnSettleError, turnTimeToSettle, turnEndTime;

    public:

    float predictedAngle;

    Drive(motor_group leftDrive, motor_group rightDrive, int inertialPORT, float wheelDiameter, float wheelRatio, float maxVoltage);

    void arcade();
    void tank();

    float getCurrentMotorPosition();

    void driveMotors(float leftVolts, float rightVolts);
    void driveMotors(float leftVolts, float rightVolts, MotorSpinType spinType);

    void brake();
    void brake(brakeType);
    void brake(bool left, bool right);
    void brake(bool left, bool right, brakeType);

    void driveDistance(float distance);

    void turn(float turnDegrees);
    void turnDegrees(float degrees);
    void turnToAngle(float desired_heading, float current_heading);
    void moveToPosition(float, float);
    void bezierTurn(float, float, float, float, float, float, int);
};