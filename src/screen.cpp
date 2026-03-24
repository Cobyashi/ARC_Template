#include "screen.h"

// ----------------+ Button Class +---------------- //

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
void Button::draw(vex::color backgroundColor, vex::color textColor, vex::fontType fontSize, std::string text, int yOffset=1, int xOffset=2){
    // Brain.Screen.setPenColor(backgroundColor);
    Brain.Screen.setPenColor(textColor);
    Brain.Screen.setFillColor(backgroundColor);
    Brain.Screen.drawRectangle(x, y-10, width, height);
    Brain.Screen.setFont(fontSize);
    Brain.Screen.setCursor((y/20)+yOffset, (x/10)+xOffset);
    Brain.Screen.print(text.c_str());
}

/// @brief Checks if a button has been pressed
/// @return True if it has, false otherwise
bool Button::checkPress(){
    if((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+width) &&
        (Brain.Screen.yPosition() >= (y-10) && Brain.Screen.yPosition() <= (y-10)+height))
            return true;
    
    return false;
}

// ----------------+ Text Class +---------------- //

/// @brief Constructor for text object
/// @param words Words to be printed
/// @param x X location
/// @param y Y location
/// @param fontSize a vex::fontType font size
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

// ----------------+ Screen Functions +---------------- //

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
/// @param buttons list of buttons
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

/// @brief Chooses one button for selection
/// @param button Button selected
/// @param buttons list of buttons
void clickButtonStartScreen(int selectedIndex, Button buttons[5]){
    if(selectedIndex == 1){
        buttons[2].draw(buttons[2].getColor(), vex::color::white, vex::fontType::mono20, buttons[2].getName(), 2, 3);
        buttons[2].setChosen(false);
    }else if(selectedIndex == 2){
        buttons[1].draw(buttons[1].getColor(), vex::color::white, vex::fontType::mono20, buttons[1].getName(), 2, 3);
        buttons[1].setChosen(false);
    }else if(selectedIndex == 3){
        buttons[4].draw(buttons[4].getColor(), vex::color::white, vex::fontType::mono20, buttons[4].getName(), 2, 3);
        buttons[4].setChosen(false);
    }else if(selectedIndex == 4){
        buttons[3].draw(buttons[3].getColor(), vex::color::white, vex::fontType::mono20, buttons[3].getName(), 2, 3);
        buttons[3].setChosen(false);
    }
    buttons[selectedIndex].draw(vex::color(0xffe000), vex::color::white, vex::fontType::mono20, buttons[selectedIndex].getName(), 2, 3);
    buttons[selectedIndex].setChosen(true);
}

/// @brief Show all the buttons
/// @param buttons List of 9 buttons to show
void showAutonSelectionScreen(Button buttons[9]){
    Brain.Screen.clearScreen();
    drawBackground();
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

void createPreAutonScreen(Button startScreenButtons[5], Text &selectedLabel, Text &configLabel){
    startScreenButtons[0] = Button("Options", vex::color(0xffe000), 360, 180);
    startScreenButtons[1] = Button("Red", vex::color::red, 30, 60, 90, 100);
    startScreenButtons[1].setChosen(true);
    startScreenButtons[2] = Button("Blue", vex::color::blue, 140, 60, 90, 100);
    startScreenButtons[3] = Button("Elliot", vex::color(0xc2c2c2), 250, 60, 90, 100);
    startScreenButtons[3].setChosen(true);
    startScreenButtons[4] = Button("Jacob", vex::color(0xc2c2c2), 360, 60, 90, 100);
    selectedLabel = Text("FillerText" , 10, 4, vex::mono20, vex::color::white);
    configLabel = Text("FillerText", 11, 4, vex::mono20, vex::color::white);
}

void showPreAutonScreen(Button startScreenButtons[5], Text &selectedLabel, Text &configLabel, std::string route, int teamColor, int driver){
    Brain.Screen.clearScreen();
    drawBackground();
    startScreenButtons[0].draw(vex::color(0xffe000), vex::color::white, vex::fontType::mono20, startScreenButtons[0].getName());
    for(int i=1;i<5;i++){
        if(startScreenButtons[i].isChosen())
            startScreenButtons[i].draw(vex::color(0xffe000), vex::color::white, vex::fontType::mono20, startScreenButtons[i].getName(), 2,3);
        else
            startScreenButtons[i].draw(startScreenButtons[i].getColor(), vex::color::white, vex::fontType::mono20, startScreenButtons[i].getName(), 2, 3);       
    }
            
    Brain.Screen.setFillColor(vex::color(0x723A86));
    selectedLabel.setWords("Route Selected: " + route);
    selectedLabel.printText();

    std::string colorString = teamColor ? "Blue" : "Red";
    std::string driverString = driver ? "Jacob        " : "Elliot        ";
    configLabel.setWords("Config: " + colorString + " - " + driverString);
    configLabel.printText();
}

bool checkPreAutonButtons(Button startScreenButtons[5], int &teamColor, int &driver, Text &configLabel){
    if(startScreenButtons[0].checkPress()){
        return true;
    }else{
        for(int i=1;i<5;i++){
            if(startScreenButtons[i].checkPress()){
                clickButtonStartScreen(i, startScreenButtons);
            }
        }
        if(startScreenButtons[1].isChosen()){
            teamColor = 0;
        }else{
            teamColor = 1;
        }
        if(startScreenButtons[3].isChosen()){
            driver = 0;
        }else{
            driver = 1;
        }
    }

    Brain.Screen.setFillColor(vex::color(0x723A86));
    std::string colorString = teamColor ? "Blue" : "Red";
    std::string driverString = driver ? "Jacob        " : "Elliot        ";
    configLabel.setWords("Config: " + colorString + " - " + driverString);
    configLabel.printText();

    return false;
}

void drawBackground(){
    Brain.Screen.setFillColor(vex::color(0x723A86));
    Brain.Screen.setPenColor(vex::color(0x723A86));
    Brain.Screen.drawRectangle(0, 0, 480, 240);
}