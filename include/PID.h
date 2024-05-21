#pragma once
#include "vex.h"

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
    int settle_time;
    int current_time;

    bool current_settle = false;

    public:

    //Constructor
    PID(float Kp, float Ki, float Kd, float integral, int settle_time, float settle_error);

    //PID Compute Formula Function
    float compute(float error);

    //Determines if PID loop is settled
    bool isSettled();
};