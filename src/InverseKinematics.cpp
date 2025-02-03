#include "InverseKinematics.h"

#include <Arduino.h>
#include <cmath>
#include <Constants.h>

using namespace std;

/**
 * Starting sequence. Sets all servos to desired default position
 */
void InverseKinematics::Start()
{
    for (Leg *leg : legs)
    {
        leg->resetPosition();
    }
}

/**
 * Calculates the angle theta_H. Angle between the main body and the tilt of the leg in front view
 * @param x X coordinate
 * @param z Z coordinate
 * @return thetaH Angle in degrees
 */
int InverseKinematics::calculateThetaH(double x, double z)
{
    const double phi = atan(x / z);
    const double alpha_2 = acos(Constants::SHOULDER / sqrt(pow(x, 2) + pow(z, 2)));
    const double thetaH = phi - PI / 2 + alpha_2;

    return -1 * degrees(thetaH) + Constants::BODYDEFAULTANGLESERVO;
    ;
}

/**
 * Calculates the angle thetaS. Angle between the shoulder and leg
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @return thetaS Angle in degrees
 */
int InverseKinematics::calculateThetaS(const double x, const double y, const double z)
{
    const double p1 = pow(Constants::LIMB, 2) + (pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2)) - pow(Constants::LIMB, 2);
    const double p2 = 2 * Constants::LIMB * sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2));
    const double phi = atan(y / sqrt(pow(x, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2)));
    const double thetaS = acos(p1 / p2) - phi;
    return -1 * (degrees(thetaS) - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;
    ;
}

/**
 * Calculates the angle thetaW. Angle between the upper leg and lower leg
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @return thetaW Angle in degrees
 */
int InverseKinematics::calculateThetaW(const double x, const double y, const double z)
{
    const double p1 = pow(Constants::LIMB, 2) + pow(Constants::LIMB, 2) - (pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2));
    const double p2 = 2 * Constants::LIMB * Constants::LIMB;
    const double thetaW = acos(p1 / p2);
    return degrees(thetaW) - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
}

/**
 * moves the robot vertically to the given z coordinate.
 * @param z Z coordinate
 */
void InverseKinematics::moveZ(double z)
{
    for (Leg *leg : legs)
    {
        leg->next_kneeAngle = calculateThetaW(leg->x, leg->y, z);
        leg->next_bodyAngle = calculateThetaH(leg->x, z);
        leg->next_shoulderAngle = calculateThetaS(leg->x, leg->y, z);

        Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, leg->y, z);

        leg->move();
        leg->updateCoordinates(leg->x, leg->y, z);

        Serial.println("Vertical Movement complete");
    }
}

/**
 * moves the robot forward/backward to a given y coordinate.
 * @param y Y coordinate
 */
void InverseKinematics::moveY(double y)
{
    for (Leg *leg : legs)
    {
        leg->next_bodyAngle = calculateThetaH(leg->x, leg->z);
        leg->next_kneeAngle = calculateThetaW(leg->x, y, leg->z);
        leg->next_shoulderAngle = calculateThetaS(leg->x, y, leg->z);

        Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, y, leg->z);

        leg->move();
        leg->updateCoordinates(leg->x, y, leg->z);
        delay(1000);
    }
}

/**
 * moves the robot forward/backward to a given y coordinate.
 * @param y Y coordinate
 */
void InverseKinematics::moveY(Leg *leg, double y)
{
    leg->next_bodyAngle = calculateThetaH(leg->x, leg->z);
    leg->next_kneeAngle = calculateThetaW(leg->x, y, leg->z);
    leg->next_shoulderAngle = calculateThetaS(leg->x, y, leg->z);

    Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, y, leg->z);

    leg->move();
    leg->updateCoordinates(leg->x, y, leg->z);
    delay(1000);
}

void InverseKinematics::moveForward()
{
    for (Leg *leg : legs)
    {
        // in interpolate we have all the y and z positions needed to move a step forward
        // we also have the angles for every y and z position
        for (int j = 0; j < Constants::AMOUNT_POINTS; j++)
        {
            // move leg to this position
            // bodyAngle never changes
            leg->next_shoulderAngle = get<0>(leg->interpolation_angles[j]);
            leg->next_kneeAngle = get<1>(leg->interpolation_angles[j]);
            leg->move();
            delay(10);
        }
    }
}

/**
 * tilts the robot forwards or backwards
 * @param a tilting angle
 * @param direction. Enum (forward, backward). enum value = offset in the legs array. 0 moves the front legs, 2 moves the back legs
 */
void InverseKinematics::tilt(int a, Direction direction)
{
    double b = Constants::HALF_BODY * sin(radians(a));

    // move legs of direction (forward or backward)
    for (int i = 0; i < 3; i += 2)
    {
        Leg *leg = legs[direction + i];
        double z = leg->z + b;
        moveZ(leg, z);
    }

    Direction new_direction = static_cast<Direction>(direction ^ 1); // use xor to toggle 1/0
    for (int i = 0; i < 3; i += 2)
    {
        Leg *leg = legs[new_direction + i];
        double z = leg->z - b;
        moveZ(leg, z);
    }
}

void InverseKinematics::moveZ(Leg *leg, double z)
{
    leg->next_kneeAngle = calculateThetaW(leg->x, leg->y, z);
    leg->next_bodyAngle = calculateThetaH(leg->x, z);
    leg->next_shoulderAngle = calculateThetaS(leg->x, leg->y, z);

    Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, leg->y, z);

    leg->move();
    leg->updateCoordinates(leg->x, leg->y, z);
}
