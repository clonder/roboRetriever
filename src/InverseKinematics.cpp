#include "InverseKinematics.h"

#include <Arduino.h>
#include <cmath>
#include <Constants.h>

/**
 * Starting sequence. Sets all servos to desired default position
 */
void InverseKinematics::Start()
{
  for (Leg* leg : legs) {
    leg->x = Constants::BASEFRONTELEGEXTEND;
    leg->y = Constants::BASESIDELEGEXTEND;
    leg->z = Constants::BASEHEIGHT;
  }

  for (Leg* leg : legs) {
    leg->rotateServo(&leg->BodyServo, Constants::BODYDEFAULTANGLESERVO);
    delay(50);
    if (leg->isLeft) {
        leg->rotateServo(&leg->ShoulderServo, Constants::LEFT_SHOULDERDEFAULTANGLESERVO);
        delay(50);
    	leg->rotateServo(&leg->KneeServo, Constants::LEFT_KNEEDEFAULTANGLESERVO);
    	delay(50);
    } else {
        leg->rotateServo(&leg->ShoulderServo, Constants::SHOULDERDEFAULTANGLESERVO);
        delay(50);
    	leg->rotateServo(&leg->KneeServo, Constants::KNEEDEFAULTANGLESERVO);
    	delay(50);
   	}
  }
}

/**
 * Calculates the angle theta_H. Angle between the main body and the tilt of the leg in front view
 * @param x X coordinate
 * @param z Z coordinate
 * @return thetaH Angle in radians
 */
double InverseKinematics::calculateThetaH(double x,  double z)
{
    const double phi = atan(x / z);
    const double alpha_2 = acos(Constants::SHOULDER / sqrt(pow(x, 2) + pow(z, 2)));
    const double thetaH = phi - PI / 2 + alpha_2;
    return thetaH;
}

/**
 * Calculates the angle thetaS. Angle between the shoulder and leg
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @return thetaS Angle in radians
 */
double InverseKinematics::calculateThetaS(const double x, const double y, const double z)
{
    const double p1 = pow(Constants::LIMB, 2) + (pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2)) - pow(Constants::LIMB, 2);
    const double p2 = 2 * Constants::LIMB * sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2));
    const double phi = atan(y / sqrt(pow(x, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2)));
    const double thetaS = acos(p1 / p2) - phi;
    return thetaS;
}

/**
 * Calculates the angle thetaW. Angle between the upper leg and lower leg
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @return thetaW Angle in radians
 */
double InverseKinematics::calculateThetaW(const double x, const double y, const double z)
{
    const double p1 = pow(Constants::LIMB, 2) + pow(Constants::LIMB, 2) - (pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2));
    const double p2 = 2 * Constants::LIMB * Constants::LIMB;
    const double thetaW = acos(p1 / p2);
    return thetaW;
}

/**
 * calculates the knee and shoulder angles needed to move the robot to a desired foot-to-shoulder height
 * @param new_height desired position of the robot
 * @param new_kneeAngle holds the output for new knee angle
 * @param new_shoulderAngle holds the output for new shoulder angle
*/

void InverseKinematics::calculateVerticalMovement(float new_height, int *new_kneeAngle, int *new_shoulderAngle) {
    // TODO: check constraints of min/max height ...

    // use law of cosines to get calculate the new knee angle
    double _new_kneeAngle_radians = acos( (2 * pow(Constants::LIMB, 2) - pow(new_height, 2)) / (2 * pow(Constants::LIMB, 2)) );
    int _new_kneeAngle = degrees(_new_kneeAngle_radians);
    Serial.printf("return value of acos %f\n", _new_kneeAngle_radians);
    Serial.printf("in degrees %d\n", _new_kneeAngle);

    // use fact that all 3 angles result in 180 degrees to calculate new shoulder angle
    int _new_shoulderAngle = (180 - _new_kneeAngle) / 2;

    *new_kneeAngle = _new_kneeAngle;
    *new_shoulderAngle = _new_shoulderAngle;
};

void InverseKinematics::moveVertical(int movement) { //TODO: check if int is signed ???
    //TODO:
    // 1. calculate position from up/down. take current z coordinate and add/subtract movement
    Serial.println("Moving vertical\n");
        int _newHeight = movement; //leg.z + movement;
        int _newKneeAngle = 0;
        int _newShoulderAngle = 0;

        // 2. calculate angles for leg
        calculateVerticalMovement(_newHeight, &_newKneeAngle, &_newShoulderAngle);
        Serial.printf("newHeight: %d New KneeAngle: %d, New Shoulder Angle: %d\n", _newHeight, _newKneeAngle, _newShoulderAngle);

        // move all legs up
        LeftRear.moveVertical(_newShoulderAngle, _newKneeAngle, 0);
        RightRear.moveVertical(_newShoulderAngle, _newKneeAngle, 1);
        LeftFront.moveVertical(_newShoulderAngle, _newKneeAngle, 0);
        RightFront.moveVertical(_newShoulderAngle, _newKneeAngle, 1);

//        for (Leg* leg : legs) {
//        	leg->moveVertical(_newShoulderAngle, _newKneeAngle, 0); //move leg into different direction, so that angle is 120 in the end?
//        }
        // TODO: interpolate(_newShoulderAngle, _newKneeAngle);
}

void InverseKinematics::interpolate(int finalShoulderAngle, int finalKneeAngle) {
    int currentKneeAngle = legs[0]->KneeServo.read();
    int currentShoulderAngle = legs[0]->ShoulderServo.read(); //TODO: could be different for every leg...
    Serial.printf("Current knee angle: %d, current shoulder angle: %d\n", currentKneeAngle, currentShoulderAngle);

    while (currentShoulderAngle < finalShoulderAngle || currentKneeAngle < finalKneeAngle) {
        currentShoulderAngle += 2;
        currentKneeAngle += 2;
//        RightRear.moveVertical(currentShoulderAngle, currentKneeAngle, 1);
//        LeftRear.moveVertical(currentShoulderAngle, currentKneeAngle, 0);
//        RightFront.moveVertical(currentShoulderAngle, currentKneeAngle, 1);
//        LeftFront.moveVertical(currentShoulderAngle, currentKneeAngle, 0);
    }
}






