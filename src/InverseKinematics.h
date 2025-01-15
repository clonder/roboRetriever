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
        Leg LeftRear = Leg(14, 12, 13, true);
        Leg RightRear = Leg(4, 2, 15, false);
        Leg LeftFront = Leg(25, 33, 32, true);
        Leg RightFront = Leg(5, 18, 19, false);

        Leg* legs[4] = {  &RightFront, &LeftRear, &LeftFront,  &RightRear };

    InverseKinematics() = default;

    static int calculateThetaH(double x, double z);
    static int calculateThetaW(double x, double y, double z);
    static int calculateThetaS(double x, double y, double z);

    // Starting sequence. Sets all servos to desired default position
    void Start();

    void moveZ(double z);
    void moveY(double y);
    void moveForward();

    // tilt the robot forwards or backwards. direction
    void tilt(int a, Direction direction);

    //vertically moves the given leg
    void moveZ(Leg* leg, double z);
};

#endif //INVERSEKINEMATICS_H
