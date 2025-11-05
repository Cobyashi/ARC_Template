#include "auton.h"

void setDriveConstants()
{
    //
    chassis.setDriveConstants(5, 0.01, 10, 0.5, 300, 3000);

    chassis.setTurnConstants(0.1, 0, 0, 0.5, 300, 3000);
    
}

void DefaultAuton()
{
    Brain.Screen.print("No auton selected.");
}

void Auton_1()
{
    Brain.Screen.print("Auton 1 running.");
}

void Auton_2()
{
    Brain.Screen.print("Auton 2 running.");
}

void Auton_3()
{
    Brain.Screen.print("Auton 3 running.");
}

void Auton_4()
{
    Brain.Screen.print("Auton 4 running.");
}

void Auton_5()
{
    Brain.Screen.print("Auton 5 running.");
}

void Auton_6()
{
    Brain.Screen.print("Auton 6 running.");
}

void Auton_7()
{
    Brain.Screen.print("Auton 7 running.");
}

void Auton_8()
{
    Brain.Screen.print("Auton 8 running.");
    
}