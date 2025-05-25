#include "../include/Debug.h"

Debug::Debug(std::string file)
{
    this->file = file;

    std::ofstream csvFile(file, std::ios::out | std::ios::trunc); // overwrite file

    if (csvFile.is_open()) {
        csvFile << "Time,Name,Description" << std::endl;
        csvFile.close();
    } else {
        Brain.Screen.print("Error creating CSV file");
    }
}

Debug::~Debug() 
{
    data_log.close();
}

char* Debug::stringToChar(std::string str)
{
    char* charStr = new char[str.length() + 1];
    std::strcpy(charStr, str.c_str());

    return charStr;
}

void Debug::log(std::string info)
{
    std::fstream myfile(file, std::ios::out | std::ios::app);
 
    if(myfile.is_open()) {

        myfile << Brain.Timer.time() << ","; // Time
        myfile << "Log: " << logCount << ","; // Name
        myfile << info << std::endl;
        myfile.close();

        logCount++;
    }
    else {
        Brain.Screen.print("Error opening file");
    }
}

/// @brief 
/// @param info 
void Debug::error(std::string info)
{
    char *charInfo = stringToChar(info);

    Brain.Screen.setPenColor(white);
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(100, 70, 300, 100);

    Brain.Screen.setCursor(5, 12);
    Brain.Screen.print(charInfo);

    delete [] charInfo;

    std::fstream myfile(file, std::ios::out | std::ios::app);
 
    if(myfile.is_open()) {

        myfile << Brain.Timer.time() << ","; // Time
        myfile << "Error: " << errorCount << ","; // Name
        myfile << info << std::endl;
        myfile.close();

        errorCount++;
    }
    else {
        Brain.Screen.print("Error opening file");
    }
}

/// @brief 
/// @param info 
void Debug::warning(std::string info)
{

}