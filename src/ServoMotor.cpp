//
// Created by Rahel Kempf on 01.01.2025.
//

#include "ServoMotor.h"

/**
 * rotates the servo and adds a little delay
 */
void ServoMotor::rotateServo(int angle) {
    servo.write(angle);
    delay(50);
};


/**
 * resets a servo to its default position
*/
void ServoMotor::resetPosition() {
    Serial.printf("defaultANgle is %d\n", defaultAngle);
   servo.write(defaultAngle);
};