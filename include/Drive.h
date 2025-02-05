#pragma once

#include "vex.h"

using namespace vex;

enum MotorSpinType {VOLTS, PERCENTAGE, DPS, RPM};

class Drive
{
    private:

    motor_group leftDrive, rightDrive;
    inertial gyro;
    float maxVoltage;
    float wheelRatio, wheelDiameter;

    public:

    Drive(motor_group leftDrive, motor_group rightDrive, int gyro, float wheelDiameter, float wheelRatio, float maxVoltage);

    void arcade();
    void tank();

    float degToInches(float deg);
    float getCurrentPosition();

    void driveMotors(float leftVolts, float rightVolts);
    void driveMotors(float leftVolts, float rightVolts, MotorSpinType spinType);

    void brake();
    void brake(brakeType);
    void brake(bool left, bool right);
    void brake(bool left, bool right, brakeType);

    void driveDistance(float distance);

    void turnAngle();
    void turnToAngle();
};