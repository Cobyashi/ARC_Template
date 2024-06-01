#pragma once
#include "vex.h"

using namespace vex;

class PID
{
    private:

    //Constants
    float Kp;
    float Ki;
    float Kd;
    float starti;

    //Temps
    float integral, prevError;
    
    //Settles
    float settle_error;
    float settle_time;
    float current_time;
    float timeout;

    float time_spent_settled = 0;

    public:

    //Constructor
    PID(float Kp, float Ki, float Kd, float integral, float settle_time, float settle_error, float timeout);

    //PID Compute Formula Function
    float compute(float error);

    //Determines if PID loop is settled
    bool isSettled();
};