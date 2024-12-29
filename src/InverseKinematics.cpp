#include "InverseKinematics.h"

#include <Arduino.h>
#include <cmath>
#include <Constants.h>



/**
 * Starting sequence. Sets all servos to desired default position
 */
void InverseKinematics::Start()
{
    RightFront.x = Constants::BASEFRONTELEGEXTEND;
    RightFront.y = Constants::BASESIDELEGEXTEND;
    RightFront.z = Constants::BASEHEIGHT;

    RightFront.rotateServo(&RightFront.BodyServo, Constants::BODYDEFAULTANGLESERVO);
    delay(500);
    RightFront.rotateServo(&RightFront.ShoulderServo, Constants::SHOULDERDEFAULTANGLESERVO);
    delay(500);
    RightFront.rotateServo(&RightFront.KneeServo, Constants::KNEEDEFAULTANGLESERVO);
    delay(500);
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
    const double p1 = pow(Constants::UPPERLEG, 2) + (pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2)) - pow(Constants::LOWERLEG, 2);
    const double p2 = 2 * Constants::UPPERLEG * sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2));
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
    const double p1 = pow(Constants::UPPERLEG, 2) + pow(Constants::LOWERLEG, 2) - (pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2));
    const double p2 = 2 * Constants::UPPERLEG * Constants::LOWERLEG;
    const double thetaW = acos(p1 / p2);
    return thetaW;
}

/**
 * Converts radians to degrees
 * @param angle Angle to be converted
 * @return converted angle
 */
int radiansDegrees(const double angle)
{
    const int degrees = static_cast<int>(angle * 180 / PI);
    return degrees;
}

/**
 * Converts degrees to angle
 * @param angle Angle to be converted
 * @return converted angle
 */
double degreesRadians(const int angle)
{
    const double radians = angle * PI / 180;
    return radians;
}





