#pragma once
#include "vex.h"

//PID Class
class PID
{
    private:
    
    float Kp, Ki, Kd;

    float prevError;
    float integral = 0, derivative;
    float output;
    float timeToSettle;
    float timeSpentSettled = 0;

    public:

    PID(float Kp, float Ki, float Kd, float timeToSettle);

    float compute(float error, float deltatime);

    bool isSettled();
};