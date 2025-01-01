//
// Created by Rahel Kempf on 01.01.2025.
//

#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <ESP32Servo.h>

class ServoMotor {
public:
    ServoMotor(int pin, int default_angle, int physical_angle) {
        controlPin = pin;
        defaultAngle = default_angle;
        defaultPhysicalAngle = physical_angle;

        // TODO: evtl. change
        minPos = 0;
        maxPos = 180;
        servo.setPeriodHertz(50);
        Serial.println("Servo Motor is being attached ... \n");
        servo.attach(controlPin, 500, 2400);

        // TODO: only set angle after changing it ...
        angleDegrees = servo.read();
        // previousDegrees = angleDegrees;
    }

    uint8_t controlPin;

    // Angle
    int16_t angleDegrees;
    // int16_t previousDegrees; previous degrees

    uint16_t maxPos;
    uint16_t minPos;

    //TODO: Calibration
    Servo servo; // the actual servo

    int16_t defaultAngle; // default angle of the servo
    int16_t defaultPhysicalAngle; // default angle of the body part attached to the servo
    /**
    * rotates the servo and adds a little delay
    */
    void rotateServo(int angle);

    /**
     * resets a servo to its default position
    */
    void resetPosition();

};

#endif //SERVOMOTOR_H
