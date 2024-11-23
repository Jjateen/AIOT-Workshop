# AIOT Workshop - Session 0: Introduction Session

Welcome to **Session-0** of the AIOT Workshop series hosted by the IoTics Club! This session covers foundational IoT and Arduino concepts, introduces key team members, and offers hands-on learning by interfacing an ultrasonic sensor (HC-SR04) with Adafruit IO and Blynk. We'll also build and simulate a circuit using Wokwi, an online electronics prototyping platform.

## IoTics Club Team

Meet the core members who support and lead this AIOT workshop:
- **Club Head**: Ayush Karapagele
- **Co-Lead**: [Jjateen Gundesha](https://github.com/Jjateen)
- **Core Members**: Akshit Gangwar, Ashwani Baghel, [Ayush Ambatkar](https://github.com/afloatwont), Ketan Bajpai, Kushagra Mehta, Lakshit Khandelwal, [Mohit Talwar](https://github.com/mohittalwar23), [Nirbhay Raut](https://github.com/sorashiro3), [Parth Singh](https://github.com/CarnageOP10), Yuvraj Singh, and [Mann Manohar](https://github.com/MannManohar).

---

## Workshop Agenda

This introductory session includes:
1. **Introduction to Arduino**: Overview of Arduino hardware, software, and basic programming.
2. **Overview of HC-SR04 Sensor**: Understanding ultrasonic distance measurement.
3. **Wokwi Simulation**: Building and testing circuits using Wokwi’s online platform.
4. **Code Examples**: Comparing two approaches for distance measurement using HC-SR04.
5. **Hands-On Project**: Integrate the HC-SR04 sensor with Adafruit IO and Blynk.

---

## 1. Introduction to Arduino

**Arduino** is an open-source electronics platform that includes both hardware (microcontroller boards) and software (IDE for programming). It is widely used by hobbyists, students, and professionals to create interactive electronic projects.

- **Programming Language**: Arduino uses a simplified C/C++ syntax.
- **Libraries**: Arduino provides libraries that simplify hardware control.

---

## 2. Overview of HC-SR04 Sensor

The **HC-SR04** ultrasonic sensor measures distance by sending an ultrasonic pulse and calculating the time it takes for the pulse to return after bouncing off an object. This sensor is commonly used in robotics and automation projects.

- **Range**: 2cm to 400cm
- **Applications**: Ideal for obstacle detection and distance measurement.

---

## 3. Wokwi Simulation

**Wokwi** is an online platform that allows virtual electronics prototyping, enabling users to design, simulate, and test electronic circuits. This session includes building and simulating an HC-SR04-based project in Wokwi.

1. Go to [Wokwi](https://wokwi.com/) and create a new project.
2. Add the following components:
   - Arduino Uno
   - HC-SR04 ultrasonic sensor
3. Connect the components as per the setup instructions in the workshop slides.
4. Run the simulation to observe distance measurements.

---

## 4. Code Examples

Two approaches to interfacing the HC-SR04 sensor with Arduino:

### Approach 1: Using `pulseIn()` Function

This code directly controls the sensor pins to measure distance.

```cpp
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
```

### Approach 2: Using `NewPing` Library

Using the `NewPing` library simplifies the process by providing a dedicated function for distance measurement.

1. Install the `NewPing` library.
2. Use the code below:

```cpp
#include <NewPing.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
```

---

## 5. Hands-On Project: Integrating HC-SR04 with Adafruit IO and Blynk

This project demonstrates how to connect the HC-SR04 sensor to Adafruit IO and Blynk, enabling data visualization and remote monitoring.

### Setup Instructions

1. **Adafruit IO**: 
   - Create an account on [Adafruit IO](https://io.adafruit.com/) and set up a feed for distance measurements.
   - Obtain your Adafruit IO credentials (username and key).

2. **Blynk**: 
   - Install the Blynk app on your mobile device.
   - Set up a project and add a widget to display sensor data.
   - Obtain your Blynk Auth Token.

> **Note**: This session provides an introductory look at Blynk and Adafruit IO integration. We will cover these platforms in more depth in upcoming sessions.

### Code Example for IoT Integration

```cpp
#include <WiFi.h>
#include <AdafruitIO_WiFi.h>
#include <BlynkSimpleEsp32.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

char ssid[] = "your_SSID";
char pass[] = "your_PASSWORD";
char auth[] = "your_BLYNK_AUTH_TOKEN";
AdafruitIO_WiFi io("your_AIO_USERNAME", "your_AIO_KEY", ssid, pass);

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  io.connect();
}

void loop() {
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send data to Adafruit IO
  io.run();

  // Send data to Blynk
  Blynk.run();
  delay(500);
}
```

---

## Summary

In this session, we covered:
- Basic IoT concepts and Arduino programming.
- Distance measurement using the HC-SR04 sensor.
- Simulating circuits with Wokwi.
- Code examples for interfacing with HC-SR04.
- Connecting the sensor to Adafruit IO and Blynk for IoT integration.

---

Feel free to explore the examples and experiment with different settings. Enjoy the workshop, and happy building!
