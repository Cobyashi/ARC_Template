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

Drive chassis(motor_group(L1, L2), motor_group(R1, R2), PORT6, 3, 1, 12);

bool isInCompetition = false;

void pre_auton(void) 
{
  setDriveConstants();
  enum preAutonStates{START_SCREEN = 0, SELECTION_SCREEN = 1};
  int currentScreen = START_SCREEN;

  gyro1.calibrate();
  forwardR.resetPosition();
  lateral.resetPosition();

  vex::color colors[8] = {vex::color::red, vex::color::red, vex::color::red, vex::color::red, 
                          vex::color::blue, vex::color::blue, vex::color::blue, vex::color::blue};
  std::string names[8] = {"Auton 1", "Auton 2", "Auton 3", "Auton 4", 
                          "Auton 5", "Auton 6", "Auton 7", "Auton 8"};
  Button buttons[9];
  createAutonButtons(colors, names, buttons);
  buttons[0].setChosen(true);

  Text selectionLabel;
  Button selectionButton;
  createPreautonScreen(selectionButton, selectionLabel);
  
  int lastPressed = 0;
  int temp;

  Controller1.Screen.print(buttons[lastPressed].getName().c_str());

  while(!isInCompetition){
    showPreautonScreen(selectionButton, selectionLabel, buttons[lastPressed].getName());
    while(currentScreen == START_SCREEN){
      if(Brain.Screen.pressing()){
        if(checkPreautonButton(selectionButton)){
          currentScreen = SELECTION_SCREEN;
        }
      }
      wait(10, msec);
    }

    showAutonSelectionScreen(buttons);
    while(currentScreen == SELECTION_SCREEN){
      if(Brain.Screen.pressing()){
        temp = checkButtonsPress(buttons);
        if(temp >= 0 && temp < 8){
          lastPressed = temp;
          Controller1.Screen.clearLine();
          Controller1.Screen.setCursor(1, 1);
          Controller1.Screen.print(buttons[lastPressed].getName().c_str());
        }
      }
      if(temp == 8)
        currentScreen = START_SCREEN;
      wait(10, msec);
    }
    wait(10, msec);
  }
  Brain.Screen.clearScreen();
}


void autonomous(void) {
  isInCompetition = true;
  Brain.Screen.clearScreen();
  //drawLogo();
  setDriveConstants();
  chassis.turnToAngle(180);
}


void usercontrol(void) {
  // User control code here, inside the loop
  Odom myOdom(2.75,2.75,2.25,1.5);
  float fwdDeg, latDeg, heading;
  myOdom.resetRotation();
  myOdom.setPosition(0,0,0);
  forwardR.resetPosition();
  lateral.resetPosition();

  writeToCard("test.txt", "THIS IS A TEST");

  while (1) {
    chassis.arcade();
    fwdDeg = forwardR.position(degrees);
    latDeg = lateral.position(degrees);
    heading = gyro1.heading();
    myOdom.updatePositionOneForward(fwdDeg, latDeg, heading);

    //Print to screen
    // Brain.Screen.setCursor(10,10);
    // Brain.Screen.print("TEST");

    Brain.Screen.setCursor(1,5);
    Brain.Screen.print("X Position: ");
    Brain.Screen.print(myOdom.getXPosition());
    Brain.Screen.setCursor(3,5);
    Brain.Screen.print("Y Position: ");
    Brain.Screen.print(myOdom.getYPosition());
    Brain.Screen.setCursor(5,5);
    Brain.Screen.print("Heading: ");
    Brain.Screen.print(myOdom.getHeading());

    

    if(Controller1.ButtonA.pressing())
    {
      chassis.driveDistance(24);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
    Brain.Screen.clearScreen();
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
