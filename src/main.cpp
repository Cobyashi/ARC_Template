/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Organization:       Autonomous Robotics Club (ARC)                      */
/*    Authors:            Coby Smith and Joesph Dye                           */
/*    Created:            9/9/2024                                            */
/*    Description:        ARC Template                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

////////////////////////// GLOBAL VARIABLES //////////////////////////

  // Competition Instance
  competition Competition;

  bool isInAuton = false;
  int lastPressed = 0;

  // Define Values for the Chassis here:
  Drive chassis
  (
    motor_group(L1, L2), // Left drive train motors
    motor_group(R1, R2), // Right drive train motors
    PORT6,               // Inertial Sensor Port
    3,                   // The diameter size of the wheel in inches
    1,                   // 
    12                   // The maximum amount of the voltage used in the drivebase (1 - 12)
  );

//////////////////////////////////////////////////////////////////////


/// @brief Runs before the competition starts
void preAuton() 
{
  setDriveConstants();
  enum preAutonStates{START_SCREEN = 0, SELECTION_SCREEN = 1};
  int currentScreen = START_SCREEN;
  int lastPressed = 0;

  // Calibrates/Resets the Brains sensors before the competition
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
  createPreAutonScreen(selectionButton, selectionLabel);
  
  //int lastPressed = 0;
  int temp;

  Controller1.Screen.print(buttons[lastPressed].getName().c_str());

  while(!isInAuton){
    showPreAutonScreen(selectionButton, selectionLabel, buttons[lastPressed].getName());
    while(currentScreen == START_SCREEN){
      if(Brain.Screen.pressing()){
        if(checkPreAutonButton(selectionButton)){
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

/// @brief Runs during the Autonomous Section of the Competition
void autonomous() 
{
  isInAuton = true;

  switch (lastPressed) 
  {
    case 1:
      Auton_1();
      break;
    case 2:
      Auton_2();
      break;
    case 3:
      Auton_3;
      break;
    case 4:
      Auton_4();
      break;
    case 5:
      Auton_5();
      break;
    case 6:
      Auton_6();
      break;
    case 7:
      Auton_7();
      break;
    case 8:
      Auton_8();
      break;
    default:
      DefaultAuton();
      break;
  }
}

/// @brief Runs during the UserControl section of the competition
void usercontrol() 
{
  // User control code here, inside the loop
  while (1) {


    chassis.arcade();
    wait(20, msec); // Sleep the task for a short amount of time to
  }
}


int main() 
{

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  preAuton();

  // Prevent main from exiting with an infinite loop.
  while (true) 
  {
    wait(100, msec);
  }
}
