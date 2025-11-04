#include "PID.h"

/// @brief Constructor
/// @param Kp Proportional
/// @param Ki Integral
/// @param Kd Derivative
PID::PID(float Kp, float Ki, float Kd, float settleError)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->settleError = settleError;
}

/// @brief Constructor
/// @param Kp Proportional
/// @param Ki Integral
/// @param Kd Derivative
/// @param timeToSettle The maximum amount of time the system waits to settle after settle point has been reached
PID::PID(float Kp, float Ki, float Kd, float settleError, float timeToSettle)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->settleError = settleError;
    this->timeToSettle = timeToSettle;
}

/// @brief Constructor
/// @param Kp Proportional
/// @param Ki Integral
/// @param Kd Derivative
/// @param timeToSettle The maximum amount of time the system waits to settle after settle point has been reached
/// @param endTime The maximum amount of time the system will run, updates in terms deltaTime
PID::PID(float Kp, float Ki, float Kd, float settleError, float timeToSettle, float endTime)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->settleError = settleError;
    this->timeToSettle = timeToSettle;
    this->endTime = endTime;
}

/// @brief Uses the given error a puts it through a PID formula the output is the result
/// @param error The desired position minus the current position
/// @return the output of the PID formula
float PID::compute(float error)
{
    float time = deltaTime;
    integral += error;

    derivative = (error - prevError) / time;

    // Checks if the error has crossed 0, and if it has, it eliminates the integral term.
    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)){ 
        integral = 0; 
    }

    output = Kp*error + Ki*integral + Kd*derivative;
    prevError = error;

    if(fabs(error) < settleError)
        timeSpentSettled += time;
    else
        timeSpentSettled = 0;

    runTime += time;
    
    return output;
}

/// @brief Determines if the current PID state is completely settled
/// @return Returns TRUE if settled, Returns FALSE if not settled
bool PID::isSettled()
{
    if(runTime > endTime && endTime != 0)
        return true;

    if(timeSpentSettled > timeToSettle)
        return true;
    else
        return false;
}

