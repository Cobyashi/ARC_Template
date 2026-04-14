/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Organization:       Autonomous Robotics Club (ARC)                      */
/*    Authors:            Coby Smith and Joseph Dye                           */
/*    Created:            9/9/2024                                            */
/*    Description:        ARC Template                                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "screen.h"
#include "util.h"
#include "Drive.h"
#include "semiPIDTuner.h"
#include "pidTests.h"
#include "images.h"

using namespace vex;

////////////////////////// GLOBAL VARIABLES //////////////////////////

  // Competition Instance
  competition Competition;

  int odomType = TWO_AT_45;

  bool isInAuton = false;
  int lastPressed = 0;
  int teamColor = 0; 
  int driver = 0; 

  // Define Values for the Chassis here:
  // Drive chassis
  // (
  //   motor_group(L1, L2), // Left drive train motors
  //   motor_group(R1, R2), // Right drive train motors
  //   PORT20,               // Inertial Sensor Port
  //   3.25,              // The diameter size of the wheel in inches
  //   1,                   // 
  //   6,                   // The maximum amount of the voltage used in the drivebase (1 - 12)
  //   odomType,
  //   2,                  //Odometry wheel diameter (set to zero if no odom)
  //   -1.0,               //Odom pod1 offset 
  //   -1.0                //Odom pod1 offset
  // );

    Drive chassis
  (
    motor_group(LFT, LFB, LBB, LBT), // Left drive train motors
    motor_group(RFT, RFB, RBB, RBT), // Right drive train motors
    PORT20,               // Inertial Sensor Port
    2.66,              // The diameter size of the wheel in inches
    1,                   // 
    12,                   // The maximum amount of the voltage used in the drivebase (1 - 12)
    odomType,
    1.955,                  //Odometry wheel diameter (set to zero if no odom)
    -1.28,               //Odom pod1 offset 
    -1.28                //Odom pod1 offset
  );

//////////////////////////////////////////////////////////////////////

///////////////////////// Prototypes /////////////////////////////////

void setDriveTrainConstants();
void Auton_1();
void Auton_2();
void Auton_3();
void Auton_4();
void Auton_5();
void Auton_6();
void Auton_7();
void Auton_8();
void semiPIDTest();
void pidTests();

//////////////////////////////////////////////////////////////////////


/// @brief Runs before the competition starts
void preAuton() 
{
  //setDriveTrainConstants();

  chassis.brake(coast);       // make sure they aren’t holding weirdly
  chassis.driveMotors(0, 0);  

  enum preAutonStates{START_SCREEN = 0, SELECTION_SCREEN = 1};
  int currentScreen = START_SCREEN;

  // Calibrates/Resets the Brains sensors before the competition
  inertial1.calibrate();
  rotation1.resetPosition();
  rotation2.resetPosition();

  vex::color colors[8] = {vex::color::red, vex::color::red, vex::color::red, vex::color::red, 
                          vex::color::blue, vex::color::blue, vex::color::blue, vex::color::blue};
  std::string names[8] = {"NONE", "NONE", "NONE", "NONE", 
                          "NONE", "NONE", "NONE", "NONE"};
  Button buttons[9];
  createAutonButtons(colors, names, buttons);
  buttons[0].setChosen(true);

  Text selectionLabel;
  Text configLabel;
  Button startScreenButtons[5];
  createPreAutonScreen(startScreenButtons, selectionLabel, configLabel);
  
  int temp;

  Controller1.Screen.print(buttons[lastPressed].getName().c_str());

  while(!isInAuton){
    showPreAutonScreen(startScreenButtons, selectionLabel, configLabel, buttons[lastPressed].getName(), teamColor, driver);
    while(currentScreen == START_SCREEN){
      if(Brain.Screen.pressing()){
        if(checkPreAutonButtons(startScreenButtons, teamColor, driver, configLabel)){
          currentScreen = SELECTION_SCREEN;
        }
        Controller1.Screen.clearLine();
        Controller1.Screen.setCursor(1, 1);
        std::string colorString = teamColor ? "Blue" : "Red";
        std::string driverString = driver ? "Driver1" : "Driver2";
        std::string controllerPrint = buttons[lastPressed].getName() + " - " + colorString + " - " + driverString;
        Controller1.Screen.print(controllerPrint.c_str());
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
          std::string colorString = teamColor ? "Blue" : "Red";
          std::string driverString = driver ? "Driver1" : "Driver2";
          std::string controllerPrint = buttons[lastPressed].getName() + " - " + colorString + " - " + driverString;
          Controller1.Screen.print(controllerPrint.c_str());
        }
      }
      if(temp == 8)
        currentScreen = START_SCREEN;
      wait(10, msec);
    }
    wait(10, msec);
  }
}

/// @brief Runs during the Autonomous Section of the Competition
void autonomous() 
{
  isInAuton = true;
  rotation1.resetPosition();
  rotation2.resetPosition();
  inertial1.resetHeading();

  //setDriveTrainConstants();
  chassis.setPosition(0,0,0);

  //pidTest();

  switch (lastPressed) 
  {
    case 1:
      Auton_1();
      break;
    case 2:
      Auton_2();
      break;
    case 3:
      Auton_3();
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
      break;
  }
}

/// @brief Runs during the UserControl section of the competition
void usercontrol() 
{

  std::cout << "Starting User Control" << std::endl;
  chassis.driveDistanceWithOdom(6);
  std::cout << "Finished first move" << std::endl;
  semiPIDTest();
  std::cout << "Finished semi PID Test" << std::endl;
  
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

/*


// Do we want to build this into a optional PID so that if a team doesn't want to use the multiple profiles 
// and just wants to set one set of PID values, they can do that?

//They can also just reduce the number of profiles to 1 and it would work the same as a normal PID


/// @brief Sets the PID values for the DriveTrain
void setDriveTrainConstants()
{
    // Set the Drive PID values for the DriveTrain
    chassis.setDriveConstants(
        0.4,  // Kp - Proportion Constant
        0.0, // Ki - Integral Constant
        0.1, // Kd - Derivative Constant
        0.5, // Settle Error
        300, // Time to Settle
        5000 // End Time
    );

    // Set the Turn PID values for the DriveTrain
    chassis.setTurnConstants(
        0.3,    // Kp - Proportion Constant
        0,      // Ki - Integral Constant
        0,      // Kd - Derivative Constant 
        0.5,    // Settle Error
        300,    // Time to Settle
        3000    // End Time
    );
    
}
*/


/// @brief Auton Slot 1 - Write code for route within this function.
void Auton_1()
{
    Brain.Screen.print("Auton 1 running.");
}

/// @brief Auton Slot 2 - Write code for route within this function.
void Auton_2()
{
    Brain.Screen.print("Auton 2 running.");
}

/// @brief Auton Slot 3 - Write code for route within this function.
void Auton_3()
{
    Brain.Screen.print("Auton 3 running.");
}

/// @brief Auton Slot 4 - Write code for route within this function.
void Auton_4()
{
    Brain.Screen.print("Auton 4 running.");
}

/// @brief Auton Slot 5 - Write code for route within this function.
void Auton_5()
{
    Brain.Screen.print("Auton 5 running.");
}

/// @brief Auton Slot 6 - Write code for route within this function.
void Auton_6()
{
    Brain.Screen.print("Auton 6 running.");
}

/// @brief Auton Slot 7 - Write code for route within this function.
void Auton_7()
{
    Brain.Screen.print("Auton 7 running.");
}

/// @brief Auton Slot 8 - Write code for route within this function.
void Auton_8()
{
    Brain.Screen.print("Auton 8 running.");
    
}

/// @brief Runs the semi-automatic PID Test
void semiPIDTest(){
  /*
  --------Buttons--------

  R2 - Drive the Robot (Robot alternates between driving forward and backwards automatically)
  R1/L1 - Swap between drive PID and turn PID
  UP/Down Arrows - Change the drive or turn distance / Adjust the variable values 
  Left/Right Arrows - Change the variable to change (P, I, D, settleError, settleTime, and endTime)
  A - Enter into a variable to be able to change it (Will not be able to use R2 while in this)
  B - Exit and Save a variable (able to use R2 after this)

  --------To Use--------
  Go into userControl and uncomment (Remove //) semiPIDTest();
  Then run the normal user-control and the controller screen will show the test
  */
  PIDTuner tuner(chassis);
  tuner.run();
}

void pidTest(){
  
  /*
      To use one of the tests below, just uncoment the test below and uncomment //pidTest() in Autonomous()
  */
  
  
   smallDrivingTest(chassis);
  // largeDrivingTest(chassis);
  // mixedDrivingTest(chassis, 20);
  
  // smallTurningTest(chassis);
  // largeTurningTest(chassis);
  // mixedTurningTest(chassis, 20);
}