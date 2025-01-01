//
// Created by Rahel on 01.01.2025.
//

#ifndef ROBOT_H
#define ROBOT_H

#include <Leg.h>
#include "Kinematics.h"

class Robot {
    // Leg classes to control each leg individually
    public:
        // Leg legs[4] = {Leg(14, 12, 13), Leg(4, 2, 15), Leg(25, 33, 32), Leg(5, 18, 19)};
        Leg legs[1] = {Leg(4, 2, 15)};

        Kinematics kinematics = Kinematics();

        // Leg LeftRear = Leg(14, 12, 13);
        // Leg RightRear = Leg(4, 2, 15);
        // Leg LeftFront = Leg(25, 33, 32);
        // Leg RightFront = Leg(5, 18, 19);

        // Starting sequence. Sets all servos to desired default position
        void Start();

        void moveVertical(int movement);

};



#endif //ROBOT_H
