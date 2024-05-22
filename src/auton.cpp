#include "vex.h"

void constants()
{
    chassis.set_turn_constants(0.4, .03, 3, 15, 3000, 2, 12);
    chassis.set_drive_constants(1.5, 0, 10, 0, 5000, 1.5, 12);
    chassis.set_swing_constants(0.3, 0.001, 2, 15, 3000, 1, 12);
    chassis.set_arch_constants(0.3, 0.001, 2, 15, 3000, 1, 12);
    chassis.set_heading_constants(0.4, 0, 1, 0, 3000, 2, 12);
}

void autonomous(void)
{

}