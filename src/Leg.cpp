//
// Created by mathi on 29/12/2024.
//

#include "Leg.h"
#include <Arduino.h>
#include <ESP32Servo.h>

void Leg::rotateKnee(const int angle)
{
    int tuned = 0;
    if (angle > Constants::KNEEDEFAULTANGLE) {
        tuned = angle - Constants::KNEEDEFAULTANGLE;
    }
    if (isLeft) {
        tuned = 180 - tuned;
    }
    rotateServo(&KneeServo, tuned);
    Serial.printf("Knee rotated by %d\n", tuned);
}

void Leg::rotateShoulder(const int angle)
{
    int tuned = Constants::SHOULDERDEFAULTANGLESERVO + angle;
    if (isLeft) { //left shoulder movement
        tuned = 180 - tuned;
    }
    // int tuned = -1 * (angle - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;
    Serial.printf("Shoulder rotated by %d\n", tuned);
    rotateServo(&ShoulderServo, tuned);
}

// void Leg::rotateBody(const int angle)
// {
//     int tuned = -1 * angle + Constants::BODYDEFAULTANGLESERVO;
//     Serial.printf("Body rotated by %d\n", tuned);
//     rotateServo(&BodyServo, tuned);
// }

void Leg::updateCoordinates(const double new_x, const double new_y, const double new_z) {
    prev_x = x;
    prev_y = y;
    prev_z = z;

    x = new_x;
    y = new_y;
    z = new_z;
}

void Leg::rotateServo(Servo *servo, int angle)
{
    servo->write(angle);
    delay(50);
}

// void Leg::move(const double thetaH, const double thetaS, const double thetaW)
// {
//     rotateShoulder(thetaS);
//     // rotateBody(thetaH);
//     rotateKnee(thetaW);
// }

void Leg::resetPosition() {
    rotateServo(&BodyServo, Constants::BODYDEFAULTANGLESERVO);
    rotateServo(&ShoulderServo, Constants::SHOULDERDEFAULTANGLESERVO);
    rotateServo(&KneeServo, Constants::KNEEDEFAULTANGLESERVO);
    updateCoordinates(Constants::BASEFRONTELEGEXTEND, Constants::BASESIDELEGEXTEND, Constants::BASEHEIGHT);
}

void Leg::moveVertical(const int shoulderAngle, const int kneeAngle, const bool isRight) {
    rotateShoulder(shoulderAngle);
    rotateKnee(kneeAngle);
    // updateCoordinates() TODO:
}