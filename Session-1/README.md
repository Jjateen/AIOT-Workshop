# AIOT Workshop - Session 1: Working with HC-SR04, Buzzer, and IoT Cloud Integration

In **Session-1** of the AIOT Workshop series, participants explore the fundamentals of interfacing an ultrasonic sensor (HC-SR04) with a buzzer and connecting it to IoT platforms like Adafruit IO and Blynk. This session includes multiple projects that showcase various ways to interact with and visualize sensor data.

---

## Projects in this Session

1. **Blink LED Example** - Basic LED blink using Arduino.
2. **Ultrasonic Sensor with Buzzer** - Set up an ultrasonic distance sensor to control a buzzer.
3. **Using NewPing Library** - Simplified ultrasonic sensor control using the NewPing library.
4. **Blynk and Adafruit IO Integration** - Visualize sensor data on the cloud using Blynk and Adafruit IO platforms.

---

## Materials Required

- **Arduino Uno**
- **HC-SR04 Ultrasonic Sensor**
- **Buzzer**
- **Jumper Wires**
- **ESP8266/ESP32** (optional, for IoT integration)
- **Internet Connection** (for cloud platforms)

---

## 1. Blink LED Example

This is a simple project to get started with Arduino by making an LED blink.

- **File**: [Blink.ino](./basic_part/Blink/Blink.ino)
- **Circuit Diagram**: Connect an LED to pin 13 on the Arduino, with a 220-ohm resistor in series to ground.

```cpp
void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
```

---

## 2. Ultrasonic Sensor with Buzzer

This project involves setting up an ultrasonic sensor to measure distance and activate a buzzer if an object comes within a certain range.

- **File**: [secondSketchofTheDay.ino](./basic_part/ultrasonicBuzzer/secondSketchofTheDay.ino)
- **Circuit Diagram**: [ckt.png](./basic_part/ckt.png)

### Code Overview

The HC-SR04 ultrasonic sensor is connected to the Arduino, and the code measures distance. If an object is detected within a set distance threshold, the buzzer is activated.

```cpp
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 11;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
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

  if (distance < 20) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
  delay(500);
}
```

---

## 3. Using NewPing Library

This project demonstrates using the **NewPing** library for simplified distance measurement with the ultrasonic sensor.

- **File**: [usingNewPing.ino](./basic_part/usingNewPing/usingNewPing.ino)
- **Circuit Diagram**: Same as above, with the HC-SR04 connected to pins 9 and 10.

### Code Overview

The NewPing library provides a more user-friendly interface for controlling the HC-SR04 sensor.

```cpp
#include <NewPing.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 200

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

## 4. Blynk and Adafruit IO Integration

In this project, we integrate the HC-SR04 sensor with Blynk and Adafruit IO to visualize sensor data remotely.

- **Files**:
  - **Blynk**: [Blynk_part.ino](./blynk_adafruit/Blynk_part/Blynk_part.ino)
  - **Adafruit IO**: [Adafruit_part.ino](./blynk_adafruit/Adafruit_part/Adafruit_part.ino)
  - **Tutorial**: [Blynk Tutorial.pdf](./blynk_adafruit/Blynk%20Tutorial.pdf)
  - **Step-by-Step Guide**: [Step-by-step.pdf](./blynk_adafruit/Step-by-step.pdf)
  - **Circuit Diagram**: [Circuit.png](./blynk_adafruit/Circuit.png)

### Blynk Setup Instructions

1. **Create a Blynk Account**: Install the Blynk app on your mobile device and create an account.
2. **Create a New Project**: Select ESP8266 or ESP32 as your hardware and add a widget (e.g., Gauge or Display) to show the distance data.
3. **Obtain Auth Token**: Copy the token for use in the code.

### Adafruit IO Setup Instructions

1. **Create an Account on Adafruit IO**: Go to [Adafruit IO](https://io.adafruit.com/) and create an account.
2. **Set Up a Feed**: Create a feed for distance measurements.
3. **Obtain Credentials**: You will need your Adafruit IO username and key for the code.

> **Note**: For more detailed instructions, refer to the [Blynk Tutorial.pdf](./blynk_adafruit/Blynk%20Tutorial.pdf) and [Step-by-step.pdf](./blynk_adafruit/Step-by-step.pdf) provided in this session.

---

### Code Examples for IoT Integration

#### Blynk Code Example

```cpp
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <NewPing.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

char auth[] = "your_BLYNK_AUTH_TOKEN";
char ssid[] = "your_SSID";
char pass[] = "your_PASSWORD";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Blynk.virtualWrite(V1, distance);
  Blynk.run();
  delay(500);
}
```

#### Adafruit IO Code Example

```cpp
#include <WiFi.h>
#include <AdafruitIO_WiFi.h>
#include <NewPing.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#define IO_USERNAME "your_AIO_USERNAME"
#define IO_KEY "your_AIO_KEY"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, ssid, pass);

void setup() {
  Serial.begin(9600);
  io.connect();
}

void loop() {
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  io.run();
  delay(500);
}
```

---

## Summary

In **Session-1**, we explored:
- Basic LED blinking using Arduino.
- Setting up the HC-SR04 sensor with a buzzer for distance-based feedback.
- Simplified sensor control using the NewPing library.
- Introduction to IoT platforms Blynk and Adafruit IO for remote visualization.

For more guidance on IoT integration, please refer to the tutorials provided in the session folder. 

---

This session introduces key concepts that will be built upon in future sessions. Happy building!
