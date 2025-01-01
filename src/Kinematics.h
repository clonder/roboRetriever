//
// Created by Rahel Kempf on 01.01.2025.
//

#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <Arduino.h>
#include "Leg.h"

class Kinematics {

    public:
        Kinematics() = default;

        // calculates all relevant motor angles to move a leg up and down
        void calculateVerticalMovement(float new_height, int *new_kneeAngle, int *new_shoulderAngle);
};

#endif //KINEMATICS_H
