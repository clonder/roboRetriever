//
// Created by mathi on 08/12/2024.
//

#include "InverseKinematics.h"

#include <Arduino.h>
#include <cmath>

float InverseKinematics::calculateThetaH()
{
    float r0 = sqrt(pow(extend, 2) + pow(height, 2) - pow(SHOULDER, 2));
    thetaH = atan(extend / height) - (PI - atan(r0 / SHOULDER));
}

float InverseKinematics::calculateThetaS()
{

}

float InverseKinematics::calculateThetaW()
{

}

float InverseKinematics::calculateNewHeight()
{

}

float InverseKinematics::calculateNewLegExtend()
{

}





