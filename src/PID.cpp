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
    // Apply dead zone
    if (std::abs(error) < 0.05) error = 0;

    // Integral with anti-windup
    float integralLimit = 100.0;
    integral += error * deltaTime;
    if (integral > integralLimit) integral = integralLimit;
    if (integral < -integralLimit) integral = -integralLimit;

    // Derivative with filtering
    float alpha = 0.9;
    derivative = alpha * derivative + (1 - alpha) * ((error - prevError) / deltaTime);
    prevError = error;

    // Calculate output and apply rate limiting
    float newOutput = error * Kp + integral * Ki + derivative * Kd;
    float maxChange = 0.5;
    if (newOutput - output > maxChange) newOutput = output + maxChange;
    if (newOutput - output < -maxChange) newOutput = output - maxChange;
    output = newOutput;

    // Check if settled within a smaller range near the target
    if(output < 0.7 && output > -0.7)
        timeSpentSettled++;

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Proportion: ");
    Brain.Screen.print(error);
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print("Integral: ");
    Brain.Screen.print(integral);
    Brain.Screen.setCursor(3,1);
    Brain.Screen.print("Derivative: ");
    Brain.Screen.print(derivative);
    Brain.Screen.setCursor(4,1);
    Brain.Screen.print("Output: ");
    Brain.Screen.print(output);
    
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

