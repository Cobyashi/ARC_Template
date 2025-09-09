#include "vex.h"

brain Brain;

controller Controller1;

motor R1 = motor(PORT20, ratio36_1, false);
motor R2 = motor(PORT10, ratio36_1, false);
motor L1 = motor(PORT11, ratio36_1, true);
motor L2 = motor(PORT1, ratio36_1, true);

motor_group rightDrive(R1, R2);
motor_group leftDrive(L1, L2);

inertial inertialSensors[2] = {inertial(PORT16), inertial(PORT17)};
const int inertialSize = sizeof(inertialSensors) / sizeof(inertialSensors[0]);

rotation forwardR = rotation(PORT14);
rotation lateral = rotation(PORT16);

