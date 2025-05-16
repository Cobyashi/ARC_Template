/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ARC                                                       */
/*    Created:      9/9/2024, 7:16:59 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <fstream>

using namespace vex;

// A global instance of competition
competition Competition;

Drive chassis(motor_group(LBack, LFront), motor_group(RBack, RFront), 3.25, 12);

inertial_group test(inertialSensors, inertialSize);

Debug debug("Test.txt");

void pre_auton(void) {
}



void autonomous(void) {

  Brain.Screen.print("Is in autonomous.");
  
}



void usercontrol(void) {
  // User control code here, inside the loop

  

  while (1) {

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  debug.log("User control started.");

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
