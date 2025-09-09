#pragma once

#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

extern brain Brain;
extern controller Controller1;

extern motor R1;
extern motor R2;
extern motor L1;
extern motor L2;

extern motor_group rightDrive;
extern motor_group leftDrive;

extern inertial inertialSensors[];
extern const int inertialSize;

extern rotation forwardR;
extern rotation lateral;