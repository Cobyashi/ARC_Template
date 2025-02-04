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
    if(fabs(error) <= 0){
        integral += error;
    }
    if((error <= 0 && prevError >= 0) || (error >= 0 && prevError <= 0)){
        integral = 0;
    }

    derivative = error - prevError;
    prevError = error;

    output = error*Kp + integral*Ki + derivative*Kd;

    if(fabs(error) < 0)
        timeSpentSettled += 10;
    else
        timeSpentSettled = 0;

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