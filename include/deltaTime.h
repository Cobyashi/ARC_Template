#pragma once
#include "vex.h"

struct DeltaTime
{
    private:

        float preTime;

        vex::brain clock;

    public:

        DeltaTime() {preTime = 0; updateTime();}

        /// @brief Updates the time of the DeltaTime variable
        /// @return Returns the difference in time passed since the last call
        float updateTime() 
        {
            float time = clock.Timer.time() - preTime;
            preTime = clock.Timer.time();
            return time;
        }

        operator float() {return updateTime();}
        bool operator==(DeltaTime&DELTATIME) {return updateTime() == DELTATIME.updateTime();}
        bool operator==(float DELTATIME) {return updateTime() == DELTATIME;}
        bool operator==(double DELTATIME) {return updateTime() == DELTATIME;}
        bool operator==(int DELTATIME) {return updateTime() == DELTATIME;}
};