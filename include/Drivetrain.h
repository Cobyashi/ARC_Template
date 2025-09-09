#pragma once

#include "vex.h"

//Drivetrain parent class would open up all the other classes to better work with one another
//This would allow us to not have to restate physical attributes of the robots in separate cases
// ie. wheel diameter, odom distance, gear ratios, etc. 
class Drivetrain{
    private:
        float heading;
        float x_position;
        float y_position;
    public:


};