/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ARC                                                       */
/*    Created:      9/9/2024, 7:16:59 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;


// A global instance of competition
competition Competition;

Drive chassis(motor_group(L1, L2), motor_group(R1, R2), PORT6, 2.5, 1, 12);

inertial_group test(inertial(PORT10), inertial(PORT11));


void pre_auton(void) {
}


void autonomous(void) {

  Brain.Screen.print("Is in autonomous.");
  
}


void usercontrol(void) {
  // User control code here, inside the loop

  while (1) {
    chassis.arcade();

    Brain.Screen.print("In Control");

    wait(20, msec); // Sleep the task for a short amount of time to
  }
}


int main() {

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
