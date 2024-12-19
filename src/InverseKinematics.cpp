#include "InverseKinematics.h"

#include <Arduino.h>
#include <cmath>

/** Calculates the angle theta_H. Angle between the main body and the tilt of the leg in front view
 * @param x X coordinate
 * @param z Z coordinate
 * @return theta_H
 */
double InverseKinematics::calculateThetaH(const double x, const double z)
{
    const double p1 = atan(z / x);
    const double  p2 = asin(1 - pow(SHOULDER, 2)/ (pow(x, 2) * pow(z, 2)));
    const double thetaH = p1 - PI / 2 + p2;
    return thetaH;
}

double InverseKinematics::calculateThetaS(const double x, const double y, const double z)
{
    const float p1 = pow(UPPERLEG, 2) + pow(z, 2) - pow(LOWERLEG, 2);
    const float p2 = 2 * UPPERLEG * z;
    const float beta = acos(p1 / p2);

    const float p3 = sqrt(pow(x, 2) + pow(z, 2) - pow(SHOULDER, 2));

    const float thetaS = beta - atan(x / p3);
    return thetaS;
}

double InverseKinematics::calculateThetaW(const double x, const double y, const double z)
{
    const float p1 = pow(UPPERLEG, 2) + pow(LOWERLEG, 2) - (pow(y, 2) + pow(x, 2) + pow(z, 2) - pow(SHOULDER, 2));
    const float p2 = 2 * UPPERLEG * LOWERLEG;
    const float thetaW = acos(p1 / p2);
    return thetaW;
}

float InverseKinematics::calculateNewHeight()
{

}

float InverseKinematics::calculateNewLegExtend()
{

}





