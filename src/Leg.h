//
// Created by mathi on 29/12/2024.
//
#ifndef LEG_H
#define LEG_H

#include <Constants.h>
#include <ServoMotor.h>

/**
 * Holds all information related to one leg
 */
class Leg
{
    public:
        // Actual Positions of the Leg
        float x = Constants::BASEFRONTELEGEXTEND;
        float y = Constants::BASESIDELEGEXTEND;
        float z = Constants::BASEHEIGHT;

        float previousX = Constants::BASEFRONTELEGEXTEND;
        float previousY = Constants::BASESIDELEGEXTEND;
        float previousZ = Constants::BASEHEIGHT;

        // Servos
        ServoMotor BodyServo;
        ServoMotor ShoulderServo;
        ServoMotor KneeServo;

        /** Constructor for leg where pin numbers are passed for servo's
         * @param bodyServoPin
         * @param shoulderServoPin
         * @param kneeServoPin
         */
        Leg(int bodyServoPin, int shoulderServoPin, int kneeServoPin)
            : BodyServo(bodyServoPin, Constants::BODYDEFAULTANGLESERVO, Constants::BODYDEFAULTANGLE),
            ShoulderServo(shoulderServoPin, Constants::SHOULDERDEFAULTANGLESERVO, Constants::SHOULDERDEFAULTANGLE),
            KneeServo(kneeServoPin, Constants::KNEEDEFAULTANGLESERVO, Constants::KNEEDEFAULTANGLE) {}

        /**
        * Rotate knee servo
        * @param angle
        */
        void rotateKnee(int angle);

        /**
        * Rotate shoulder servo
        * @param angle
        */
        void rotateShoulder(int angle);

        /**
        * Rotate body servo
        * @param angle
        */
        void rotateBody(int angle);

        /**
         * Move the leg
         */
        void moveVertical(int shoulderAngle, int kneeAngle);

        /**
         * updates leg coordinates
        */
        void updateCoordinates(double new_x, double new_y, double new_z);

        /**
         * resets a leg to its default position
        */
        void resetPosition();
};

#endif //LEG_H
