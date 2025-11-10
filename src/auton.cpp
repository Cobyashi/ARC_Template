#include "auton.h"

/// @brief Sets the PID values for the DriveTrain
void setDriveTrainConstants()
{
    // Set the Drive PID values for the DriveTrain
    chassis.setDriveConstants(
        5, // Kp - Proportion Constant
        0.01, // Ki - Integral Constant
        10, // Kd - Derivative Constant
        0.5, // Settle Error
        300, // Time to Settle
        3000 // End Time
    );

    // Set the Turn PID values for the DriveTrain
    chassis.setTurnConstants(
        0.1,    // Kp - Proportion Constant
        0,      // Ki - Integral Constant
        0,      // Kd - Derivative Constant 
        0.5,    // Settle Error
        300,    // Time to Settle
        3000    // End Time
    );
    
}

/// @brief If no auton is chosen run this function during auton
void DefaultAuton()
{
    Brain.Screen.print("No auton selected.");
}

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