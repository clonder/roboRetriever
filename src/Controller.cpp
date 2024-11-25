//
// Created by mathi on 24/11/2024.
//

#include <iostream>
#include "Controller.h"
#include <string>
#include <regex>

using namespace std;

/*
Map controller input to controller object.
 */
string ControllerInput::readInput(string input)
{
    // Use regex matching to get variable conditions
    regex pattern(R"(\[lsb:\((\d+), (\d+)\), rsb:\((\d+), (\d+)\), buttons: A:(True|False), B:(True|False), X:(True|False), Y:(True|False)\])");

    smatch match;

    if (regex_match(input, match, pattern))
    {
        // Set controller input
        controller.LSB.x = stoi(match[1].str());
        controller.LSB.y = stoi(match[2].str());
        controller.RSB.x = stoi(match[3].str());
        controller.RSB.y = stoi(match[4].str());
        controller.A = (match[5] == "True");
        controller.B = (match[6] == "True");
        controller.X = (match[7] == "True");
        controller.Y = (match[8] == "True");
        return "Success";
    }
    else
    {
        return "Error";
    }
};
