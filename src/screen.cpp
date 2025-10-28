#include "vex.h"

Button::Button(int x, int y, int width=9, int height=2){
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
    Brain.Screen.setCursor(x+1, y+1);
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

void createButtons(vex::color colors[8], std::string names[8], Button buttons[8]){
    for(int i=0;i<4;i++){
        buttons[i] = Button((3 + (9*i) + (2*i)), 3);
    }
    for(int i=4;i<8;i++){
        buttons[i] = Button((3 + (9*i) + (2*i)), 6);
    }
    Button backButton = Button(3, 9);

    for(int i=0;i<8;i++){
        buttons[i].draw(colors[i], vex::color::white, vex::fontType::mono15, names[i]);
    }
    // backButton.draw(vex::color::COLOR, vex::color::white, vex::fontType::mono15, "Back");
}