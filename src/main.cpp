#include <Controller.h>
#include <InverseKinematics.h>
#include <string>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <vector>
#include "esp_task_wdt.h"

using namespace std;

const char* ssid = "Clonder";
const char* password = "1234567812";

AsyncWebServer server(80);
InverseKinematics ik;
bool wifiConnected = false;

void setup()
{
    // Setup serial
    Serial.begin(115200);
    while (!Serial) {
    }

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(1000);
    }

    if (WiFi.status() == WL_CONNECTED) {
        wifiConnected = true;
    }

    // Position servos into default position
    ik.Start();
    delay(1000);

    server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Test endpoint reached");
    });

    server.on("/command", HTTP_GET, [](AsyncWebServerRequest *request){
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
                if (cmd.find("y") != -1) {
                    int y = stoi(cmd.substr(1, cmd.length()));
                    ik.moveY(y);
                } else if (cmd.find("w") != -1) {
                    int steps = stoi(cmd.substr(1, cmd.length()));
                    
                    // Break down the movement into smaller steps
                    const int stepIncrement = 1; // Adjust this value as needed
                    int remainingSteps = steps;
                    
                    while (remainingSteps > 0) {
                        esp_task_wdt_reset();
                        int currentStep = min(stepIncrement, remainingSteps);
                        ik.moveForward(currentStep);
                        remainingSteps -= currentStep;
                        
                        // Yield control to reset the watchdog timer
                        
                    }
                    esp_task_wdt_reset();
                } else if (cmd.find("z") != -1) {
                    int z = stoi(cmd.substr(1, cmd.length()));
                    if (z >= 6 && z <= 19) {
                        ik.moveZ(z);
                    }
                } else if (cmd.find("ft") != -1) {
                    int z = stoi(cmd.substr(2, cmd.length()));
                    if (z >= 2 && z <= 19) {
                        ik.tilt(z, FORWARD);
                    }
                } else if (cmd.find("bt") != -1) {
                    int z = stoi(cmd.substr(2, cmd.length()));
                    if (z >= 3 && z <= 19) {
                        ik.tilt(z, BACKWARD);
                    }
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
        }
    });

    server.begin();
}

void loop()
{
    // Attempt to connect to WiFi until connected
    if (!wifiConnected) {
        WiFi.begin(ssid, password);
        unsigned long startAttemptTime = millis();

        // Wait for connection
        while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
            delay(500);
        }

        if (WiFi.status() == WL_CONNECTED) {
            wifiConnected = true;
        } else {
            // If not connected, restart the attempt
            WiFi.disconnect();
            delay(1000);
        }
    }

    // Add a small delay to avoid flooding the Serial Monitor
    delay(1000);
}