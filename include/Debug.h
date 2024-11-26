#pragma once

#include "vex.h"


class Debug
{
    private:

    std::string fileName = "debug.txt";
    brain Brain;
    float runTime = 0;

    public:
    uint8_t data[ 100 ];
    uint8_t read[ 1000 ];

    void log(char* info);
    void error(std::string info);
    void warning(std::string info);
};