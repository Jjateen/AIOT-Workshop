const int trigPin = 2;
/*
"#define" is a preprocessor directive. It defines a lable and a value, that will be positioned in the
preprocessed-source-code at the same place of each occurence of the label. No type is defined, so it 
is a basic substitution of strings before compilation. It can then lead to errors or misunderstandings during compilation.
*/
#define echoPin 3 // Unsafer as the compiler can check for type errors and throw messages (or break compilation) if you made a mistake.

const int buzzer = 4;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in centimeters (divide by 58 for inches)
  
  Serial.println("Distance = " + (String)distance);
  
  if(distance <= 5) digitalWrite(buzzer,HIGH);
  else digitalWrite(buzzer,LOW);
  
  delay(10); // Wait for 1 second before sending the next data
}
