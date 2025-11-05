#include "vex.h"

brain Brain;

controller Controller1;

motor R1 = motor(PORT20, ratio6_1, false);
motor R2 = motor(PORT10, ratio6_1, false);
motor L1 = motor(PORT16, ratio6_1, true);
motor L2 = motor(PORT1, ratio6_1, true);

motor_group rightDrive(R1, R2);
motor_group leftDrive(L1, L2);

rotation forwardR = rotation(PORT5);
rotation lateral = rotation(PORT4);

inertial gyro1 = inertial(PORT6);