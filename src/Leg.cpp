//
// Created by mathi on 29/12/2024.
//

#include "Leg.h"
#include <Arduino.h>
#include <ESP32Servo.h>
#include <InverseKinematics.h>

using namespace std;

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

void Leg::calculateCurve() {
    double multiplier = 0.1;
    tuple<int, int> bottom_range = make_tuple(-3, 3);
    tuple<int, int> top_range = make_tuple(3, 9);

    double length = get<1>(top_range) - get<0>(bottom_range);
    int amount_points = length / multiplier;

    // parametrisierte wege untere kurve [-3, 3]
    auto bottom_func = [] (double i) -> tuple<double, double> {
        return make_tuple(i, 0.05 * pow(i, 2));
    };

    // values obere kurve
    auto top_func = [] (double i) -> tuple<double, double> {
        return make_tuple(-1 * (i - 6), 1.281 * cos(i - 6) + 1.718);
    };

    for (int i = 0; i < amount_points; i++) {
        double t = i * multiplier - 3.;
        if (t >= get<0>(bottom_range) && t < get<1>(bottom_range)) {
           // calculate bottomfunc
            curve_values[i] = bottom_func(t);
        }
        else {
            // calculate topfunc
            curve_values[i] = top_func(t);
        }
    }
}

void Leg::calculateInterpolationAngles() {
    // 1.
    for (int i = 0; i < Constants::AMOUNT_POINTS; i++) {
        tuple<double, double> curve_point = curve_values[i];
        double thetaW = InverseKinematics::calculateThetaW(x, get<0>(curve_point), get<1>(curve_point));
        double thetaS = InverseKinematics::calculateThetaS(x, get<0>(curve_point), get<1>(curve_point));
        interpolation_angles[i] = make_tuple(thetaS, thetaW);
    }
}
