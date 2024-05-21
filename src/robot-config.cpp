#include "robot-config.h"

using signature = vision::signature;
using code = vision::code;

brain Brain;

//VEXcode devices

controller Controller1 = controller(primary);

//Left Motor Drive
    bool LeftDriveDirection = true;
    motor OneL = motor(PORT12, ratio6_1, LeftDriveDirection);
    motor TwoL = motor(PORT14, ratio6_1, !LeftDriveDirection);
    motor ThreeL = motor(PORT13, ratio6_1, LeftDriveDirection);
    motor FourL = motor(PORT15, ratio6_1, !LeftDriveDirection);
    motor_group LeftDrive = motor_group(OneL, TwoL, ThreeL, FourL);

//Right Motor Drive
    bool RightDriveDirection = false;
    motor OneR = motor(PORT19, ratio6_1, RightDriveDirection);
    motor TwoR = motor(PORT18, ratio6_1, !RightDriveDirection);;
    motor ThreeR = motor(PORT17, ratio6_1, RightDriveDirection);;
    motor FourR = motor(PORT16, ratio6_1, !RightDriveDirection);;
    motor_group RightDrive = motor_group(OneR, TwoR, ThreeR, FourR);


void vexcodeInit( void )
{

}
