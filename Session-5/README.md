# **Session-5: Object Detection with CamVisioTech Mk1**

This session walks through the implementation of **real-time object detection** using Haar Cascade classifiers, with a focus on building a Wi-Fi-enabled camera system called **CamVisioTech Mk1** for smart surveillance. By the end of this tutorial, you'll have developed an AI-driven camera that recognizes objects, locks doors, and sends alerts.

## **Project Overview**

In this project, you'll create a smart surveillance system capable of:
- Detecting faces and objects in real time using the **Haar Cascade** method.
- Locking doors and triggering alarms when an intruder is detected.
- Sending email and Telegram notifications to alert the user.
- Streaming live video with object detection overlays via a Flask web application.

### **Demo Video**

For a live demonstration of the project in action, check out this video on Instagram:
[CamVisioTech Mk1 Demo](https://www.instagram.com/p/C0wjcxdiWFX/)

---

## **Objectives:**
1. **Understand the Haar Cascade method** for object detection.
2. **Implement real-time object detection** on a Wi-Fi-enabled camera.
3. **Develop a Flask-based web application** for video streaming and live monitoring.
4. **Set up automated alerts** via email and Telegram for security breaches.

---

## **1. Understanding Object Detection**

### 1.1 What is Haar Cascade?

Haar Cascades are machine learning object detection algorithms used to identify objects in images or videos. The technique was introduced by **Paul Viola** and **Michael Jones** in their 2001 research paper [Rapid Object Detection using a Boosted Cascade of Simple Features](https://www.cs.ubc.ca/~lowe/425/slides/13-ViolaJones.pdf). The algorithm uses a cascade function trained from a lot of positive and negative images to detect objects, primarily faces.

It works in stages, where each stage applies increasingly complex filters to identify the features of the object of interest.

### 1.2 Object Detection and Face Recognition

In this project, we'll combine **Haar Cascades** for face detection and **face recognition** using the `face_recognition` library. The system will recognize known individuals and trigger a response if an unknown face is detected.

For more information on Haar Cascades, check the following free resources:
- [OpenCV Documentation: Haar Feature-based Cascade Classifiers](https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html)
- [Viola-Jones Face Detection Algorithm Paper](https://www.cs.ubc.ca/~lowe/425/slides/13-ViolaJones.pdf)

---

## **2. Hardware & Software Requirements**

### 2.1 Hardware:
- **ESP32CAM** Module: A microcontroller with a built-in camera and Wi-Fi for capturing images and video.
- **L298N Motor Driver**: For controlling motors (optional for added mobility).
- **Servo Motor**: To rotate the camera (optional).
- **Buzzer**: For triggering alerts.
- **Power Supply**: Suitable power source for your ESP32CAM and motor setup.
- **Breadboard & Jumper Wires**: For wiring connections.

### 2.2 Software:
- **Python 3.x**
- **Flask** (for the web app)
- **OpenCV** (for image and video processing)
- **face_recognition** (for face detection and recognition)
- **MediaPipe** (optional for gesture recognition)
- **PySerial** (for serial communication with Arduino or ESP32)

#### **Installing `face_recognition` and `dlib`**
To install the `face_recognition` library, **Dlib** must be installed first. Dlib is required for facial feature extraction and recognition. 

For Windows users, follow these steps to install **Dlib** using pre-compiled binary wheels:

1. Download the `.whl` file for your specific Python version from this repository:
   [Dlib Compiled Binaries](https://github.com/z-mahmud22/Dlib_Windows_Python3.x)

2. Open a terminal and install the `.whl` file for your Python version:
   - Python 3.7:
     ```bash
     python -m pip install dlib-19.22.99-cp37-cp37m-win_amd64.whl
     ```
   - Python 3.8:
     ```bash
     python -m pip install dlib-19.22.99-cp38-cp38-win_amd64.whl
     ```
   - Python 3.9:
     ```bash
     python -m pip install dlib-19.22.99-cp39-cp39-win_amd64.whl
     ```
   - Python 3.10:
     ```bash
     python -m pip install dlib-19.22.99-cp310-cp310-win_amd64.whl
     ```
   - Python 3.11:
     ```bash
     python -m pip install dlib-19.24.1-cp311-cp311-win_amd64.whl
     ```
   - Python 3.12:
     ```bash
     python -m pip install dlib-19.24.99-cp312-cp312-win_amd64.whl
     ```

3. After installing Dlib, install `face_recognition`:
   ```bash
   pip install face_recognition
   ```

If you'd like to build Dlib from source, refer to the [official Dlib GitHub instructions](https://github.com/davisking/dlib) for guidance.

---

## **3. Setting Up the Project**

### 3.1 Clone the Repository

Start by cloning the repository:
```bash
git clone https://github.com/Jjateen/AIOT-Workshop.git
cd Session-5
```

### 3.2 Install Required Dependencies

Ensure you have all necessary Python libraries installed:
```bash
pip install -r requirements.txt
```

### 3.3 Flash the ESP32CAM

Flash the ESP32CAM with the provided firmware in the `WifiCam/` directory:
- `WifiCam.ino`: The Arduino sketch for capturing video and sending it over Wi-Fi.
- `handlers.cpp` and `WifiCam.hpp`: Support files for ESP32CAM functionality.

### 3.4 Circuit Diagram

The circuit connections are depicted in the image `ckt.png`. Ensure the wiring matches the diagram for proper functionality, especially for the buzzer and motor control.

![Circuit Diagram](./ckt.png)

---

## **4. Running the Surveillance Bot**

### 4.1 Flask Web App

The Flask web application serves the video feed and provides an interface for monitoring the camera and receiving alerts. To start the web app, run:

```bash
python app.py
```

Open your browser and navigate to `http://127.0.0.1:5000` to view the live video stream from the ESP32CAM.

### 4.2 Face Detection and Recognition

The project uses pre-stored images for face recognition. Make sure you add your images to the specified folder in the `app.py` file:
```python
path = r'C:\path\to\your\images'
```

Once the images are loaded and encoded, the system will compare faces in real-time with the stored images, triggering an alert if an unknown face is detected.

### 4.3 Notifications and Alerts

The system can:
- **Trigger a buzzer** when an unknown face is detected.
- **Lock the door** via the ESP32CAM by sending a GET request to its IP.
- **Send email and Telegram alerts** to notify the user of intrusions.

Ensure you configure the following in `app.py`:
- **ESP32CAM IP Address**: Update with your ESP32CAM’s local IP address.
- **Gmail Credentials**: Replace with your own email details to send alerts.
- **Telegram Bot Token**: Set up a Telegram bot to send notifications.

---

## **5. Code Explanation**

### 5.1 Face Recognition and Detection

The code uses **face_recognition** and **MediaPipe** to perform face detection and recognition. Faces are detected, cropped, and then matched with pre-encoded images.

- **Face Detection**: MediaPipe is used to detect faces and highlight them with bounding boxes.
- **Face Recognition**: The face_recognition library matches detected faces with known faces stored in the system.

### 5.2 Video Streaming

The Flask app streams video frames from the ESP32CAM using the following logic:
- The `generate_frames` function captures images from the ESP32CAM URL.
- These frames are processed and encoded in JPEG format.
- The video feed is served at `/video_feed` using Flask's `Response` method.

---

## **6. Resources for Further Learning**

For those interested in diving deeper into object detection and face recognition, here are some excellent (and free) resources:

- **OpenCV's Cascade Classifier**: [Documentation](https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html)
- **Viola-Jones Face Detection**: [Research Paper](https://cs.nyu.edu/~yannick/face-detection/face_detection_ViolaJones.pdf)
- **Face Recognition with Python**: [GitHub Repo](https://github.com/ageitgey/face_recognition)
- **MediaPipe Documentation**: [MediaPipe Solutions](https://google.github.io/mediapipe/solutions/face_detection)

---

## **Conclusion**

In this session, you learned how to:
- Implement Haar Cascade-based face detection.
- Set up an ESP32CAM for live video streaming.
- Build a real-time smart surveillance system with automated alerts and facial recognition.

This project is an excellent stepping stone for AI-powered security systems, providing both hands-on hardware experience and advanced coding knowledge. Feel free to extend the functionality and explore more AI-based use cases!

---

## **License**

This project is licensed under the [Apache 2.0 License](../LICENSE).

Feel free to modify and contribute!
