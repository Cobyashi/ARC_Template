#pragma once

#include "vex.h"


class Debug
{
    private:

    std::string fileName = "debug.txt";
    brain Brain;
    float runTime = 0;

    public:

    void log(char* info);
    void error(std::string info);
    void warning(std::string info);
};