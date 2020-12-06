#define echoPinA 8 // attach pin 8 Arduino to pin Echo of HC-SR04
#define trigPinA 9 //attach pin 9 Arduino to pin Trig of HC-SR04
#define echoPinB 6 // attach pin 6 Arduino to pin Echo of HC-SR04
#define trigPinB 7 //attach pin 7 Arduino to pin Trig of HC-SR04

int Led1 = 13;
int Led2 = 12;
int Led3 = 11;
int led4 = 10;

int sensor1 = 0;
int sensor2 = 0;
float duration1, distance1, distance2, duration2;
volatile int FSM_state = 0;
int score = 0;
unsigned long tempo = 0;
unsigned long r, s, x;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
}

void loop()
{
  Serial.println("Activate Sensor1: ");
  Serial.println(FSM_state);
  digitalWrite(trigPinA, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinA, LOW);

  duration1 = pulseIn(echoPinA, HIGH); //tini=micros();
  distance1 = (duration1 / 2) * 0.0345;

  Serial.print("Distance A: ");
  Serial.print(distance1);
  Serial.println(" cm");

  digitalWrite(Led1, LOW);
  digitalWrite(Led2, LOW);
  digitalWrite(Led3, LOW);

  if (distance1 >= 1 && distance1 <= 9)
  {
    //detect an object
    sensor1 = 1;

    if (sensor1 == 1)
    {

      FSM();
    }
  }
  else
  {
    sensor1 = 0;
  }
}

void FSM() //detect the direction of the object
{
  int contador;
  int s = 1000; //timeout

  switch (FSM_state)
  {

  case 0:
    digitalWrite(Led1, LOW);
    digitalWrite(Led2, LOW);
    digitalWrite(Led3, LOW);

    FSM_state = 1;
    break;

  case 1:
    r = millis(); //Returns the number of milliseconds passed since the Arduino board began running the current program
    digitalWrite(Led1, HIGH);
    digitalWrite(Led2, LOW);
    digitalWrite(Led3, LOW);
    FSM_state = 2;
    break;

  case 2:

    delay(60);
    digitalWrite(trigPinB, HIGH);
    delayMicroseconds(500);
    digitalWrite(trigPinB, LOW);
    duration2 = pulseIn(echoPinB, HIGH);
    distance2 = (duration2 / 2) * 0.0344;
    x = millis() - r;

    if ((distance2 >= 1 && distance2 < 9) && (x < s))
    {

      FSM_state = 3;
    }
    else
    {
      FSM_state = 4;
    }
    break;

  case 3:
    digitalWrite(Led1, HIGH);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led3, LOW);
    Serial.println();
    Serial.print("-------------------------------------------");
    Serial.println();
    Serial.print("-----------CORRECT-------------- ");
    Serial.println();
    Serial.print("-------------------------------------------");
    Serial.println();
    score++;
    Serial.println(score);
    FSM_state = 0;
    break;

  case 4:
    digitalWrite(Led1, LOW);
    digitalWrite(Led2, LOW);
    digitalWrite(Led3, HIGH);
    Serial.println();
    Serial.print("-------------------------------------------");
    Serial.println();
    Serial.print("-----------INCORRECT -------------- ");
    Serial.println();
    Serial.print("-------------------------------------------");
    Serial.println();
    delay(200);
    FSM_state = 0;
    break;
  }
}
