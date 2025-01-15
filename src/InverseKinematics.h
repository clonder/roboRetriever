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

        // Leg* legs[4] = {  &RightFront, &LeftFront, &LeftRear, &RightRear };
        Leg* legs[4] = {  &LeftFront, &RightFront, &RightRear, &LeftRear  };

    InverseKinematics() = default;

    // Elbow angle
    static double calculateThetaH(double x, double z);
    static double calculateThetaW(double x, double y, double z);
    static double calculateThetaS(double x, double y, double z);

    // Starting sequence. Sets all servos to desired default position
    void Start();

    void moveZ(double z);
    void moveY(double y);
    void moveY(Leg* leg, double y);
    void moveForward(int steps);

    // tilt the robot forwards or backwards. direction
    void tilt(double z, Direction direction);
};

#endif //INVERSEKINEMATICS_H
