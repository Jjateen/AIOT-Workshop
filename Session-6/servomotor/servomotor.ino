#include <Servo.h>
int trig = 8;
int echo = 9;
int gndL = 3;
int posL = 4;
int gndR = 5;
int posR = 6;
int enableL = 10;
int enableR = 11;
int planepos=90;
long distance,traveltime;
String signal;
Servo servoright;
Servo servoleft;
Servo servohead;
Servo servobottom;
void setup() {
  servobottom.attach(A3);
  servoright.attach(A2);
  servoleft.attach(A1);
  servohead.attach(A0);
  Serial.begin(9600);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(gndL, OUTPUT);
  pinMode(posL, OUTPUT);
  pinMode(gndR, OUTPUT);
  pinMode(posR, OUTPUT);
  pinMode(enableL, OUTPUT);
  pinMode(enableR, OUTPUT);
  servoright.write(0);
  servoleft.write(0);
  servohead.write(143);
  servobottom.write(90);
  analogWrite(enableL,255);  // Ensure motors are enabled
  analogWrite(enableR,255);
}

void loop() {
  if (Serial.available() > 0) {
   while(Serial.available()>0)
   {
    Serial.read();
   }
   delay(500);
   signal=Serial.readStringUntil('\n');
   signal.trim();
    if(signal=="Right")
    {
      //right();
      servoBottom(1);
    }
    else if(signal=="Left")
    {
      //left();
      servoBottom(0);
    }
    else if(signal=="Center1" || signal=="Center2")
    {
      stop();
      operatearm();
    }
    else if(signal=="Nothing")
    {
    //stop();

    //   digitalWrite(trig,LOW);
    //   delay(1);
    //   digitalWrite(trig,HIGH);
    //   delayMicroseconds(25);
    //   digitalWrite(trig,LOW);
    //   traveltime=pulseIn(echo,HIGH);
    //   distance=0.0343*traveltime/2; 
    //   if(distance<30)
    //   {
        //stop();
        // if(Serial.available()>0)
        // {
        //    if(Serial.readStringUntil('\n')=="Left")
        //    {
        //     goto left;
        //    }
        //    if(Serial.readStringUntil('\n')=="Right")
        //    {
        //     goto right;
        //    }
        // }
      
        
      }
    }
  }

//}

void forward() {
  digitalWrite(posL, HIGH);
  digitalWrite(gndL, LOW);
  digitalWrite(posR, LOW);
  digitalWrite(gndR, HIGH);
}

void right() {
  digitalWrite(posL, LOW);
  digitalWrite(gndL, HIGH);
  digitalWrite(posR, LOW);
  digitalWrite(gndR, HIGH);
}

void left() {
  digitalWrite(posL, HIGH);
  digitalWrite(gndL, LOW);
  digitalWrite(posR, HIGH);
  digitalWrite(gndR, LOW);
}

void backward() {
  digitalWrite(posL, LOW);
  digitalWrite(gndL, HIGH);
  digitalWrite(posR, HIGH);
  digitalWrite(gndR, LOW);
}

void stop() {
  digitalWrite(posL, LOW);
  digitalWrite(gndL, LOW);
  digitalWrite(posR, LOW);
  digitalWrite(gndR, LOW);
}

void servoBottom(int n)
{
  if(n==1)
  {
   while(signal!="Center1" && signal!="Center2")
   {
   planepos=planepos+1;
   if(planepos>=180)
   {
    planepos=180;
   }
   servobottom.write(planepos);
    while(Serial.available()>0)
    {
     Serial.read();
    }
   delay(800);
   signal=Serial.readStringUntil('\n');
   signal.trim();
   }
   operatearm();
  }
  else if(n==0)
  {
  while(signal!="Center1" && signal!="Center2")
  {
  planepos=planepos-1;
   if(planepos<=0)
   {
    planepos=0;
   }
   servobottom.write(planepos);
    while(Serial.available()>0)
    {
     Serial.read();
    }
   delay(800);
   signal=Serial.readStringUntil('\n');
   signal.trim();
  }
  operatearm();
  }
}
void operatearm()
{
  servohead.write(80);
  for(int speed=0;speed<=20;speed++)
  {
    servoright.write(speed);
    delay(25);
  }
  delay(1000);
  for(int speed=0;speed<=40;speed++)
  {
    servoleft.write(speed);
    delay(25);
  }
  delay(1000);
  servohead.write(144);
  delay(1000);
 for(int speed=20;speed>=0;speed--)
  {
    for(int speed2=40;speed2<=60;speed2++)
    {
      servoleft.write(speed2);
    }
    servoright.write(speed);
    delay(25);
  }
 delay(1000);
  if(signal=="Center1"){
    for(int speed=planepos;speed>=0;speed--)
      {
        servobottom.write(speed);
        planepos=speed;
        delay(25);
      }
  servohead.write(80);
  delay(1000);
  for(int speed=planepos;speed<=90;speed++)
  {
    servobottom.write(speed);
    planepos=speed;
    delay(25);
  }
  }
  else if(signal=="Center2"){
  for(int speed=planepos;speed<=180;speed++)
  {
    servobottom.write(speed);
    planepos=speed;
    delay(25);
  }
  delay(1000);
  servohead.write(80);
  delay(1000);
  for(int speed=planepos;speed>=90;speed--)
  {
    servobottom.write(speed);
    planepos=speed;
    delay(25);
  }
  }
   delay(1000);
   for (int speed=60;speed>=0;speed--)
  {
    servoleft.write(speed);
    delay(25);
  }
  servohead.write(143);
 
}
