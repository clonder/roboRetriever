//
// Created by mathi on 29/12/2024.
//
#ifndef LEG_H
#define LEG_H

#include <Constants.h>
#include <ESP32Servo.h>

enum Direction {
    FORWARD = 0,
    BACKWARD = 1,
};

/**
 * Holds all information related to one leg
 */
class Leg {
    public:
        bool isLeft;

        //current angles
        int kneeAngle = Constants::KNEEDEFAULTANGLESERVO;
        int shoulderAngle = Constants::SHOULDERDEFAULTANGLESERVO;
        int bodyAngle = Constants::BODYDEFAULTANGLESERVO;

        //desired angles
        int next_kneeAngle = Constants::KNEEDEFAULTANGLESERVO;
        int next_shoulderAngle = Constants::SHOULDERDEFAULTANGLESERVO;
        int next_bodyAngle = Constants::BODYDEFAULTANGLESERVO;

        // Positions
        double x = Constants::BASEFRONTELEGEXTEND;
        double y = Constants::BASESIDELEGEXTEND;
        double z = Constants::BASEHEIGHT;

        // Servos
        Servo BodyServo;
        Servo ShoulderServo;
        Servo KneeServo;

        // Walking
        std::tuple<double, double> curve_values[Constants::AMOUNT_POINTS];
        std::tuple<int, int> interpolation_angles[Constants::AMOUNT_POINTS]; // shoulder and knee angle

        /** Constructor for leg where pin numbers are passed for servo's
         * @param bodyServoPin
         * @param shoulderServoPin
         * @param kneeServoPin
         */
        Leg(int bodyServoPin, int shoulderServoPin, int kneeServoPin, bool isLeft)
        {
            this->isLeft = isLeft;

            calculateCurve(); // saves array of points for walking interpolation

            if (isLeft) {
                kneeAngle = Constants::LEFT_KNEEDEFAULTANGLESERVO;
                shoulderAngle = Constants::LEFT_SHOULDERDEFAULTANGLESERVO;

                next_kneeAngle = Constants::LEFT_KNEEDEFAULTANGLESERVO;
                next_shoulderAngle = Constants::LEFT_SHOULDERDEFAULTANGLESERVO;
            }

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
        void move();

        void rotateServo(Servo *servo, int angle);

        void updateCoordinates(double new_x, double new_y, double new_z);
        void updateAngles();

        void resetPosition();

        // calculates the points for the curve movement when walking
        void calculateCurve();

        // calculates the angles for each position that the leg needs to take
        void calculateInterpolationAngles();
};

#endif //LEG_H
