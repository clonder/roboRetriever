//
// Created by Rahel Kempf on 01.01.2025.
//

#include "Robot.h"

/**
 * Starting sequence. Sets all servos to desired default position
 */
void Robot::Start() {
      Serial.println("Start Robototer\n");
    for (Leg leg : legs) {
        leg.resetPosition();
        Serial.printf("leg is being reset\n");
    }
};

/*
 * Moves the robot up and down.
 */

void Robot::moveVertical(int movement) { //TODO: check if int is signed ???
    //TODO:
    // 1. calculate position from up/down. take current z coordinate and add/subtract movement
    Serial.println("Moving vertical\n");
    for (Leg leg : legs) {
      int _newHeight = movement; //leg.z + movement;
      int _newKneeAngle = 0;
      int _newShoulderAngle = 0;

      // 2. calculate angles for leg
      kinematics.calculateVerticalMovement(_newHeight, &_newKneeAngle, &_newShoulderAngle); //TODO: maybe move outside loop bc it only needs to be calculated once
      Serial.printf("newHeight: %d New KneeAngle: %d, New Shoulder Angle: %d\n", _newHeight, _newKneeAngle, _newShoulderAngle);
      leg.moveVertical(_newShoulderAngle, _newKneeAngle); //TODO: move multiple legs at the same time ...
    }
}

