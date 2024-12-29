//
// Created by mathi on 29/12/2024.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants related to the body dimensions of the robot
namespace Constants {
    constexpr double UPPERLEG = 10.0;
    constexpr double LOWERLEG = 10.0;
    constexpr double SHOULDER = 6.1;

    constexpr double BASEHEIGHT = 8.7;
    constexpr double BASESIDELEGEXTEND = 0.5;
    constexpr double BASEFRONTELEGEXTEND = 6.1;

    constexpr int BODYDEFAULTANGLESERVO = 90;
    constexpr int SHOULDERDEFAULTANGLESERVO = 90;
    constexpr int KNEEDEFAULTANGLESERVO = 0;
    constexpr int BODYDEFAULTANGLE = 90;
    constexpr int SHOULDERDEFAULTANGLE = 64;
    constexpr int KNEEDEFAULTANGLE = 51;
}

#endif //CONSTANTS_H