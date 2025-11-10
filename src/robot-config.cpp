#include "vex.h"

////////////// DO NOT REMOVE //////////////

// Defines the Brain and Controller
brain Brain;
controller Controller1;

///////////////////////////////////////////

//////////// Drive Train Motors ////////////

motor R1 = motor(PORT20, ratio6_1, false);
motor R2 = motor(PORT10, ratio6_1, false);
motor L1 = motor(PORT16, ratio6_1, true);
motor L2 = motor(PORT1, ratio6_1, true);

///////////////////////////////////////////

//////////// Odometry Sensors ////////////
//TODO: CHANGE THE NAMES OF THESE
rotation forwardR = rotation(PORT5);
rotation lateral = rotation(PORT4);

/////////////////////////////////////////

//////////// Inertial Sensors ////////////

inertial gyro1 = inertial(PORT6);

/////////////////////////////////////////