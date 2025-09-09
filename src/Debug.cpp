#include "../include/Debug.h"

    
    /// @brief Logs info to debug file 
    /// @param info The information written into the debug file
    void Debug::log(char* info)
    {
        //data = reinterpret_cast<uint8_t*>(info);
        for(int i=0;i<100;i++){
            data[i] = i * 2;
        }
        
        int bytesWritten = Brain.SDcard.savefile("test.h", data, sizeof(data));

        if(bytesWritten > 0){
            Brain.Screen.print("We wrote %d bytes to the SD Card", bytesWritten);

            int bytesRead = Brain.SDcard.loadfile("test.h", data, sizeof(data));
            Brain.Screen.setCursor(2,1);
            Brain.Screen.print("We read %d bytes to the SD Card", bytesRead);

            Brain.Screen.setCursor(4,1);
            

            Brain.Screen.setCursor(6,2);
            for(int i=0;i<100;i++){
                Brain.Screen.print("%02X ", read);
            }
            
        }
        else{
            Brain.Screen.printAt(10, 40, "Error writing to SD Card");
        }


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