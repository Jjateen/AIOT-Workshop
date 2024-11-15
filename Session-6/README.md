# Arduino Light Tracking Robot

This project, created by **[Vasu Agarwal](https://github.com/Vasu007-tech)**, **Lakshya Ojha**, **Prayag Srivastava**, and **Muffaddal Saify**, is an Arduino-based Light Tracking Robot that autonomously detects and follows light sources using Light Dependent Resistors (LDRs). The project was exhibited at the IoT Exhibition for the **Introduction to IoT (ECL 104)** course, under the guidance of **Dr. Rashmi Ranjan Kumar**.

## Table of Contents
- [System Overview](#system-overview)
- [Components Required](#components-required)
- [Circuit Diagram](#circuit-diagram)
- [Assembly and Setup](#assembly-and-setup)
- [Code and Operation](#code-and-operation)
- [Final Setup Images](#final-setup-images)
- [Applications](#applications)
- [Future Enhancements](#future-enhancements)

---

### System Overview

The Light Tracking Robot consists of three main modules:
1. **Sensing Module**: Uses LDRs to detect ambient light.
2. **Control Module**: An Arduino microcontroller processes sensor data and determines the movement direction.
3. **Actuation Module**: An H-bridge motor driver (L298N) controls four DC motors to drive the robot.

### Components Required

- Arduino Uno
- L298N Motor Driver
- Light Dependent Resistors (LDRs) - 3
- DC Motors - 4
- Jumper Wires and Breadboard
- Power Source (Battery Pack)

### Circuit Diagram

![Circuit Diagram](CIRCUIT%20DIAGRAM.jpg)

The above diagram shows the connections required to set up the light-tracking robot. Ensure all connections are secure, especially for the motor driver and LDR sensors.

### Assembly and Setup

1. **Attach the LDR Sensors**: Place LDRs on the front left, center, and right of the robot. These sensors help detect light intensity and guide the robot towards the brightest light source.
2. **Set Up the Motor Driver and Motors**: Connect the L298N driver to the motors and Arduino. The motor driver will receive signals from the Arduino to control motor speed and direction.

### Code and Operation

Upload the following code to the Arduino. The code enables the robot to detect the light source direction using LDRs and control the motors to move towards it.

```cpp
#include <AFMotor.h> 
#define L1 A0 
#define M1 A1
#define R1 A2

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
  Serial.begin(9600);
  pinMode(L1, INPUT);
  pinMode(M1, INPUT);
  pinMode(R1, INPUT);
}

void loop() {
  int LSensor = digitalRead(L1);
  int MSensor = digitalRead(M1);
  int RSensor = digitalRead(R1);

  Serial.print("LSensor: ");
  Serial.println(LSensor);
  Serial.print("MSensor: ");
  Serial.println(MSensor);
  Serial.print("RSensor: ");
  Serial.println(RSensor);

  if ((LSensor == 0) && (MSensor == 0) && (RSensor == 0)) { 
    // Move Forward
    motor1.setSpeed(120);
    motor1.run(FORWARD);
    motor2.setSpeed(120);
    motor2.run(FORWARD);
    motor3.setSpeed(120);
    motor3.run(FORWARD);
    motor4.setSpeed(120);
    motor4.run(FORWARD);
  } else if ((LSensor == 0) && (MSensor == 0) && (RSensor == 1)) {
    // Turn Left
    motor1.setSpeed(150);
    motor1.run(BACKWARD);
    motor2.setSpeed(150);
    motor2.run(BACKWARD);
    motor3.setSpeed(150);
    motor3.run(FORWARD);
    motor4.setSpeed(150);
    motor4.run(FORWARD);
  } else if ((LSensor == 1) && (MSensor == 0) && (RSensor == 0)) {
    // Turn Right
    motor1.setSpeed(150);
    motor1.run(FORWARD);
    motor2.setSpeed(150);
    motor2.run(FORWARD);
    motor3.setSpeed(150);
    motor3.run(BACKWARD);
    motor4.setSpeed(150);
    motor4.run(BACKWARD);
  } else if ((LSensor == 1) && (MSensor == 1) && (RSensor == 1)) {
    // Stop
    motor1.setSpeed(0);
    motor1.run(RELEASE);
    motor2.setSpeed(0);
    motor2.run(RELEASE);
    motor3.setSpeed(0);
    motor3.run(RELEASE);
    motor4.setSpeed(0);
    motor4.run(RELEASE);
  }
}
```

> **Note**: Before uploading, install the required libraries. Remove the yellow jumper cap from the motor driver before uploading.

### Final Setup Images

Refer to the images below for guidance on how the final setup should look.

#### Image 1: Final Setup - Top View
![Final Setup - Top View](FINAL%20IMAGE%20SETUP%20-%201.jpg)

#### Image 2: Final Setup - Side View
![Final Setup - Side View](FINAL%20IMAGE%20SETUP%20-%202.jpg)

These images provide a reference for assembling the robot components, including the LDR placement, motor driver setup, and sensor positioning.

### Applications

The Light Tracking Robot has potential applications across various fields:
1. **Solar Panel Alignment**: Track the sun's position to optimize energy capture.
2. **Smart Lighting**: Dynamically adjust indoor lighting for energy savings.
3. **Autonomous Navigation**: Enable robots to follow light sources for navigation.

### Future Enhancements

Future improvements could include:
- Adding obstacle avoidance sensors for improved navigation.
- Using more refined light-tracking algorithms for smoother movements.
