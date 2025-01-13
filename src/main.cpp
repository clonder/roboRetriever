#include <Controller.h>
#include <InverseKinematics.h>
#include <string>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <vector>

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
        ; // Wait for serial port to connect. Needed for native USB port only
    }

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
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
                    ik.moveForward(steps);
                } else if (cmd.find("z") != -1) {
                    int z = stoi(cmd.substr(1, cmd.length()));
                    if (z >= 6 && z <= 19) {
                        ik.moveZ(z);
                    }
                } else if (cmd.find("ft") != -1) {
                    int z = stoi(cmd.substr(2, cmd.length()));
                    if (z >= 6 && z <= 19) {
                        ik.tilt(z, FORWARD);
                    }
                } else if (cmd.find("bt") != -1) {
                    int z = stoi(cmd.substr(2, cmd.length()));
                    if (z >= 6 && z <= 19) {
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
        }
    }

    // Add a small delay to avoid flooding the Serial Monitor
    delay(1000);
}