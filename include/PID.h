#pragma once
#include "vex.h"

using namespace vex;

class PID
{
    private:
    float error;
    float kp;
    float ki;
    float kd;
    float starti;
    float settle_error;
    float settle_time;
    float timeout;
    float accumulated_error;
    float previous_error;
    float output;
    float time_spent_settled;
    float time_spent_running;

    public:

    PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

    PID(float error, float kp, float ki, float kd, float starti);

    float compute(float error);

    bool is_settled();
};