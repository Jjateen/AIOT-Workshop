# Session-4: Advanced Machine Learning Concepts and Surveillance Bot

Welcome to **Session-4** of the IoTics AIoT Workshop! In this session, we will delve deeper into machine learning concepts and implement a semi-autonomous surveillance robot with advanced AI capabilities.

## Overview

### Objectives:
1. **Understand advanced machine learning concepts**, including Artificial Neural Networks (ANN) and Convolutional Neural Networks (CNN).
2. **Build a hand gesture-controlled system** using MediaPipe and Arduino for servo motor and LED control.
3. **Develop a semi-autonomous surveillance robot** equipped with a camera for real-time object detection and wireless control.

---

## 1. Advanced Machine Learning Concepts: ANN and CNN

### 1.1 Artificial Neural Networks (ANN)

An **Artificial Neural Network (ANN)** is a computational model inspired by the human brain's structure and function. It consists of layers of nodes (neurons) where each connection carries a weight that adjusts as learning progresses. ANN is widely used in tasks such as classification, regression, and pattern recognition.

#### Key Concepts:
- **Neurons**: Basic units of computation.
- **Layers**: Input layer, hidden layers, and output layer.
- **Activation Functions**: Functions like Sigmoid, ReLU, etc., that introduce non-linearity.

#### Learning Resources for ANN:
- **Research Paper**: ["An Overview of Artificial Neural Networks"](https://arxiv.org/pdf/1404.0936.pdf)
- **Course**: [CS231n: Convolutional Neural Networks for Visual Recognition](http://cs231n.stanford.edu/), particularly the sections on ANNs and their applications.
- **Textbook**: ["Neural Networks and Deep Learning"](http://neuralnetworksanddeeplearning.com/) by Michael Nielsen.

### 1.2 Convolutional Neural Networks (CNN)

A **Convolutional Neural Network (CNN)** is a specialized type of ANN designed to process structured grid data like images. CNNs are highly effective for image recognition tasks due to their ability to capture spatial hierarchies using convolutional layers.

#### Key Concepts:
- **Convolutional Layers**: Extract features using filters/kernels.
- **Pooling Layers**: Reduce the dimensionality of feature maps.
- **Fully Connected Layers**: Connect all neurons from one layer to another.
  
#### Learning Resources for CNN:
- **Research Paper**: ["ImageNet Classification with Deep Convolutional Neural Networks"](https://proceedings.neurips.cc/paper_files/paper/2012/file/c399862d3b9d6b76c8436e924a68c45b-Paper.pdf) by Alex Krizhevsky et al.
- **Course**: [Stanford CS231n: Convolutional Neural Networks for Visual Recognition](http://cs231n.stanford.edu/), which offers detailed coverage of CNNs.

---

## 2. Hand Gesture Control with MediaPipe

### 2.1 Project Overview

In this part, we will use **MediaPipe** for hand gesture recognition to control hardware devices such as a servo motor and LEDs. MediaPipe is a versatile framework by Google that supports real-time, cross-platform AI applications.

### 2.2 Hardware Requirements
- **Arduino Board** (Uno/Nano)
- **Servo Motor**
- **LEDs**
- **Webcam**
- **Breadboard, Jumper wires**

### 2.3 Software Requirements
- **Python 3.9**
- **OpenCV**
- **MediaPipe**
- **PyFirmata** (to interface with Arduino)

### 2.4 Setup Instructions

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Jjateen/PTI-mediapipe.git
   ```

2. **Install Dependencies:**
   Install necessary Python packages using:
   ```bash
   pip install -r requirements.txt
   ```

3. **Connect Arduino:**
   Update the COM port in the `final_test.py` script to match your Arduino connection.

4. **Run the Setup Script:**
   Test the environment setup with:
   ```bash
   python err_test.py
   ```

### 2.5 Running Gesture Control

- **Left Hand Gestures**: Control the servo motor’s angle.
- **Right Hand Gestures**: Control the state of connected LEDs.

To start gesture control:
```bash
python final_test.py
```

### 2.6 Code Explanation

- **MediaPipe** detects the hand and computes angles for each finger. These angles are transmitted to Arduino using **PyFirmata** to control the servo motor and LEDs.
- Data is logged into a CSV file for further analysis.

---

## 3. Surveillance Bot Mk2

### 3.1 Project Overview

The **Surveillance Bot Mk2** is a semi-autonomous robot designed for real-time object detection and wireless control. It uses an **ESP32CAM** module for image capture and live video streaming, with object detection powered by **MobileNetSSD**.

### 3.2 Hardware Requirements
- **ESP32CAM Module**
- **Motor Driver** (L298N or similar)
- **DC Motors** and chassis for the robot
- **Battery Pack**
- **Ultrasonic Sensor** (optional for obstacle avoidance)

### 3.3 Software Requirements
- **Python 3.7 and above**
- **Flask** (for web server)
- **MobileNetSSD**
- **OpenCV**

### 3.4 Setup Instructions

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Jjateen/SurveillanceBotMk2.git
   ```

2. **Install Dependencies:**
   Install required Python libraries using:
   ```bash
   pip install -r requirements.txt
   ```

3. **ESP32CAM Setup:**
   - Flash the ESP32CAM with the provided firmware.
   - Connect it to your local network.

4. **Start the Flask Web Server:**
   ```bash
   flask run
   ```

### 3.5 Running the Surveillance Bot

1. **Launch the Web App:**
   - Open the web app on your browser (usually `http://127.0.0.1:5000`).
   - Use the joystick for wireless control and view the live video feed.

2. **Object Detection:**
   - The bot uses **MobileNetSSD** for real-time object detection.
   - Detected objects are displayed with bounding boxes in the live video stream.

### 3.6 Code Explanation

- **Flask Web App**: Provides a user interface for controlling the robot.
- **Object Detection**: Uses **OpenCV** to apply MobileNetSSD to video frames for object detection.
- **Wireless Control**: Joystick commands are sent from the web app to the robot for movement.

---

## Conclusion

By the end of this session, you will have a deeper understanding of **ANN and CNN** models, hand gesture recognition, and real-time object detection in IoT systems. These skills are crucial for developing innovative applications in AI-powered IoT.

---

## Additional Free Resources

- **MediaPipe Documentation**: [MediaPipe by Google](https://mediapipe.dev/)
- **PyFirmata Documentation**: [PyFirmata](https://pyfirmata.readthedocs.io/)
- **MobileNetSSD Research Paper**: ["MobileNetV1"](https://arxiv.org/pdf/1704.04861.pdf)
- **OpenCV Documentation**: [OpenCV](https://opencv.org/)

---

## License

This project is licensed under the [MIT License](../LICENSE). Feel free to explore and contribute!
