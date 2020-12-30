#define echoPinA 8 // attach pin 8 Arduino to pin Echo of HC-SR04
#define trigPinA 9 //attach pin 9 Arduino to pin Trig of HC-SR04
#define echoPinB 6 // attach pin 6 Arduino to pin Echo of HC-SR04
#define trigPinB 7 //attach pin 7 Arduino to pin Trig of HC-SR04

#define echoPinC 4
#define trigPinC 5
#define echoPinD 2
#define trigPinD 3

int Led1 = 13;
int Led2 = 12;
int Led3 = 11;
int Ledx = 10; //detect

int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;

float duration1, distance1, distance2, duration2;
float duration3, distance3, distance4, duration4;

volatile int FSM_state = 0;

unsigned long detect_timeout;
unsigned long timer1, timer1_diff;
unsigned long timer2, timer2_diff;

int walking = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT);
  pinMode(trigPinD, OUTPUT);
  pinMode(echoPinD, INPUT);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Ledx, OUTPUT);
}

float frontsensor(int trigPin, int echoPin)
{
  float duration, distance;
  // Serial.println("Activate Sensor1 & Sensor4: ");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); //tini=micros();
  distance = (duration / 2) * 0.0345;

  // Serial.print(distance);
  // Serial.println(" cm");
  return distance;
}

float backsensor(int trigPin, int echoPin)
{
  float duration, distance;
  // Serial.println("Activate Sensor2 & Sensor3: ");
  delay(60);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  return distance;
}

void loop()
{
//  Serial.print(">>FSM_state: ");
//  Serial.println(FSM_state);

  distance1 = frontsensor(trigPinA, echoPinA);
  Serial.print("Distance 1: ");
  Serial.println(distance1);
//  distance2 = backsensor(trigPinB, echoPinB);
//  Serial.print("Distance 2: ");
//  Serial.println(distance2);
//  distance3 = backsensor(trigPinC, echoPinC);
//  Serial.print("Distance 3: ");
//  Serial.println(distance3);
  distance4 = frontsensor(trigPinD, echoPinD);
  Serial.print("Distance 4: ");
  Serial.println(distance4);

  walking = 1;
  lightup();

  digitalWrite(Ledx, HIGH);
  delay(1000);

}

void lightup()
{
//  Serial.println("lightup, is walking: ");
//  Serial.println(walking);
  if (walking == 1)
  {
    digitalWrite(Led1, HIGH);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led3, HIGH);
  }
  else
  {
    digitalWrite(Led3, LOW);
    digitalWrite(Led2, LOW);
    digitalWrite(Led1, LOW);
  }
}
