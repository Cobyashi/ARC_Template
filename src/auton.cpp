#include "auton.h"

void constants()
{

    chassis.set_turn_constants
    (
        0.4,    //Kp
        0.03,   //Ki
        3,      //Kd
        15,     //Start i
        3000,   //Settle Time
        2,      //Settle Error
        30000,  //Timeout
        6       //Max Voltage
    );

    chassis.set_drive_constants
    (
        1.5,    //Kp
        0,      //Ki
        10,     //Kd
        0,      //Start i
        5000,   //Settle Time
        1.5,    //Settle Error
        50000,  //Timeout
        6       //Max Voltage
    );

    chassis.set_swing_constants
    (
        0.3,    //Kp
        0.001,  //Ki
        2,      //Kd
        15,     //Start i
        3000,   //Settle Time
        1,      //Settle Error
        30000,  //Timeout
        6       //Max Voltage
    );

    chassis.set_arch_constants
    (
        0.3,    //Kp
        0.001,  //Ki
        2,      //Kd
        15,     //Start i
        3000,   //Settle Time
        1,      //Settle Error
        30000,  //Timeout
        6       //Max Voltage
    );

    chassis.set_heading_constants
    (
        0.4,    //Kp
        0,      //Ki
        1,      //Kd
        0,      //Start i
        3000,   //Settle Time
        2,      //Settle Error
        50000,  //Timeout
        6       //Max Voltage
    );
}

void ProgAuto(void)
{
    inertialSensor.calibrate();
    waitUntil(!inertialSensor.isCalibrating());

    chassis.turn_to_angle(90);
}