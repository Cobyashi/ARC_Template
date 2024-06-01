#include "robot-config.h"

using signature = vision::signature;
using code = vision::code;

brain Brain;

//VEXcode devices

controller Controller1 = controller(primary);

//Left Motor Drive
    bool LeftDriveDirection = true;
    motor OneL = motor(PORT20, ratio6_1, LeftDriveDirection);
    motor TwoL = motor(PORT10, ratio6_1, !LeftDriveDirection);

//Right Motor Drive
    bool RightDriveDirection = false;
    motor OneR = motor(PORT1, ratio6_1, RightDriveDirection);
    motor TwoR = motor(PORT11, ratio6_1, !RightDriveDirection);

//Gyro
    inertial inertialSensor = inertial(PORT6);


void vexcodeInit( void )
{

}
