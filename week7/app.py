import cv2
import mediapipe as mp
import numpy as np
import face_recognition
import os
from flask import Flask, Response
import datetime
import serial
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from telegram import Bot
import asyncio
import urllib.request  # Add this import for URL handling
import requests

# Define the IP address of your ESP32-based PCB
esp32_ip = "192.168.137.29"  # Change to your ESP32's IP address

# Function to trigger the buzzer
def trigger_buzzer():
    response = requests.get(f"http://{esp32_ip}/trigger_buzzer")
    if response.status_code == 200:
        print("Buzzer triggered!")

# Function to lock the door 
def lock_door():
    response = requests.get(f"http://{esp32_ip}/lock_door")
    if response.status_code == 200:
        print("Door locked!")


# Define your Gmail credentials
GMAIL_USER = "yours"
GMAIL_PASSWORD = "yours"

# Define your Telegram bot token and chat ID
TELEGRAM_BOT_TOKEN = 'yours'
TELEGRAM_CHAT_ID = 'yours'

# Create an SMTP client
smtp_client = smtplib.SMTP("smtp.gmail.com", 587)
smtp_client.starttls()
smtp_client.login(GMAIL_USER, GMAIL_PASSWORD)

url = 'http://192.168.137.189/1600x1200.jpg' #cam url

# Initialize the MediaPipe Face Detection module
mp_face_detection = mp.solutions.face_detection
mp_drawing = mp.solutions.drawing_utils

# Load known face encodings and names for face recognition
path = r'C:\Users\HP\Desktop\camvisiotech\test'  # Replace with your image directory
images = []
classNames = []
myList = os.listdir(path)
print(myList)
for cl in myList:
    curImg = cv2.imread(f'{path}/{cl}')
    images.append(curImg)
    classNames.append(os.path.splitext(cl)[0])

def findEncodings(images):
    encodeList = []
    for img in images:
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        encode = face_recognition.face_encodings(img)[0]
        encodeList.append(encode)
    return encodeList

encodeListKnown = findEncodings(images)
print('Encoding Complete')

# Initialize variables for continuous "0" counting and last notification time
continuous_zeros = 0
last_notification_time = None

def generate_frames():
    global continuous_zeros, last_notification_time

    while True:
        try:
            # Capture the image from the ESP32-CAM's URL
            img_response = urllib.request.urlopen(url)
            img_np = np.array(bytearray(img_response.read()), dtype=np.uint8)
            frame = cv2.imdecode(img_np, -1)

            # Convert the frame to RGB
            image_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

            # Detect faces in the frame using MediaPipe Face Detection
            with mp_face_detection.FaceDetection(
                model_selection=0, min_detection_confidence=0.5) as face_detection:
                results = face_detection.process(image_rgb)

                # Initialize flags for recognized and unknown
                recognized = False
                unknown = False

                if results.detections:
                    for detection in results.detections:
                        bboxC = detection.location_data.relative_bounding_box
                        ih, iw, _ = frame.shape
                        x, y, w, h = int(bboxC.xmin * iw), int(bboxC.ymin * ih), int(bboxC.width * iw), int(bboxC.height * ih)

                        # Crop the face region for face recognition
                        face_image = frame[y:y+h, x:x+w]

                        # Ensure that face_image is not empty before resizing
                        if face_image.shape[0] > 0 and face_image.shape[1] > 0:
                            # Perform face recognition on the cropped face image
                            imgS = cv2.resize(face_image, (0, 0), None, 0.25, 0.25)
                            imgS = cv2.cvtColor(imgS, cv2.COLOR_BGR2RGB)
                            facesCurFrame = face_recognition.face_locations(imgS)
                            encodesCurFrame = face_recognition.face_encodings(imgS, facesCurFrame)

                            for encodeFace, faceLoc in zip(encodesCurFrame, facesCurFrame):
                                matches = face_recognition.compare_faces(encodeListKnown, encodeFace)
                                if any(matches):
                                    recognized = True
                                    # Get the name of the recognized known face
                                    name = classNames[matches.index(True)]
                                    y1, x2, y2, x1 = faceLoc
                                    y1, x2, y2, x1 = y1 * 4 + y, x2 * 4 + x, y2 * 4 + y, x1 * 4 + x
                                    cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                                    cv2.rectangle(frame, (x1, y2 - 35), (x2, y2), (0, 255, 0), cv2.FILLED)
                                    cv2.putText(frame, name, (x1 + 6, y2 - 6), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
                                else:
                                    unknown = True
                                    # Draw a red bounding box for unknown individuals
                                    cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)

            # Display "0/1" based on recognition status
                
            if recognized or not (recognized or unknown):
                displayed_text = "1"
                continuous_zeros = 0  # Reset the continuous "0" count
            
            
            else:
                displayed_text = "0"
                continuous_zeros += 1 # Increment the continuous "0" count

            # Check if continuous_zeros has reached 5 (indicating 5 seconds of "0")
            if continuous_zeros >= 3 * 3:  # 3 seconds * 3 frames/second
                current_time = datetime.datetime.now()

                # Check if enough time has passed since the last notification (15 se )
                if last_notification_time is None or (current_time - last_notification_time).total_seconds() >= 15:
                    last_notification_time = current_time

                    # Trigger the notification
                    trigger_buzzer()  # Trigger the buzzer
                    lock_door()       # Lock the door
                    subject = "Motion Detected!"
                    body = "Someone has entered the frame. Here's the link to the video:\n\n"
                    video_link = "https://mohittalwar23.github.io/PythonSystemTest/"  # Replace with the actual path to your video file
                    body += video_link
                    send_notification(subject, body)

            # Add "0/1" text to the top-left corner
            cv2.putText(frame, displayed_text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

            # Add timestamp
            current_time = datetime.datetime.now()
            timestamp = current_time.strftime("%Y-%m-%d %H:%M:%S")

            # Calculate the position of the timestamp
            timestamp_x = frame.shape[1] - 300
            timestamp_y = 30

            # Display the timestamp at the calculated position
            cv2.putText(frame, timestamp, (timestamp_x, timestamp_y), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)

            # Encode the frame as JPEG
            _, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()

            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

        except Exception as e:
            print(f"Error: {e}")

app = Flask(__name__)

@app.route('/')
def index():
    return "Livestreaming Face Recognition/Detection"

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

async def send_telegram_message(text):
    bot = Bot(token=TELEGRAM_BOT_TOKEN)
    await bot.send_message(chat_id=TELEGRAM_CHAT_ID, text=text)

def send_notification(subject, body):
    send_email(subject, body)
    asyncio.run(send_telegram_message(f"{subject}\n{body}"))

def send_email(subject, body):
    msg = MIMEMultipart()
    msg['From'] = GMAIL_USER
    msg['To'] = 'jeewarrior23@gmail.com'  # Replace with the recipient's email address
    msg['Subject'] = subject
    msg.attach(MIMEText(body, 'plain'))
    smtp_client.sendmail(GMAIL_USER, 'jeewarrior23@gmail.com', msg.as_string())

# Run the Flask app
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)
