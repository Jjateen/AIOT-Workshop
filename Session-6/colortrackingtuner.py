import cv2
import numpy as np
huelow=0
huehigh=10
satlow=0
sathigh=10
vallow=0
valhigh=10
def huelowtrack(val):
    print(val)
    global huelow
    huelow=val
def huehightrack(val):
    print(val)
    global huehigh
    huehigh=val
def satlowtrack(val):
    print(val)
    global satlow
    satlow=val
def sathightrack(val):
    print(val)
    global sathigh
    sathigh=val           
def vallowtrack(val):
    print(val)
    global vallow
    vallow=val
def valhightrack(val):
    print(val)
    global valhigh
    valhigh=val
url='http://192.168.137.7'
cam=cv2.VideoCapture(url+":81/stream")
cv2.namedWindow('tuner')
cv2.createTrackbar('hue low','tuner',0,179,huelowtrack)
cv2.createTrackbar('hue high','tuner',30,179,huehightrack)
cv2.createTrackbar('sat low','tuner',0,255,satlowtrack)
cv2.createTrackbar('sat high','tuner',10,255,sathightrack)
cv2.createTrackbar('val low','tuner',0,255,vallowtrack)
cv2.createTrackbar('val high','tuner',10,255,valhightrack)
while True:
    ignore, frame=cam.read()
    cv2.resize(frame,(240,240))
    frameHSV=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    lowerbound=np.array([huelow,satlow,vallow])
    upperbound=np.array([huehigh,sathigh,valhigh])
    mymask=cv2.inRange(frameHSV,lowerbound,upperbound)
    cv2.imshow('mask',mymask)
    cv2.imshow('my cam',frame)
    
    if cv2.waitKey(1)==ord('q'):
        break
cv2.destroyAllWindows()    