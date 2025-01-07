//
// Created by mathi on 29/12/2024.
//

#include "Leg.h"
#include <Arduino.h>
#include <ESP32Servo.h>

void Leg::rotateKnee(int angle)
{
    // int tuned = angle - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
    if (isLeft) {
        angle = 180 - angle;
    }
    Serial.printf("Knee rotated by %d\n", angle);
    rotateServo(&KneeServo, angle);
}

void Leg::rotateShoulder(int angle)
{
    // int tuned = -1 * (angle - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;
    if (isLeft) { //left shoulder movement
        angle = 180 - angle;
    }
    Serial.printf("Shoulder rotated by %d\n", angle);
    rotateServo(&ShoulderServo, angle);
}

void Leg::rotateBody(int angle)
{
    // int tuned = -1 * angle + Constants::BODYDEFAULTANGLESERVO;
    Serial.printf("Body rotated by %d\n", angle);
    rotateServo(&BodyServo, angle);
}

void Leg::updateCoordinates(const double new_x, const double new_y, const double new_z) {
    x = new_x;
    y = new_y;
    z = new_z;
}

void Leg::updateAngles() {
    kneeAngle = next_kneeAngle;
    shoulderAngle = next_shoulderAngle;
    bodyAngle = next_bodyAngle;
}

void Leg::rotateServo(Servo *servo, int angle)
{
    servo->write(angle);
    // delay(50);
}

void Leg::move() {
    rotateBody(next_bodyAngle);
    rotateShoulder(next_shoulderAngle);
    rotateKnee(next_kneeAngle);
    updateAngles();
}

void Leg::resetPosition() {
    rotateServo(&BodyServo, Constants::BODYDEFAULTANGLESERVO);
    if (isLeft) {
        rotateServo(&ShoulderServo, Constants::LEFT_SHOULDERDEFAULTANGLESERVO);
    	rotateServo(&KneeServo, Constants::LEFT_KNEEDEFAULTANGLESERVO);
    } else {
        rotateServo(&ShoulderServo, Constants::SHOULDERDEFAULTANGLESERVO);
    	rotateServo(&KneeServo, Constants::KNEEDEFAULTANGLESERVO);
   	}
    updateCoordinates(Constants::BASEFRONTELEGEXTEND, Constants::BASESIDELEGEXTEND, Constants::BASEHEIGHT);
}