#include "vex.h"

Button::Button(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Button::draw(vex::color backgroundColor, vex::color textColor, vex::fontType fontSize, std::string text){
    Brain.Screen.setFillColor(backgroundColor);
    Brain.Screen.drawRectangle(x, y, width, height);
    Brain.Screen.setPenColor(textColor);
    Brain.Screen.setFont(fontSize);
    Brain.Screen.setCursor(x+2, y+2);
    Brain.Screen.print(text);
}

bool Button::checkPress(){
    if((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+width) &&
       (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+height)){
        return true;
    }
    return false;
}

Text::Text(std::string words, int x, int y, vex::fontType fontsize, vex::color textColor){
    this->words = words;
    this->x = x;
    this->y = y;
    this->fontSize = fontSize;
    this->textColor = textColor;
}

void Text::printText(){
    Brain.Screen.setCursor(x, y);
    Brain.Screen.setFont(fontSize);
    Brain.Screen.setPenColor(textColor);
    Brain.Screen.print(words);
}
