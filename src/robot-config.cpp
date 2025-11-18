#include "robot-config.h"

////////////// DO NOT REMOVE //////////////

// Defines the Brain and Controller
brain Brain;
controller Controller1;

///////////////////////////////////////////

//////////// Drive Train Motors ////////////

motor R1 = motor(PORT9, ratio6_1, true);
motor R2 = motor(PORT3, ratio6_1, true);
motor L1 = motor(PORT10, ratio6_1, false);
motor L2 = motor(PORT4, ratio6_1, false);

///////////////////////////////////////////

//////////// Odometry Sensors ////////////
//TODO: CHANGE THE NAMES OF THESE
rotation forwardR = rotation(PORT18);
rotation lateral = rotation(PORT17);

/////////////////////////////////////////

//////////// Inertial Sensors ////////////

inertial gyro1 = inertial(PORT20);

/////////////////////////////////////////