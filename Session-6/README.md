# IoT-Based Light Tracking Robot

This project, created by **[Vasu Agarwal](https://github.com/Vasu007-tech)**, **Lakshya Ojha**, **Prayag Srivastava**, and **Muffaddal Saify**, is an IoT-enabled Light Tracking Robot that autonomously detects and follows light sources using Light Dependent Resistors (LDRs). The system leverages an Arduino microcontroller and various sensors to track light while collecting environmental data such as temperature and humidity. This project was exhibited at the IoT Exhibition for the **Introduction to IoT (ECL 104)** course, under the guidance of **Dr. Rashmi Ranjan Kumar**.

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

The Light Tracking Robot consists of four main modules:
1. **Sensing Module**: Uses LDRs to detect ambient light and a DHT11 sensor for temperature and humidity.
2. **Control Module**: An Arduino microcontroller processes the sensor data and determines the movement direction.
3. **Actuation Module**: An H-bridge motor driver (L298N) controls two DC motors to move the robot.
4. **Communication Module**: An ESP8266 Wi-Fi module enables IoT capabilities, sending data to cloud platforms like ThingSpeak or Blynk.

### Components Required

- Arduino Uno
- L298N Motor Driver
- Light Dependent Resistors (LDRs) - 2 or more
- DHT11 Temperature & Humidity Sensor
- ESP8266 Wi-Fi Module
- DC Motors - 2
- Jumper Wires and Breadboard
- Power Source (Battery Pack)

### Circuit Diagram

![Circuit Diagram](CIRCUIT%20DIAGRAM.jpg)

The above diagram shows the connections required to set up the light-tracking robot. Ensure all connections are secure, especially for the motor driver and LDR sensors.

### Assembly and Setup

1. **Attach the LDR Sensors**: Place LDRs on the front corners of the robot. These sensors help detect light intensity and guide the robot towards the brightest light source.
2. **Connect the DHT11 Sensor**: This sensor provides environmental data like temperature and humidity, which can be logged to the cloud.
3. **Set Up the Motor Driver and Motors**: Connect the L298N driver to the motors and Arduino. The motor driver will receive signals from the Arduino to control motor speed and direction.
4. **Integrate the ESP8266 Wi-Fi Module**: Connect the ESP8266 to enable IoT capabilities, such as data logging and remote control via cloud platforms.

### Code and Operation

Upload the code provided in this repository to the Arduino. The code includes:
- Reading light intensity from the LDRs to determine the direction of movement.
- Using the DHT11 sensor to gather environmental data.
- Communicating with the ESP8266 to send data to cloud platforms in real time.

> **Note**: Ensure you have the necessary libraries for Arduino, including `DHT.h` for the DHT11 sensor and `ESP8266WiFi.h` for Wi-Fi connectivity.

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
4. **Agricultural Monitoring**: Use sunlight tracking to monitor crop exposure.

### Future Enhancements

Future improvements could include:
- Adding obstacle avoidance sensors for improved navigation.
- Enhancing IoT integration to support more data analytics platforms.
- Implementing adaptive motor control for smoother light tracking.
