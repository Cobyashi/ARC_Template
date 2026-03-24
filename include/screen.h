#pragma once
#include "vex.h"

class Button{
    private:
        int x, y, width, height;
        bool chosen, isBack;
        vex::color color;
        std::string name;
    public:
        Button(){};
        Button(std::string name, vex::color color, int x, int y, int width, int height);

        void draw(vex::color backgroundColor, vex::color textColor, vex::fontType fontSize, std::string text, int yOffset, int xOffset);

        bool checkPress();
        
        bool isChosen(){return this->chosen;}
        vex::color getColor(){return this->color;}
        std::string getName(){return this->name;}
        bool getBack(){return this->isBack;}

        void setChosen(bool chosen){this->chosen = chosen;}
        void setColor(vex::color color){this->color = color;}
        void setName(std::string name){this->name = name;}
        void setBack(bool isBack){this->isBack = isBack;}

};

class Text{
    private:
        std::string words;
        int x, y;
        vex::fontType fontSize;
        vex::color textColor;
    public:
        Text(std::string words, int x, int y, vex::fontType fontsize, vex::color textColor);
        Text(){};

        void printText();
        void setWords(std::string words){
            this->words = words;
        }

};

void createAutonButtons(vex::color colors[8], std::string names[8], Button buttons[9]);
void clickButton(Button &selected, Button buttons[9]);
void showAutonSelectionScreen(Button buttons[9]);
int checkButtonsPress(Button buttons[9]);
void createPreAutonScreen(Button startScreenButtons[5], Text &selectedLabel, Text &configLabel);
void showPreAutonScreen(Button startScreenButtons[5], Text &selectedLabel, Text &configLabel, std::string route, int teamColor, int driver);
bool checkPreAutonButtons(Button startScreenButtons[5], int &teamColor, int &driver, Text &configLabel);
void drawBackground();

