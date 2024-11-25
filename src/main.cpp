cd #include <WiFi.h>
#include <Controller.h>
#include <string>

using namespace std;

// WiFi credentials
auto ssid = "ESP32-AP";
auto password = "quadruped";

// Set web server port number to 80
WiFiServer server(80);
ControllerInput controller_input;

// Setup before main thread is run
void setup()
{
    // Console Output setup
    Serial.begin(115200);

    // Connect to Wi-Fi network with ssid and password
    WiFi.softAP(ssid, password);

    const IPAddress Ip = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(Ip);

    server.begin();
}

// Main thread where programm runs
void loop()
{
    WiFiClient client = server.available();

    // Check if new client is connected
    if (client)
    {
        string currentLine;
        while (client.connected())
        {
            while (client.available())
            {
                // Read client input
                char c = client.read();
                Serial.write(c);

                // If end of message
                if (c == '\n')
                {
                    // Set input
                    string output = controller_input.readInput(currentLine);
                    currentLine = "";
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }
        // Close the connection
        client.stop();
    }
}
