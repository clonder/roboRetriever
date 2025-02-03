#include <Controller.h>
#include <InverseKinematics.h>
#include <string>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <vector>
#include "esp_task_wdt.h"

using namespace std;

const char *ssid = "Clonder";
const char *password = "1234567812";

AsyncWebServer server(80);
InverseKinematics ik;
bool wifiConnected = false;

void setup()
{
    // Setup serial
    Serial.begin(115200);
    while (!Serial)
    {
    }

    // Initialize watchdog timer
    esp_task_wdt_init(120, true);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000)
    {
        delay(1000);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        wifiConnected = true;
    }

    // Position servos into default position
    ik.Start();
    delay(1000);

    server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Test endpoint reached"); });

    server.on("/command", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("cmd")) {
            String command = request->getParam("cmd")->value();
            string data = command.c_str();
            // Split the commands by semicolon
            vector<string> commands;
            size_t pos = 0;
            while ((pos = data.find(";")) != string::npos) {
                commands.push_back(data.substr(0, pos));
                data.erase(0, pos + 1);
            }
            commands.push_back(data);

            // Execute each command
            for (const string& cmd : commands) {
                // command for moving along y-axis (for/backwards)
                if (cmd.find("y") != -1) {
                    int y = stoi(cmd.substr(1, cmd.length()));
                    ik.moveY(y);
                // command for walking
                } else if (cmd.find("w") != -1) {
                    int steps = stoi(cmd.substr(1, cmd.length()));
                    for (Leg *leg : ik.legs) {
                        if (leg->isHind) {
                            ik.moveY(leg, -10);
                        }
                        else {
                            ik.moveY(leg, -6);
                        }
                        leg->calculateCurve(); // saves array of points for walking interpolation
                        leg->calculateInterpolationAngles();                        
                    }
                    //ik.moveZ(Constants::WALKINGHEIGHT);
                    for (int i = 0; i < steps; i++) {
                        ik.moveForward();
                    }
                    esp_task_wdt_reset();
                // command for moving vertically
                } else if (cmd.find("z") != -1) {
                    int z = stoi(cmd.substr(1, cmd.length()));
                    if (z >= 6 && z <= 19) {
                        // Get current z of first leg, as all legs have same height;
                        int current_z = ik.legs[0]->z;
                        int step = z > current_z ? 1 : -1;
                        // Incrementally move z position
                        for (int i = current_z; i != z; i += step) {
                            ik.moveZ(i);
                            delay(10);
                        }
                    }
                // command for tilting forward
                } else if (cmd.find("ft") != -1) {
                    int a = stoi(cmd.substr(2, cmd.length()));
                    if (a >= -1000 && a <= 1000) { //TODO: adjust
                        ik.tilt(a, FORWARD);
                    }
                // command for tilting backward
                } else if (cmd.find("bt") != -1) {
                    int a = stoi(cmd.substr(2, cmd.length()));
                    if (a >= -100 && a <= 100) { //TODO: adjust
                        ik.tilt(a, BACKWARD);
                    }
                // command for resetting to starting position
                } else if (cmd.find("RESET") != -1) {
                    ik.Start();
                } else {
                    request->send(400, "text/plain", "Invalid command: " + String(cmd.c_str()));
                    return;
                }
                delay(500);
            }
            request->send(200, "text/plain", "Command sequence executed");
        } else {
            request->send(400, "text/plain", "No command sent");
        } });

    server.begin();
}

void loop()
{
    // Attempt to connect to WiFi until connected
    if (!wifiConnected)
    {
        WiFi.begin(ssid, password);
        unsigned long startAttemptTime = millis();

        // Wait for connection
        while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000)
        {
            delay(500);
        }

        if (WiFi.status() == WL_CONNECTED)
        {
            wifiConnected = true;
        }
        else
        {
            // If not connected, restart the attempt
            WiFi.disconnect();
            delay(1000);
        }
    }

    // Add a small delay to avoid flooding the Serial Monitor
    delay(1000);
}