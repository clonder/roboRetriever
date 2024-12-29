//
// Created by mathi on 29/12/2024.
//

#include "Leg.h"
#include <Arduino.h>
#include <ESP32Servo.h>

void Leg::rotateKnee(const int angle)
{
    int tuned = angle - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
    Serial.printf("Knee rotated by %d\n", tuned);
    rotateServo(&KneeServo, tuned);
}

void Leg::rotateShoulder(const int angle)
{
    int tuned = -1 * (angle - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;
    Serial.printf("Shoulder rotated by %d\n", tuned);
    rotateServo(&ShoulderServo, tuned);
}

void Leg::rotateBody(const int angle)
{
    int tuned = -1 * angle + Constants::BODYDEFAULTANGLESERVO;
    Serial.printf("Body rotated by %d\n", tuned);
    rotateServo(&BodyServo, tuned);
}

void Leg::rotateServo(Servo *servo, int angle)
{
    servo->write(angle);
    delay(50);
}

void Leg::move(const double thetaH, const double thetaS, const double thetaW)
{
    rotateShoulder(thetaS);
    rotateBody(thetaH);
    rotateKnee(thetaW);
}