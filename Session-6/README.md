# Color Tracking Robotic Gripper

## Description
This project involves a color tracking robotic gripper capable of distinguishing between two sets of colors. It can sort items based on their color, placing one set on its left and the other on its right. This functionality is particularly useful for sorting harmful trash where human interference can pose health risks. The project is completely automatic.

## Features
- Automatic color detection and sorting
- Distinguishes between two sets of colors
- Places items on the left or right based on their color
- Can be used for sorting harmful trash to prevent health issues
- Integrates with an Arduino for controlling the robotic arm

## Installation and Setup
1. Clone the repository:
    ```sh
    git clone https://github.com/your-username/color-tracking-robotic-gripper.git
    cd color-tracking-robotic-gripper
    ```

2. Install the required Python libraries:
    ```sh
    pip install opencv-python pyserial numpy
    ```

3. Upload the Arduino code to the Arduino Uno:
    ```sh
    # Use the Arduino IDE to upload the provided sketch to the Arduino Uno.
    ```

## Usage
1. Initialize the ESP32-CAM and host a local webserver to stream images.
2. Obtain the IP address of the ESP32-CAM from the serial monitor.
3. Use the IP address in the Python script to grab frames from the local webserver.
4. Run the Python script in VS Code to process the frames and find contours for the set color ranges.

## Hardware Requirements
- 3 MG955 servo motors
- 1 SG servo motor
- 3D printed model of the robotic arm
- Arduino Uno
- ESP32-CAM
- Board for programming the ESP32-CAM via USB cable
- Laptop for image processing

## Software Requirements
- Python
- OpenCV
- pySerial
- NumPy
- Arduino Servo Library
  
##Software Details
Python: Version 3.7(Used). Compatible with 3.9 (Tested)

## Team Details

### Team Name
Iot-1st-Year

### Members
- **Member 1**: Jayesh Thakare (Programing and Designing) - Contact: +91 8446374356 
- **Member 2**: Kartik Agrawal (Demonstrator) - Contact: +91 9259322930
- **Member 3**: Nimesh Suryawanshi (Assembly) - Contact: +91 7489230310
- **Member 4**: Vivek Kumar (Hardware Management) - Contact: +91 6393265832

### Contact
- **Email(Jayesh Thakare)**: scientistn1420@gmail.com

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Acknowledgements
- Thanks to the open-source community for providing resources and libraries.
- Special thanks to Jayesh for the project idea and implementation.
