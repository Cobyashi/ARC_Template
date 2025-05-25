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

    Debug(std::string file);
    ~Debug();

    char* stringToChar(std::string str);
    uint8_t* stringToUint8(std::string str);

    void log(std::string info);
    void error(std::string info);
    void warning(std::string info);
};