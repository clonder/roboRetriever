#include <Controller.h>
#include <InverseKinematics.h>
#include <string>
#include <WiFi.h>

using namespace std;
InverseKinematics ik;

void setup()
{
    // Setup serial
    Serial.begin(115200);
    Serial.println("Starting setup sequence\n");

    // Position servos into default position
    ik.Start();
    delay(1000);

    Serial.println("Finished setup sequence\n");
}

// Main thread where programm runs
void loop()
{
    if (Serial.available())
    {
        String data_1 = Serial.readStringUntil('\n');
        Serial.println(data_1);
        string data = data_1.c_str();
        // if (data.find("X") != -1)
        // {
        //     int x = stoi(data.substr(1, data.length()));
        //     ik.RightFront.x = x;
        // }
        // else if (data.find("Y") != -1)
        // {
        //     int y = stoi(data.substr(1, data.length()));
        //     ik.RightFront.y = y;
        // }
        if (data.find("Z") != -1)
        {
            int z = stoi(data.substr(1, data.length()));
            // ik.RightFront.z = z;
            ik.moveVertical(z);
        }
        else if (data.find("RESET") != -1)
        {
            ik.Start();
        }
        // int new_thetaH = radiansDegrees(ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z));
        // int new_thetaS = radiansDegrees(ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
        // int new_thetaW = radiansDegrees(ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
        // Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", new_thetaW, new_thetaH, new_thetaS);
        // Serial.printf("X = %f | Y = %f | Z = %f\n", ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
        // ik.RightFront.rotateShoulder(new_thetaS);
        // ik.RightFront.rotateKnee(new_thetaW);
        // ik.RightFront.rotateBody(new_thetaH);
        // Serial.println("Rotation complete");
        // delay(2000);
        //
        // ik.LeftFront.rotateShoulder(new_thetaS);
        // ik.LeftFront.rotateKnee(new_thetaW);
        // ik.LeftFront.rotateBody(new_thetaH);
        //
        // ik.LeftRear.rotateShoulder(new_thetaS);
        // ik.LeftRear.rotateKnee(new_thetaW);
        // ik.LeftRear.rotateBody(new_thetaH);
        //
        // ik.RightRear.rotateShoulder(new_thetaS);
        // ik.RightRear.rotateKnee(new_thetaW);
        // ik.RightRear.rotateBody(new_thetaH);
    }
}
