#include "vex.h"

/// @brief Button Constructor
/// @param name Button label
/// @param color Color of the button
/// @param x X location
/// @param y Y location
/// @param width 
/// @param height 
Button::Button(std::string name, vex::color color, int x, int y, int width=90, int height=40){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->chosen = false;
    this->color = color;
    this->name = name;
}

/// @brief Draws a rectangle/button with respect to size, location, color, and font
/// @param backgroundColor Color of the button
/// @param textColor Color of the text
/// @param fontSize a vex::fontType font size
/// @param text Button label
void Button::draw(vex::color backgroundColor, vex::color textColor, vex::fontType fontSize, std::string text){
    Brain.Screen.setFillColor(backgroundColor);
    Brain.Screen.drawRectangle(x, y, width, height);
    Brain.Screen.setPenColor(textColor);
    Brain.Screen.setFont(fontSize);
    Brain.Screen.setCursor(x+1, y+1);
    Brain.Screen.print(text.c_str());
}

/// @brief Checks if a button has been pressed
/// @return True if it has, false otherwise
bool Button::checkPress(){
    if((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+width) &&
       (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+height)){
        return true;
    }
    return false;
}

/// @brief Constructor for text object
/// @param words Words to be printed
/// @param x X location
/// @param y Y location
/// @param fontsize a vex::fontType font size
/// @param textColor a vex::color color
Text::Text(std::string words, int x, int y, vex::fontType fontsize, vex::color textColor){
    this->words = words;
    this->x = x;
    this->y = y;
    this->fontSize = fontSize;
    this->textColor = textColor;
}

/// @brief Prints text in the screen
void Text::printText(){
    Brain.Screen.setCursor(x, y);
    Brain.Screen.setFont(fontSize);
    Brain.Screen.setPenColor(textColor);
    Brain.Screen.print(words.c_str());
}

/// @brief Creates all 9 buttons for the autonomous route selection screen
/// @param colors Colors of the buttons
/// @param names Names to be put on the buttons
/// @param buttons List of 9 buttons
void createAutonButtons(vex::color colors[8], std::string names[8], Button buttons[9]){
    for(int i=0;i<4;i++){
        buttons[i] = Button(names[i], colors[i], (30 + (90*i) + (20*i)), 60);
    }
    for(int i=4;i<8;i++){
        buttons[i] = Button(names[i], colors[i], (30 + (90*(i-4)) + (20*(i-4))), 120);
    }
    buttons[8] = Button("Back", vex::color(0xffe000), 30, 180);
    buttons[0].setChosen(true);
}

/// @brief Chooses one button for selection
/// @param button Button selected
/// @param oldSelected Previously chosen button
void clickButton(Button button, Button *oldSelected){
    oldSelected->draw(oldSelected->getColor(), vex::color::white, vex::fontType::mono20, oldSelected->getName());
    oldSelected->setChosen(false);
    button.draw(vex::color(0xffe000), vex::color::white, vex::fontType::mono20, button.getName());
    button.setChosen(true);
}

/// @brief Show all the buttons
/// @param buttons List of 9 buttons to show
void showAutonSelectionScreen(Button buttons[9]){
    Brain.Screen.clearScreen();
    for(int i=0;i<9;i++){
        buttons[i].draw(buttons[i].getColor(), vex::color::white, vex::fontType::mono20, buttons[i].getName());
    }
}

/// @brief Checks all buttons to see if they've been pressed
/// @param buttons List of 9 buttons to check
/// @param oldSelected Previously selected button
/// @return True if a button has been pressed, false otherwise
bool checkButtonsPress(Button buttons[9], Button *oldSelected){
    for(int i=0;i<9;i++){
        if(buttons[i].checkPress()){
            clickButton(buttons[i], oldSelected);
            return true;
        }
    }
    return false;
}