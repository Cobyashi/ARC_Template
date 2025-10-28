#include "vex.h"

Button::Button(std::string name, vex::color color, int x, int y, int width=9, int height=2){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->chosen = false;
    this->color = color;
    this->name = name;
}

void Button::draw(vex::color backgroundColor, vex::color textColor, vex::fontType fontSize, std::string text){
    Brain.Screen.setFillColor(backgroundColor);
    Brain.Screen.drawRectangle(x, y, width, height);
    Brain.Screen.setPenColor(textColor);
    Brain.Screen.setFont(fontSize);
    Brain.Screen.setCursor(x+1, y+1);
    Brain.Screen.print(text.c_str());
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
    Brain.Screen.print(words.c_str());
}

void createAutonButtons(vex::color colors[8], std::string names[8], Button buttons[9]){
    for(int i=0;i<4;i++){
        buttons[i] = Button(names[i], colors[i], (3 + (9*i) + (2*i)), 3);
    }
    for(int i=4;i<8;i++){
        buttons[i] = Button(names[i], colors[i], (3 + (9*i) + (2*i)), 6);
    }
    buttons[8] = Button("Back", vex::color(0xffe000), 3, 9);
    buttons[0].setChosen(true);

    // for(int i=0;i<8;i++){
    //     buttons[i].draw(buttons[i].getColor(), vex::color::white, vex::fontType::mono15, buttons[i].getName());
    // }
    // buttons[8].draw(buttons[8].getColor(), vex::color::white, vex::fontType::mono15, buttons[8].getName());
}

void clickButton(Button button, Button *oldSelected){
    oldSelected->draw(oldSelected->getColor(), vex::color::white, vex::fontType::mono15, oldSelected->getName());
    oldSelected->setChosen(false);
    button.draw(vex::color(0xffe000), vex::color::white, vex::fontType::mono15, button.getName());
    button.setChosen(true);
}

void showAutonSelectionScreen(Button buttons[9]){
    Brain.Screen.clearScreen();
    for(int i=0;i<9;i++){
        buttons[i].draw(buttons[i].getColor(), vex::color::white, vex::fontType::mono15, buttons[i].getName());
    }
}

bool checkButtonsPress(Button buttons[9], Button *oldSelected){
    for(int i=0;i<9;i++){
        if(buttons[i].checkPress()){
            clickButton(buttons[i], oldSelected);
            return true;
        }
    }
    return false;
}