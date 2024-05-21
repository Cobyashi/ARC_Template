#pragma once
#include "vex.h"

using signature = vision::signature;
using code = vision::code;

extern brain Brain;

extern controller Controller1;

//VEXcode devices

extern motor OneL;
extern motor TwoL;
extern motor ThreeL;
extern motor FourL;
extern motor_group LeftDrive;

extern motor OneR;
extern motor TwoR;
extern motor ThreeR;
extern motor FourR;
extern motor_group RightDrive;

inertial inertialSensor;