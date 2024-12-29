//
// Created by mathi on 08/12/2024.
//

#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H
#include <Arduino.h>
#include <Leg.h>


/**
 * Contains all functions, variables related to the inverse kinematics
 */
class InverseKinematics {
    // Leg classes to control each leg individually
    public:
        //Leg LeftRear;
        //Leg RightRear;
        //Leg LeftFront;
        Leg RightFront = Leg(25, 26, 27);

    InverseKinematics() = default;

    // Elbow angle
    static double calculateThetaH(double x, double z);
    static double calculateThetaW(double x, double y, double z);
    static double calculateThetaS(double x, double y, double z);

    // Interpolation of the movement
    double interpolate();

    // Starting sequence. Sets all servos to desired default position
    void Start();
};

int radiansDegrees(double angle);
double degreesRadians(int angle);


#endif //INVERSEKINEMATICS_H
