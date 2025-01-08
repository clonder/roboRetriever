//
// Created by mathi on 29/12/2024.
//
#ifndef LEG_H
#define LEG_H

#include <Constants.h>
#include <ESP32Servo.h>


/**
 * Holds all information related to one leg
 */
class Leg
{
    public:
        // Positions
        double x = Constants::BASEFRONTELEGEXTEND;
        double y = Constants::BASESIDELEGEXTEND;
        double z = Constants::BASEHEIGHT;

        // Servos
        Servo BodyServo;
        Servo ShoulderServo;
        Servo KneeServo;

        /** Constructor for leg where pin numbers are passed for servo's
         * @param bodyServoPin
         * @param shoulderServoPin
         * @param kneeServoPin
         */
        Leg(int bodyServoPin, int shoulderServoPin, int kneeServoPin)
        {
            BodyServo.setPeriodHertz(50);
            BodyServo.attach(bodyServoPin, 500, 2400);

            ShoulderServo.setPeriodHertz(50);
            ShoulderServo.attach(shoulderServoPin, 500, 2400);

            KneeServo.setPeriodHertz(50);
            KneeServo.attach(kneeServoPin, 500, 2400);
        }

        /**
        * Rotate knee servo
        * @param angle
        */
        void rotateKnee(int angle, bool isRight);

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
         * Move the leg after modifying leg coordinates inplace.
         */
        void move(double thetaH, double thetaS, double thetaW);

        void rotateServo(Servo *servo, int angle);
};



#endif //LEG_H
