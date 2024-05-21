#include "PID.h"

//Proportional Control
/*
    T = Kp * (error)
    Torque = Multiplier * (Target - Current)
*/

//Integral Control
/*
    T = Ki * INT(0 to T) [(error) dt]
    Torque = Mutilplier * INT(0 to T) [Target - Current dt]
*/

//Derivative Control
/*
    T = Kd * DER(0)
    Torque = Multiplier * DER(Current)
*/


PID::PID(float Kp, float Ki, float Kd, float integral, int settle_time, float settle_error)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->integral = integral;
    this->settle_time = settle_time;
    this->settle_error = settle_error;
}

float PID::compute(float error)
{
    integral += error;
    float output = (Kp * error) + (Ki * integral) + (Kd * (error - prevError));

    prevError = error;
    current_time++;

    if(fabs(error) < settle_error)
        current_settle = true;

    return output;
}

bool PID::isSettled()
{
    if(current_time > settle_time || current_settle)
        return true;
    else
        return false;
}
