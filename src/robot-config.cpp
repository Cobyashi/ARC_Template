#include "vex.h"

brain Brain;

motor L1 = motor(PORT20, ratio6_1, false);
motor L2 = motor(PORT10, ratio6_1, false);
motor L3 = motor(PORT19, ratio6_1, false);
motor L4 = motor(PORT9, ratio6_1, true);
motor R1 = motor(PORT11, ratio6_1, true);
motor R2 = motor(PORT1, ratio6_1, true);
motor R3 = motor(PORT12, ratio6_1, true);
motor R4 = motor(PORT2, ratio6_1, false);

inertial inertialSensors[2] = {inertial(PORT16), inertial(PORT17)};
const int inertialSize = sizeof(inertialSensors) / sizeof(inertialSensors[0]);

rotation forwardR = rotation(PORT14);
rotation lateral = rotation(PORT16);

