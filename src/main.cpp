#include <Controller.h>
#include <InverseKinematics.h>
#include <string>
#include <WiFi.h>

using namespace std;
/*
// WiFi credentials
auto ssid = "ESP32-AP";
auto password = "quadruped";

// Set web server port number to 80
WiFiServer server(80);
ControllerInput controller_input;

// Setup before main thread is run
*/
InverseKinematics ik;

void setup()
{
    // Setup serial
    Serial.begin(115200);
    Serial.println("Starting setup sequence\n");

    // Position servos into default position
    ik.Start();
    delay(1000);
    /*
    // Console Output setup
    Serial.begin(115200);

    // Connect to Wi-Fi network with ssid and password
    WiFi.softAP(ssid, password);

    const IPAddress Ip = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(Ip);

    server.begin();
    */
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
        if (data.find("X") != -1)
        {
            int x = stoi(data.substr(1, data.length()));
            ik.RightFront.x = x;
        }
        else if (data.find("Y") != -1)
        {
            int y = stoi(data.substr(1, data.length()));
            ik.RightFront.y = y;
        }
        else if (data.find("Z") != -1)
        {
            int z = stoi(data.substr(1, data.length()));
            ik.RightFront.z = z;
        }
        else if (data.find("RESET") != -1)
        {
            ik.Start();
        }
        int new_thetaH = radiansDegrees(ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z));
        int new_thetaS = radiansDegrees(ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
        int new_thetaW = radiansDegrees(ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
        Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d\n", new_thetaW, new_thetaH, new_thetaS);
        Serial.printf("X = %f | Y = %f | Z = %f\n", ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
        ik.RightFront.rotateShoulder(new_thetaS);
        ik.RightFront.rotateKnee(new_thetaW);
        ik.RightFront.rotateBody(new_thetaH);
        Serial.println("Rotation complete");
        delay(2000);

        ik.LeftFront.rotateShoulder(new_thetaS);
        ik.LeftFront.rotateKnee(new_thetaW);
        ik.LeftFront.rotateBody(new_thetaH);

        ik.LeftRear.rotateShoulder(new_thetaS);
        ik.LeftRear.rotateKnee(new_thetaW);
        ik.LeftRear.rotateBody(new_thetaH);

        ik.RightRear.rotateShoulder(new_thetaS);
        ik.RightRear.rotateKnee(new_thetaW);
        ik.RightRear.rotateBody(new_thetaH);
    }
    /*
    ik.RightFront.x += 5;
    int new_thetaH = radiansDegrees(ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z));
    int new_thetaS = radiansDegrees(ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    int new_thetaW = radiansDegrees(ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d", new_thetaW, new_thetaH, new_thetaS);
    Serial.printf("X = %f | Y = %f | Z = %f", ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    ik.RightFront.rotateShoulder(new_thetaS);
    ik.RightFront.rotateKnee(new_thetaW);
    ik.RightFront.rotateBody(new_thetaH);
    Serial.println("Rotation complete first");
    delay(2000);
    ik.RightFront.x -= 5;
    new_thetaH = radiansDegrees(ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z));
    new_thetaS = radiansDegrees(ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    new_thetaW = radiansDegrees(ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d", new_thetaW, new_thetaH, new_thetaS);
    Serial.printf("X = %f | Y = %f | Z = %f", ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    ik.RightFront.rotateShoulder(new_thetaS);
    ik.RightFront.rotateKnee(new_thetaW);
    ik.RightFront.rotateBody(new_thetaH);
    Serial.println("Rotation complete second");
    delay(2000);
    */
    /*
    ik.RightFront.y += 5;
    int new_thetaH = radiansDegrees(ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z));
    int new_thetaS = radiansDegrees(ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    int new_thetaW = radiansDegrees(ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d", new_thetaW, new_thetaH, new_thetaS);
    Serial.printf("X = %f | Y = %f | Z = %f", ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    ik.RightFront.rotateShoulder(new_thetaS);
    ik.RightFront.rotateKnee(new_thetaW);
    ik.RightFront.rotateBody(new_thetaH);
    Serial.println("Rotation complete first");
    delay(2000);
    ik.RightFront.z += 5;
    new_thetaH = radiansDegrees(ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z));
    new_thetaS = radiansDegrees(ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    new_thetaW = radiansDegrees(ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d", new_thetaW, new_thetaH, new_thetaS);
    Serial.printf("X = %f | Y = %f | Z = %f", ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    ik.RightFront.rotateShoulder(new_thetaS);
    ik.RightFront.rotateKnee(new_thetaW);
    ik.RightFront.rotateBody(new_thetaH);
    Serial.println("Rotation complete second");
    delay(2000);
    ik.RightFront.y -= 5;
    new_thetaH = radiansDegrees(ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z));
    new_thetaS = radiansDegrees(ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    new_thetaW = radiansDegrees(ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d", new_thetaW, new_thetaH, new_thetaS);
    Serial.printf("X = %f | Y = %f | Z = %f", ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    ik.RightFront.rotateShoulder(new_thetaS);
    ik.RightFront.rotateKnee(new_thetaW);
    ik.RightFront.rotateBody(new_thetaH);
    Serial.println("Rotation complete second");
    delay(2000);
    ik.RightFront.z -= 5;
    new_thetaH = radiansDegrees(ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z));
    new_thetaS = radiansDegrees(ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    new_thetaW = radiansDegrees(ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z));
    Serial.printf("thetaW = %d | thetaH = %d | thetaS = %d", new_thetaW, new_thetaH, new_thetaS);
    Serial.printf("X = %f | Y = %f | Z = %f", ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    ik.RightFront.rotateShoulder(new_thetaS);
    ik.RightFront.rotateKnee(new_thetaW);
    ik.RightFront.rotateBody(new_thetaH);
    Serial.println("Rotation complete second");
    delay(2000);
    */
    /*
    ik.RightFront.rotateServo(&ik.RightFront.BodyServo, ik.RightFront.thetaH + 90);
    delay(500);
    ik.RightFront.rotateServo(&ik.RightFront.ShoulderServo, ik.RightFront.thetaS + 90);
    delay(500);
    ik.RightFront.rotateServo(&ik.RightFront.KneeServo, ik.RightFront.thetaW + 90);
    delay(5000);
    ik.RightFront.rotateServo(&ik.RightFront.BodyServo, ik.RightFront.thetaH - 90);
    delay(500);
    ik.RightFront.rotateServo(&ik.RightFront.ShoulderServo, ik.RightFront.thetaS - 90);
    delay(500);
    ik.RightFront.rotateServo(&ik.RightFront.KneeServo, ik.RightFront.thetaW - 90);
    Serial.print("HERE");
    delay(5000);
    */
    /*
    double thetaH = ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z);
    double thetaS = ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    double thetaW = ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    Serial.print(thetaH);
    Serial.print(thetaS);
    Serial.print(thetaW);
    delay(3000);
    ik.RightFront.z = ik.RightFront.z + 0.1;
    double new_thetaH = ik.calculateThetaH(ik.RightFront.x, ik.RightFront.z);
    double new_thetaS = ik.calculateThetaS(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    double new_thetaW = ik.calculateThetaW(ik.RightFront.x, ik.RightFront.y, ik.RightFront.z);
    Serial.print(new_thetaH);
    Serial.print(new_thetaS);
    Serial.print(new_thetaW);
    ik.RightFront.rotateServo(&ik.RightFront.BodyServo, new_thetaH);
    ik.RightFront.rotateServo(&ik.RightFront.ShoulderServo, new_thetaS);
    ik.RightFront.rotateServo(&ik.RightFront.KneeServo, new_thetaW);
    */

              // waits 15ms for the servo to reach the position
    //myservo.write(180);
    //#delay(200);             // waits 15ms for the servo to reach the position

    /*
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
    */
}
