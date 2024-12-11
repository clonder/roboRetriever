//
// Created by mathi on 08/12/2024.
//

#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H
// Constants related to the body dimensions of the robot
// Upper leg length
float UPPERLEG;
// Lower leg length
float LOWERLEG;
// Shoulder length
float SHOULDER;
// Base height of robot at starting condition
float BASEHEIGHT;
// Base length extend from body to leg
float BASELEGEXTEND;




class InverseKinematics {
    public:
        float thetaH;
        float thetaW;
        float ThetaS;

        float height;
        float extend;

    // Elbow angle
    float calculateThetaH();
    float calculateThetaW();
    float calculateThetaS();

    float calculateNewHeight();
    float calculateNewLegExtend();
};



#endif //INVERSEKINEMATICS_H
