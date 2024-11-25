//
// Created by mathi on 24/11/2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>

using namespace std;

class JoyStick
{
public:
    float x;
    float y;
};

class Controller {
    
    public:
        bool A;    // A button
        bool B;    // B Button
        bool Y;    // Y Button
        bool X;    // X Button
        bool LB;   // LB Button
        bool RB;   // RB Button

        JoyStick LSB;
        JoyStick RSB;
};

class ControllerInput
{
    public:
        Controller controller;

    string readInput(string input);
};



#endif //CONTROLLER_H
