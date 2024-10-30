#pragma once

#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

extern brain Brain;
extern controller Controller1;

extern motor RFront;
extern motor RBack;

extern motor LFront;
extern motor LBack;

extern inertial inertialSensors[];
extern const int inertialSize;

extern rotation forward1;
extern rotation forward2;
extern rotation lateral;