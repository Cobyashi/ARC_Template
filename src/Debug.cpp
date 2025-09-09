#include "Debug.h"

    
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

    /// @brief 
    /// @param info 
    void Debug::error(std::string info)
    {

        Brain.Screen.setPenColor(white);
        Brain.Screen.setFillColor(red);
        Brain.Screen.drawRectangle(240, 130, 100, 50);

    }

    /// @brief 
    /// @param info 
    void Debug::warning(std::string info)
    {

    }