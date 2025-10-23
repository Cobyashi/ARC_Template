#pragma once
#include "vex.h"

class Button{
    private:
        int x, y, width, height;
    public:
        Button(int x, int y, int width, int height);

        void draw(vex::color backgroundColor, vex::color textColor, vex::fontType fontSize, std::string text);

        bool checkPress();
};

class Text{
    private:
        std::string words;
        int x, y;
        vex::fontType fontSize;
        vex::color textColor;
    public:
        Text(std::string words, int x, int y, vex::fontType fontsize, vex::color textColor);

        void printText();

};