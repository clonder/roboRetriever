//
// Created by Rahel Kempf on 01.01.2025.
//

#include "Kinematics.h"

/**
 * calculates the knee and shoulder angles needed to move the robot to a desired foot-to-shoulder height
 * @param new_height desired position of the robot
 * @param new_kneeAngle holds the output for new knee angle
 * @param new_shoulderAngle holds the output for new shoulder angle
*/

void Kinematics::calculateVerticalMovement(float new_height, int *new_kneeAngle, int *new_shoulderAngle) {
    // TODO: check constraints of min/max height ...

  // use law of cosines to get calculate the new knee angle
  int _new_kneeAngle = acos( 1 - pow(new_height, 2) / (2 * pow(Constants::LIMB, 2)));

  // use fact that all 3 angles result in 180 degrees to calculate new shoulder angle
  int _new_shoulderAngle = (180 - _new_kneeAngle) / 2;

  *new_kneeAngle = _new_kneeAngle;
  *new_shoulderAngle = _new_shoulderAngle;
};


