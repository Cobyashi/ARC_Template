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
    this->isBack = false;
}

/// @brief Draws a rectangle/button with respect to size, location, color, and font
/// @param backgroundColor Color of the button
/// @param textColor Color of the text
/// @param fontSize a vex::fontType font size
/// @param text Button label
void Button::draw(vex::color backgroundColor, vex::color textColor, vex::fontType fontSize, std::string text){
    Brain.Screen.setPenColor(backgroundColor);
    Brain.Screen.setFillColor(backgroundColor);
    Brain.Screen.drawRectangle(x, y, width, height);
    Brain.Screen.setPenColor(textColor);
    Brain.Screen.setFont(fontSize);
    Brain.Screen.setCursor((y/20)+1, (x/10)+2);
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
Text::Text(std::string words, int x, int y, vex::fontType fontSize, vex::color textColor){
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
    buttons[8].setBack(true);
    buttons[0].setChosen(true);
}

/// @brief Chooses one button for selection
/// @param button Button selected
/// @param oldSelected Previously chosen button
void clickButton(Button &selected, Button buttons[9]){
    if(!selected.getBack()){
        for(int i=0;i<9;i++){
            buttons[i].draw(buttons[i].getColor(), vex::color::white, vex::fontType::mono20, buttons[i].getName());
            buttons[i].setChosen(false);
        }
        selected.draw(vex::color(0xffe000), vex::color::white, vex::fontType::mono20, selected.getName());
        selected.setChosen(true);
    }
}

/// @brief Show all the buttons
/// @param buttons List of 9 buttons to show
void showAutonSelectionScreen(Button buttons[9]){
    Brain.Screen.clearScreen();
    Text header = Text("Select an Autonomous Route", 1, 1, vex::fontType::mono30, vex::color::white);
    header.printText();
    for(int i=0;i<9;i++){
        if(buttons[i].isChosen())
            buttons[i].draw(vex::color(0xffe000), vex::color::white, vex::fontType::mono20, buttons[i].getName());
        else
            buttons[i].draw(buttons[i].getColor(), vex::color::white, vex::fontType::mono20, buttons[i].getName());
    }
}

/// @brief Checks all buttons to see if they've been pressed
/// @param buttons List of 9 buttons to check
/// @param oldSelected Previously selected button
/// @return True if a button has been pressed, false otherwise
int checkButtonsPress(Button buttons[9]){
    for(int i=0;i<9;i++){
        if(buttons[i].checkPress()){
            clickButton(buttons[i], buttons);
            return i;
        }
    }
    return -1;
}

void createPreautonScreen(Button &autonButton, Text &selectedLabel){
    autonButton = Button("Options", vex::color(0xffe000), 360, 180);
    selectedLabel = Text("FillerText" , 10, 4, vex::mono20, vex::color::white);
    //Create Text
    //Create ARC logo
}

void showPreautonScreen(Button &autonButton, Text &selectedLabel, std::string route){
    Brain.Screen.clearScreen();
    autonButton.draw(autonButton.getColor(), vex::color::white, vex::fontType::mono20, autonButton.getName());
    
    Brain.Screen.setFillColor(vex::color::black);
    selectedLabel.setWords("Route Selected: " + route);
    selectedLabel.printText();
}

bool checkPreautonButton(Button autonButton){
    if(autonButton.checkPress()){
        return true;
    }
    return false;
}