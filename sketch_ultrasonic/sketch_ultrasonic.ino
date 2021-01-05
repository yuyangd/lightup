// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPinA 5 // attach pin 8 Arduino to pin Echo of HC-SR04
#define trigPinA 6 //attach pin 9 Arduino to pin Trig of HC-SR04
//#define echoPinB 6 // attach pin 6 Arduino to pin Echo of HC-SR04
//#define trigPinB 7 //attach pin 7 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

void setup()
{
  pinMode(trigPinA, OUTPUT); // Sets the trigPin as an OUTPUT
//  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinA, INPUT); // Sets the echoPin as an INPUT
//  pinMode(echoPinB, INPUT);
  Serial.begin(9600);                               // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

float getDistance(int trigPin, int echoPin)
{
  // Clears the trigPinA condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPinA HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPinA, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}


float frontsensor(int trigPin, int echoPin)
{
  // Serial.println("Activate Sensor1 & Sensor4: ");
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); //tini=micros();
  distance = (duration / 2) * 0.0345;

  return distance;
}

float backsensor(int trigPin, int echoPin)
{
  // Serial.println("Activate Sensor2 & Sensor3: ");
  float duration, distance;
  delay(60);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
//  Serial.print(distance);
//  Serial.println(" cm");
  return distance;
}

void loop()
{
  
  distance = frontsensor(trigPinA, echoPinA);
  if (distance < 5.5)
  {
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");    
  }


//  distance = getDistance(trigPinB, echoPinB);
//  Serial.print("Distance B: ");
//  Serial.print(distance);
//  Serial.println(" cm");
  
}
