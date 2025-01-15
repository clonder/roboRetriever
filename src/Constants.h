//
// Created by mathi on 29/12/2024.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants related to the body dimensions of the robot
namespace Constants {
    constexpr double LIMB = 10.0;
    // constexpr double LOWERLEG = 10.0;
    constexpr double SHOULDER = 6.1;

    constexpr double BASEHEIGHT = 5.0; // default z value
    constexpr double BASESIDELEGEXTEND = 0.5; // default y value
    constexpr double BASEFRONTELEGEXTEND = 5.5; // default x value

    constexpr int BODYDEFAULTANGLESERVO = 85;
    constexpr int SHOULDERDEFAULTANGLESERVO = 0; //Right side
    constexpr int LEFT_SHOULDERDEFAULTANGLESERVO = 180;
    constexpr int KNEEDEFAULTANGLESERVO = 0;
    constexpr int LEFT_KNEEDEFAULTANGLESERVO = 180;

    constexpr int BODYDEFAULTANGLE = 90;
    constexpr int SHOULDERDEFAULTANGLE = 85;
    constexpr int KNEEDEFAULTANGLE = 30;

    constexpr int WALKINGHEIGHT = 19;
    constexpr int AMOUNT_POINTS = 120;

}

#endif //CONSTANTS_H