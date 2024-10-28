

#include "PID.h"

/// @brief Constructor
/// @param Kp Proportional
/// @param Ki Integral
/// @param Kd Derivative
/// @param timeToSettle The maximum amount of time the sytem waits to settle after settle point has been reached
PID::PID(float Kp, float Ki, float Kd, float timeToSettle):Kp(Kp), Ki(Ki), Kd(Kd), timeToSettle(timeToSettle)
{
}

/// @brief Uses the given error a puts it through a PID formula the output is the result
/// @param error The desired position minus the current position
/// @return the output of the PID formula
float PID::compute(float error)
{
    integral = integral + error;

    if(error <= 0)
        integral = 0;

    derivative = error - prevError;
    prevError = error;

    float output = error*Kp + integral*Ki + derivative*Kd;

    if(output < 0.7 && output > -0.7)
        timeSpentSettled++;

    
    return output;
}

/// @brief Determines if the current PID state is completely settled
/// @return Returns TRUE if settled, Returns FALSE if not settled
bool PID::isSettled()
{
    if(timeSpentSettled > timeToSettle)
        return true;
    else
        return false;
}

