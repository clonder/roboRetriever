#include <Robot.h>
#include <string>
#include <WiFi.h>

using namespace std;
Robot quadruped;

void setup()
{
    // Setup serial
    Serial.begin(115200);
    Serial.printf("Starting setup sequence\n");

    // Position servos into default position
    // quadruped.Start();
    // delay(1000);
    Serial.printf("Finished setup sequence\n");
}

// Main thread where program runs
void loop()
{
    if (Serial.available())
    {
        String data_1 = Serial.readStringUntil('\n');
        Serial.println(data_1);
        string data = data_1.c_str();
        if (data.find("UP") != -1)
        {
            int up = stoi(data.substr(1, data.length()));
            quadruped.moveVertical(up);
        }
        else if (data.find("DOWN") != -1) {
            int down = stoi(data.substr(1, data.length())) * -1; //negative number
            quadruped.moveVertical(down);
        }
        else if (data.find("RESET") != -1)
        {
            quadruped.Start();
        }
    }
}
