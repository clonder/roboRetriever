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
    leg->resetPosition();
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

void InverseKinematics::moveZ(double z) {
     for (Leg* leg : legs) {
        int new_thetaH = degrees(calculateThetaH(leg->x, z));
        int new_thetaS = degrees(calculateThetaS(leg->x, leg->y, z));
        int new_thetaW = degrees(calculateThetaW(leg->x, leg->y, z));

        leg->next_kneeAngle = new_thetaW - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
        leg->next_bodyAngle = -1 * new_thetaH + Constants::BODYDEFAULTANGLESERVO;
        leg->next_shoulderAngle = -1 * (new_thetaS - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;

        Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", new_thetaW, new_thetaH, new_thetaS);
        Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, leg->y, z);

        leg->move();
        leg->updateCoordinates(leg->x, leg->y, z);

        Serial.println("Vertical Movement complete");
     }
}

void InverseKinematics::moveY(double y) {
     for (Leg* leg : legs) {
        int new_thetaH = degrees(calculateThetaH(leg->x, leg->z));
        int new_thetaS = degrees(calculateThetaS(leg->x, y, leg->z));
        int new_thetaW = degrees(calculateThetaW(leg->x, y, leg->z));

        leg->next_kneeAngle = new_thetaW - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
        leg->next_bodyAngle = -1 * new_thetaH + Constants::BODYDEFAULTANGLESERVO;
        leg->next_shoulderAngle = -1 * (new_thetaS - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;

        Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", new_thetaW, new_thetaH, new_thetaS);
        Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, y, leg->z);

        leg->move();
        leg->updateCoordinates(leg->x, y, leg->z);
        delay(1000);
     }
}


void InverseKinematics::moveY(Leg* leg, double y) {
    int new_thetaH = degrees(calculateThetaH(leg->x, leg->z));
    int new_thetaS = degrees(calculateThetaS(leg->x, y, leg->z));
    int new_thetaW = degrees(calculateThetaW(leg->x, y, leg->z));

    leg->next_kneeAngle = new_thetaW - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
    leg->next_bodyAngle = -1 * new_thetaH + Constants::BODYDEFAULTANGLESERVO;
    leg->next_shoulderAngle = -1 * (new_thetaS - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;

    Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", new_thetaW, new_thetaH, new_thetaS);
    Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, y, leg->z);

    leg->move();
    leg->updateCoordinates(leg->x, y, leg->z);
}

void InverseKinematics::moveForward() {
    // 1. all legs should be walking height (at least 10cm) so upper leg can move freely
    moveZ(Constants::WALKINGHEIGHT);
    delay(1000);

    for (Leg* leg : legs) {
        // 2. lift lower leg up
        leg->next_kneeAngle =  leg->kneeAngle - 30;
        leg->move();
        delay(1000);

        // 3. move lower leg forward
        moveY(leg, Constants::STEPSIZE);
        delay(1000);
    }
}

/**
* tilts the robot forwards or backwards
* @param Z new z coordinate
* @param direction. Enum (forward, backward). enum value = offset in the legs array. 0 moves the front legs, 2 moves the back legs
*/
void InverseKinematics::tilt(double z, Direction direction) {
    for (int i = 0; i < 3; i+=2) {
        Leg* leg = legs[direction + i];

        int new_thetaH = degrees(calculateThetaH(leg->x, z));
        int new_thetaS = degrees(calculateThetaS(leg->x, leg->y, z));
        int new_thetaW = degrees(calculateThetaW(leg->x, leg->y, z));

        leg->next_kneeAngle = new_thetaW - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
        leg->next_bodyAngle = -1 * new_thetaH + Constants::BODYDEFAULTANGLESERVO;
        leg->next_shoulderAngle = -1 * (new_thetaS - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;

        Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", new_thetaW, new_thetaH, new_thetaS);
        Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, leg->y, z);

        leg->move();
        leg->updateCoordinates(leg->x, leg->y, z);

        Serial.println("Tilt complete");
//        delay(50);
    }
}








