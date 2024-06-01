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


PID::PID(float Kp, float Ki, float Kd, float integral, float settle_time, float settle_error, float timeout)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->integral = integral;
    this->settle_time = settle_time;
    this->settle_error = settle_error;
    this->timeout = timeout;
}

float PID::compute(float error)
{
    integral += error;
    float output = (Kp * error) + (Ki * integral) + (Kd * (error - prevError));

    prevError = error;

    if(fabs(error)<settle_error)
        time_spent_settled += 10;
    else
        time_spent_settled = 0;

    current_time++;

    return output;
}

bool PID::isSettled()
{
    if (current_time > timeout && timeout != 0)
        return true;

    if (time_spent_settled > settle_time)
        return true;

  return false;
}
