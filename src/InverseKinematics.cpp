#include "InverseKinematics.h"

#include <Arduino.h>
#include <cmath>
#include <Constants.h>

using namespace std;

/**
 * Starting sequence. Sets all servos to desired default position
 */
void InverseKinematics::Start()
{
  for (Leg* leg : legs) {
    leg->resetPosition();
  }
}

/**
 * Calculates the angle theta_H. Angle between the main body and the tilt of the leg in front view
 * @param x X coordinate
 * @param z Z coordinate
 * @return thetaH Angle in radians
 */
double InverseKinematics::calculateThetaH(double x,  double z)
{
    const double phi = atan(x / z);
    const double alpha_2 = acos(Constants::SHOULDER / sqrt(pow(x, 2) + pow(z, 2)));
    const double thetaH = phi - PI / 2 + alpha_2;

	// leg->next_bodyAngle = -1 * new_thetaH + Constants::BODYDEFAULTANGLESERVO;
    return -1 * degrees(thetaH) + Constants::BODYDEFAULTANGLESERVO;;
}

/**
 * Calculates the angle thetaS. Angle between the shoulder and leg
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @return thetaS Angle in radians
 */
double InverseKinematics::calculateThetaS(const double x, const double y, const double z)
{
    const double p1 = pow(Constants::LIMB, 2) + (pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2)) - pow(Constants::LIMB, 2);
    const double p2 = 2 * Constants::LIMB * sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2));
    const double phi = atan(y / sqrt(pow(x, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2)));
    const double thetaS = acos(p1 / p2) - phi;
//        leg->next_shoulderAngle = -1 * (new_thetaS - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;
    return  -1 * (degrees(thetaS) - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;;
}

/**
 * Calculates the angle thetaW. Angle between the upper leg and lower leg
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @return thetaW Angle in radians
 */
double InverseKinematics::calculateThetaW(const double x, const double y, const double z)
{
    const double p1 = pow(Constants::LIMB, 2) + pow(Constants::LIMB, 2) - (pow(x, 2) + pow(y, 2) + pow(z, 2) - pow(Constants::SHOULDER, 2));
    const double p2 = 2 * Constants::LIMB * Constants::LIMB;
    const double thetaW = acos(p1 / p2);
//       leg->next_kneeAngle = new_thetaW - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
    return degrees(thetaW) - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
}

void InverseKinematics::moveZ(double z) {
     for (Leg* leg : legs) {
        leg->next_kneeAngle = calculateThetaW(leg->x, leg->y, z);
        leg->next_bodyAngle = calculateThetaH(leg->x, z);
        leg->next_shoulderAngle = calculateThetaS(leg->x, leg->y, z);

//        Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", l, new_thetaH, new_thetaS);
        Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, leg->y, z);

        leg->move();
        leg->updateCoordinates(leg->x, leg->y, z);

        Serial.println("Vertical Movement complete");
     }
}

void InverseKinematics::moveY(double y) {
     for (Leg* leg : legs) {
        leg->next_bodyAngle = calculateThetaH(leg->x, leg->z);
        leg->next_kneeAngle = calculateThetaW(leg->x, y, leg->z);
        leg->next_shoulderAngle = calculateThetaS(leg->x, y, leg->z);

//        Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", new_thetaW, new_thetaH, new_thetaS);
        Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, y, leg->z);

        leg->move();
        leg->updateCoordinates(leg->x, y, leg->z);
        delay(1000);
     }
}

void InverseKinematics::moveForward(int steps) {
  // 1. all legs should be walking height (at least 10cm) so upper leg can move freely
  moveZ(Constants::WALKINGHEIGHT);

  for (int i = 0; i < steps; i++) {
    for (Leg* leg : legs) {
      	// in interpolate we have all the y and z positions needed to move a step forward
        // we also have the angles for every y and z position
        for (int i = 0; i < Constants::AMOUNT_POINTS; i++) {
        	// move leg to this position
            // bodyAngle never changes
    		leg->next_shoulderAngle = get<0>(leg->interpolation_angles[i]);
    		leg->next_kneeAngle = get<1>(leg->interpolation_angles[i]);
            leg->move();
            delay(10);
        }
    }
  }
}

/**
* tilts the robot forwards or backwards
* @param Z new z coordinate
* @param direction. Enum (forward, backward). enum value = offset in the legs array. 0 moves the front legs, 2 moves the back legs
*/
void InverseKinematics::tilt(double z, Direction direction) {
    for (int i = 0; i < 3; i+=2) {
        Leg* leg = legs[direction + i];

        int new_thetaH = degrees(calculateThetaH(leg->x, z));
        int new_thetaS = degrees(calculateThetaS(leg->x, leg->y, z));
        int new_thetaW = degrees(calculateThetaW(leg->x, leg->y, z));

        leg->next_kneeAngle = new_thetaW - Constants::KNEEDEFAULTANGLE + Constants::KNEEDEFAULTANGLESERVO;
        leg->next_bodyAngle = -1 * new_thetaH + Constants::BODYDEFAULTANGLESERVO;
        leg->next_shoulderAngle = -1 * (new_thetaS - Constants::SHOULDERDEFAULTANGLE) + Constants::SHOULDERDEFAULTANGLESERVO;

        Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", new_thetaW, new_thetaH, new_thetaS);
        Serial.printf("X = %f | Y = %f | Z = %f\n", leg->x, leg->y, z);

        leg->move();
        leg->updateCoordinates(leg->x, leg->y, z);

        Serial.println("Tilt complete");
    }
}








