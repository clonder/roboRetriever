# 🐾 Robo Retriever

---

## 🧾 Project Description

This project aims to develop **Robo Retriever**, a four-legged robotic dog controlled via Wi-Fi, to explore and demonstrate principles of computer architecture. Using a microcontroller, we will program the robot to execute movement commands, leveraging instruction cycles, control signals, and memory management techniques. By building and testing the robot, our team will gain hands-on experience with embedded systems, hardware interfacing, and real-time data processing.

---

## 📢 Project Information

- **References**:
  - [ESP32 Small Robot Dog on Instructables](https://www.instructables.com/ESP32-Small-Robot-Dog/)
  - [PCBWay Quadruped Robot Model Introduction](https://www.pcbway.com/project/shareproject/An_introduction_to_quadruped_robot_models_0f4aa139.html)

---

## 🎯 Objective

1. 🟢 **Ideal Project Result**: Robo Retriever is fully functional, performing a variety of movements (e.g., walking, sitting, and turning) via real-time commands from an interface. 
2. 🟠 **Acceptable Project Result**: Robo Retriever can walk.

---

## ✅ Tasks

### 3D Printing and Assembly

- **3D Design / Printing**: Design and print robot parts such as the frame and servo mounts.
- **Robot Frame Assembly**: Assemble the 3D-printed parts and verify the structural stability.

### Electronics Assembly

- **Wiring and Electronics Mounting**: Wire up the servos, ESP32, and other components.
- **Soldering**: Solder any necessary connections, particularly for servo control and power distribution.

### Programming - Wi-Fi and Server

- **ESP32 Wi-Fi Setup**: Set up ESP32 Wi-Fi configuration for connectivity.
- **WebSocket for Real-Time Control**: Enable real-time control of the robot through WebSocket.
- **Web Server and Command Handling**: Create a web server on the ESP32 to handle movement commands from the web interface.

### Programming - Interface

- **Design Web Control Interface**: Develop a user-friendly interface with buttons for movement commands.
- **Link Buttons to ESP32 Commands**: Map web interface commands to ESP32 actions.
- **Device Testing**: Test the interface on various devices to ensure smooth operation.

### Programming - Servo Control

- **Servo Setup**: Configure servos on the ESP32 and write movement functions.
- **Movement Functions**: Write code for complex actions (e.g., stand, sit, walk).
- **Servo Calibration**: Test and calibrate servos to ensure accurate movements.

---

## 📦 Components

| **Name**           | **Description**                          | **Amount** | **Price** | **Link** |
|--------------------|------------------------------------------|------------|-----------|----------|
| Servo Motors       | Motors for robot leg movement           | 12         | -         | [Amazon Link](https://www.amazon.de/-/en/dp/B09WQYPP17?_encoding=UTF8&th=1) |
| Timing Belts       | 25cm belts for leg motion               | 4          | -         | [Amazon Link](https://www.amazon.com/Cyrank-Printer-Accessories-Synchronous-MendelMax/dp/B0CH17YFQL) |
| ESP32              | Microcontroller for control             | 1          | -         | [Amazon Link](https://www.amazon.de/-/en/diymore-Nodemcu-Development-Bluetooth-2-ESP32/dp/B0D9BTQRYT?crid=32YV6FM3WYVIY&dib=eyJ2IjoiMSJ9.QiXWYXzpa1FokIOtgxrGsCHoZecushHbHQ_D6RX50XCFEzctudIA8kF2oZo_epvjxILp3SSG6mQtoVyBv3X7Xf_twmW03l7vtBQma3R9bC4sXjmjXu8G9gbiEsYg_NtC0G1IeViEGymfLHXESFVtAv6MrhichvuUsNnLkfuSPIukv7Zzq11qDf9g9XarQ17ilDsOgGdXcAwTmkXEUiLfbu2PliGYVUi8lGDHuM6PZnM.5NsBmvWBxq4K2A7yBaT-EiExZK41EnvYly1lmok3i6s&dib_tag=se&keywords=esp32&qid=1731348548&sprefix=esp32%2Caps%2C89&sr=8-3) |
| Battery (Akku)     | Powers ESP32 and servos                 | 1          | -         | [Amazon Link]() |
| Servo Shield       | Connects ESP32 to servos and distributes power | 1 | - | [Servo Shield Link](https://www.pcbway.com/project/shareproject/Multiple_Servo_Motor_Controller_Board_DOIT_ESP32_DEVKIT_V1_c9c8165e.html) |
| Micro USB Cable    | For flashing and programming ESP32      | 1          | -         | We have this |
| Non-slip Material  | Rubber or pads to keep feet stable      | 4          | -         | [Amazon Link]() |
| Filament           | 3D printing filament                    | 2kg        | -         | [Bambulab Link](https://eu.store.bambulab.com/en-ch) |
| Screws             | M3 screws in various lengths            | As needed  | -         | [Schraubenking.ch](https://www.schraubenking.ch/) |
| Ruthex Inserts     | Inserts for securing screws             | As needed  | -         | No need to buy |

---

## ⚙️ Equipment

- **3D Printer**: For prototyping parts
- **Soldering Kit**: For assembling electronic components
- **Basic Tools**: Screwdrivers, hex wrenches, and wire cutters
