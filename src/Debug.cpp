#include "../include/Debug.h"

Debug::Debug(std::string file_name)
{
    file = stringToChar(file_name);
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

uint8_t* Debug::stringToUint8(std::string str)
{
    int size = str.length() + 1;

    uint8_t* uint8Data = new uint8_t[size];
    for(int i=0; i<size ; i++) 
    {
        uint8Data[i] = static_cast<uint8_t>(i < str.length() ? str[i] : '\0');
    }

    return uint8Data;

}

void Debug::log(std::string info)
{
    int size = info.length() + 1;
    uint8_t * writeData = stringToUint8(info);

    uint8_t     myReadBuffer[ 1000 ];
    
    // write test data to SD Card
    int nWritten = Brain.SDcard.savefile( file, writeData, size);

    // did that work ?
    if( nWritten > 0) {
        // display on screen how many bytes we wrote
        Brain.Screen.setCursor( 2, 2 );
        Brain.Screen.print( "We wrote %d bytes to the SD Card", nWritten );

        // now read it back into a different buffer
        int nRead = Brain.SDcard.loadfile( file, myReadBuffer, sizeof(myReadBuffer) );

        // display on screen how many bytes we read
        Brain.Screen.setCursor( 3, 2 );
        Brain.Screen.print( "We read %d bytes from the SD Card", nRead );

        // and display some of the data
        Brain.Screen.setCursor( 6, 2 );
        for(int i=0;i<8;i++)
            Brain.Screen.print("%02X ", myReadBuffer[i]);
    }
    else {
        Brain.Screen.printAt( 10, 40, "Error writing to the SD Card" );        
    }

    delete [] writeData;
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