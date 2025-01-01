//
// Created by mathi on 29/12/2024.
//

#include "Leg.h"
#include <Arduino.h>

void Leg::rotateKnee(const int angle) {
   int tuned = angle - KneeServo.defaultPhysicalAngle;
    KneeServo.rotateServo(tuned);
    Serial.printf("Knee rotated by %d\n", tuned);
}

void Leg::rotateShoulder(const int angle)
{
    int tuned = -1 * (angle - (ShoulderServo.defaultAngle - ShoulderServo.defaultPhysicalAngle)); // TODO: check if correct
    ShoulderServo.rotateServo(tuned);
    Serial.printf("Shoulder rotated by %d\n", tuned);
}

// void Leg::rotateBody(const int angle) // TODO:
// {
//     int tuned = -1 * angle + BodyServo.defaultAngle;
//     BodyServo.rotateServo(tuned);
//     Serial.printf("Body rotated by %d\n", tuned);
// }

void Leg::updateCoordinates(const double new_x, const double new_y, const double new_z) {
    previousX = x;
    previousY = y;
    previousZ = z;
    x = new_x;
    y = new_y;
    z = new_z;
}

void Leg::resetPosition() {
    BodyServo.resetPosition();
    ShoulderServo.resetPosition();
    KneeServo.resetPosition();
    updateCoordinates(Constants::BASEFRONTELEGEXTEND, Constants::BASESIDELEGEXTEND, Constants::BASEHEIGHT);
}

void Leg::moveVertical(int shoulderAngle, int kneeAngle) {
    rotateShoulder(shoulderAngle);
    rotateKnee(kneeAngle);
}

