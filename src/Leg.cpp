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
    if (isLeft) {
        angle = 180 - angle;
    }
    // Serial.printf("Knee rotated by %d\n", angle);
    int direction = 1;
    if (kneeAngle > angle) {
        direction = -1;
    }

    while (kneeAngle != angle) {
        rotateServo(&KneeServo, kneeAngle);
        kneeAngle = kneeAngle + (1 * direction);
    }
    // delay(10);
}

void Leg::rotateShoulder(int angle)
{
    if (isLeft) { //left shoulder movement
        angle = 180 - angle;
    }

    int direction = 1;
    if (shoulderAngle > angle) {
        direction = -1;
    }

    while (shoulderAngle != angle) {
        rotateServo(&ShoulderServo, shoulderAngle);
        shoulderAngle = shoulderAngle + (1 * direction);
    }
    // Serial.printf("Shoulder rotated by %d\n", angle);
    // delay(10);
}

void Leg::rotateBody(int angle)
{
    // Serial.printf("Body rotated by %d\n", angle);
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
    int lastAngle = servo->read();
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
        return make_tuple(-i, 0.05 * pow(i, 2));
    };

    // values obere kurve
    auto top_func = [] (double i) -> tuple<double, double> {
        return make_tuple((i - 6), 1.281 * cos(i - 6) + 1.718);
    };

    for (int i = 0; i < amount_points; i++) {
        // Maps [0, 12] to [0, 9] + [-3, 0] ranges so that starting point of array is starting point of walking motion
        // f(x) = (x + 3) % 12 - 3
        double t = std::fmod(i * multiplier + 3., 12) - 3;
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
        double z_value = Constants::WALKINGHEIGHT - get<1>(curve_point);
        double thetaW = InverseKinematics::calculateThetaW(x, get<0>(curve_point), z_value);
        double thetaS = InverseKinematics::calculateThetaS(x, get<0>(curve_point), z_value);
        interpolation_angles[i] = make_tuple(thetaS, thetaW);
    }
}
