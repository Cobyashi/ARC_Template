#pragma once

#include "vex.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

class Debug
{
    private:

    brain Brain;
    std::ofstream data_log;
    std::string file;

    int logCount = 1;
    int errorCount = 1; 
    int warningCount = 1;

    public:
    uint8_t data[ 100 ];
    uint8_t read[ 1000 ];

    void log(char* info);
    void error(std::string info);
    void warning(std::string info);
};