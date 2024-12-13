//
// Created by mathi on 08/12/2024.
//

#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H
#include <Arduino.h>
#include <math.h>
// Constants related to the body dimensions of the robot
// Upper leg length
float UPPERLEG;
// Lower leg length
float LOWERLEG;
// Shoulder length
float SHOULDER;
// Base height of robot at starting condition
float BASEHEIGHT;
// Base length extend from body to leg from side
float BASESIDELEGEXTEND;
// Base length extend from body to leg from front
float BASEFRONTELEGEXTEND;

class Leg
{
    public:
        double thetaH = PI / 2;
        double thetaW = PI / 2;
        double ThetaS = PI / 2;

        double x = BASEFRONTELEGEXTEND;
        double y = BASESIDELEGEXTEND;
        double z = BASEHEIGHT;
};

class InverseKinematics {
    public:
        Leg LeftRear;
        Leg RightRear;
        Leg LeftFront;
        Leg RightFront;

    // Elbow angle
    static double calculateThetaH(double x, double z);
    static double calculateThetaW(double x, double y, double z);
    static double calculateThetaS(double x, double y, double z);

    double calculateNewHeight();
    double calculateNewLegExtend();

    // Interpolation of the movement
    double interpolate();
};



#endif //INVERSEKINEMATICS_H
