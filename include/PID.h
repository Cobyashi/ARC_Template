#pragma once
#include "vex.h"
#include "deltaTime.h"

//PID Class
class PID
{
    private:
    
    float Kp, Ki, Kd, settleError;

    // DeltaTime deltaTime;

    float prevError = 0;
    float integral = 0, derivative = 0;
    float output = 0;
    float timeToSettle = 0, endTime = 0;
    float timeSpentSettled = 0, runTime = 0;

    public:

    PID(float Kp, float Ki, float Kd, float settleError);
    PID(float Kp, float Ki, float Kd, float settleError, float TimeToSettle);
    PID(float Kp, float Ki, float Kd, float settleError, float timeToSettle, float endTime);

    float compute(float error);

    bool isSettled();

    float getTimeSpentSettled(){return timeSpentSettled;}
};