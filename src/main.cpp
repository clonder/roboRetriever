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
        // move leg forward
        if (data.find("y") != -1)
        {
            int y = stoi(data.substr(1, data.length()));
            ik.moveY(y);
        }
        // walk forward
        else if (data.find("w") != -1)
        {
            int steps = stoi(data.substr(1, data.length()));
            ik.moveForward(steps);
        }
        // move up and down
        else if (data.find("z") != -1)
        {
            int z = stoi(data.substr(1, data.length()));
            if (z >= 6 | z <= 19) {
                ik.moveZ(z);
            }
        }
        // tilt forward
        else if (data.find("ft") != -1)
        {
            int z = stoi(data.substr(2, data.length()));
            if (z >= 6 | z <= 19) {
                ik.tilt(z, FORWARD);
            }
        }
        // tilt backward
        else if (data.find("bt") != -1)
        {
            int z = stoi(data.substr(2, data.length()));
            if (z >= 6 | z <= 19) {
                ik.tilt(z, BACKWARD);
            }
        }
        else if (data.find("RESET") != -1)
        {
            ik.Start();
        }
    }
}
