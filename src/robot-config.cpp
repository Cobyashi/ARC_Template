#include "vex.h"

brain Brain;

motor RFront = motor(PORT11, ratio36_1, false);
motor RBack = motor(PORT1, ratio36_1, false);

motor LFront = motor(PORT20, ratio36_1, true);
motor LBack = motor(PORT10, ratio36_1, true);

inertial inertialSensors[2] = {inertial(PORT16), inertial(PORT17)};
const int inertialSize = sizeof(inertialSensors) / sizeof(inertialSensors[0]);

encoder forwardRight = encoder(Brain.ThreeWirePort.A);
encoder forwardLeft = encoder(Brain.ThreeWirePort.C);
encoder lateral = encoder(Brain.ThreeWirePort.E);

