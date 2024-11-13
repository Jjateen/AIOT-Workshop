import serial
import cv2
import time
import numpy as np
import requests
arduinoData=serial.Serial('com12',9600,timeout=1)
time.sleep(1)
d1=0
add1=0
d2=0
add2=0


huelow1=0
huehigh1=93
satlow1=66
sathigh1=165
vallow1=24
valhigh1=139

huelow2=121
huehigh2=179
satlow2=0
sathigh2=88
vallow2=52
valhigh2=151
url='http://192.168.137.7'   #change you ip address
cam=cv2.VideoCapture(url+":81/stream")
while True:
    #img_resp = urllib.request.urlopen(url)
    #img_np = np.array(bytearray(img_resp.read()), dtype=np.uint8) 
    #frame = cv2.imdecode(img_np, -1)                    #capture frame from here
    ignore,frame=cam.read()
    frame=cv2.resize(frame,(240,240))
    frameHSV=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    lowerbound1=np.array([huelow1,satlow1,vallow1])
    upperbound1=np.array([huehigh1,sathigh1,valhigh1])
    lowerbound2=np.array([huelow2,satlow2,vallow2])
    upperbound2=np.array([huehigh2,sathigh2,valhigh2])
    mymask1=cv2.inRange(frameHSV,lowerbound1,upperbound1)
    mymask2=cv2.inRange(frameHSV,lowerbound2,upperbound2)
    counters1,junk=cv2.findContours(mymask1,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    counters2,junk=cv2.findContours(mymask2,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    for count in counters1:
        add1=add1+1 
    for count in counters2:
        add2=add2+1     
    for counter in counters1:
        area=cv2.contourArea(counter)
        if area>=200:
            #cv2.drawContours(frame,[counter],-1,(255,0,0),3)
            x,y,w,h=cv2.boundingRect(counter)
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
            if y+(h/2) < 80:
                arduinoData.write(('Right'+'\n').encode())
                time.sleep(0.01)
                #print("left")
            if y+(h/2) > 160:
                arduinoData.write(('Left'+'\n').encode()) 
                time.sleep(0.01)
                #print("right")   
            if y+(h/2)>80 and y+(h/2)<160:
                arduinoData.write(('Center1'+'\n').encode())
                time.sleep(0.01)
                arduinoData.flush() 
                #print("center1") 
        else:
            d1=d1+1
            if d1==add1:
                arduinoData.write(('Nothing'+'\n').encode())
                print("nothing")         
    for counter in counters2:
        area=cv2.contourArea(counter)
        if area>=200:
            #cv2.drawContours(frame,[counter],-1,(255,0,0),3)
            x,y,w,h=cv2.boundingRect(counter)
            cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
            if y+(h/2) < 80:
                arduinoData.write(('Right'+'\n').encode())
                time.sleep(0.01)
                print("left")
            if y+(h/2) > 160:
                arduinoData.write(('Left'+'\n').encode()) 
                time.sleep(0.01)
                print("right")   
            if y+(h/2)>80 and y+(h/2)<160:
                arduinoData.write(('Center2'+'\n').encode())
                time.sleep(0.01)
                arduinoData.flush() 
                print("center2")              
        else:
            d2=d2+1
            if d2==add2:
                arduinoData.write(('Nothing'+'\n').encode())
                print("nothing")
    d1=0
    d2=0
    add1=0
    add2=0
    #cv2.imshow('maske',mymask1)
    #cv2.imshow('maskp',mymask2) 
    cv2.imshow('my cam',frame)
    if cv2.waitKey(1)==ord('q'):
        break
cv2.destroyAllWindows() 
cam.release()   