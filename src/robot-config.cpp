#include "robot-config.h"

////////////// DO NOT REMOVE //////////////

// Defines the Brain and Controller
brain Brain;
controller Controller1;

///////////////////////////////////////////
/*
//////////// Drive Train Motors ////////////

motor R1 = motor(PORT9, ratio6_1, true);
motor R2 = motor(PORT3, ratio6_1, true);
motor L1 = motor(PORT10, ratio6_1, false);
motor L2 = motor(PORT4, ratio6_1, false);

///////////////////////////////////////////

//////////// Odometry Sensors ////////////
//TODO: CHANGE THE NAMES OF THESE
rotation rotation1 = rotation(PORT18);
rotation rotation2 = rotation(PORT17);

/////////////////////////////////////////

//////////// Inertial Sensors ////////////

inertial inertial1 = inertial(PORT20);

/////////////////////////////////////////
*/


//////////// Drive Train Motors ////////////

motor LFT = motor(PORT9, ratio6_1, false);
motor LFB = motor(PORT7, ratio6_1, true);
motor LBB = motor(PORT8, ratio6_1, true);
motor LBT = motor(PORT10, ratio6_1, false);

motor RFT = motor(PORT4, ratio6_1, true);
motor RFB = motor(PORT1, ratio6_1, false);
motor RBB = motor(PORT3, ratio6_1, false);
motor RBT = motor(PORT2, ratio6_1, true);
///////////////////////////////////////////

motor_group leftDrive = motor_group(LFT, LFB, LBB, LBT); // Left drive train motors
motor_group rightDrive = motor_group(RFT, RFB, RBB, RBT);

//////////// Odometry Sensors ////////////
rotation rotation1 = rotation(PORT13);
rotation rotation2 = rotation(PORT12);

/////////////////////////////////////////

//////////// Inertial Sensors ////////////

inertial inertial1 = inertial(PORT14);

/////////////////////////////////////////