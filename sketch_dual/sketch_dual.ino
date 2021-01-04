#define echoPinA 9 
#define trigPinA 10
#define echoPinB 7
#define trigPinB 8

#define echoPinC 5
#define trigPinC 6
#define echoPinD 3
#define trigPinD 4

int Led1 = 13;
int Led2 = 12;
int Led3 = 11;
int Ledx = 10; // indicator of sensor detection

int sensor1 = 0;
int sensor2 = 0;
int sensor3 = 0;
int sensor4 = 0;

float wall_distance = 5.5;
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
  // Serial.println("Activate Sensor1 & Sensor4: ");
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); //tini=micros();
  distance = (duration / 2) * 0.0345;

   Serial.print(distance);
   Serial.println(" cm");
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
  return distance;
}

void loop()
{
  Serial.print(">>FSM_state: ");
  Serial.println(FSM_state);

  distance1 = frontsensor(trigPinA, echoPinA);
  distance4 = frontsensor(trigPinD, echoPinD);

  lightup();

  digitalWrite(Ledx, LOW);

  if (distance4 >= 1 && distance4 <= wall_distance)
  {
    //detect an object, activate sensor4
    sensor4 = 1;
  }

  if (distance1 >= 1 && distance1 <= wall_distance)
  {
    //detect an object, activate sensor1
    sensor1 = 1;
  }

  if ((sensor1 + sensor4) >= 1)
  {
    FSM();
  }
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

void FSM() //detect the state of the object
{
  int detect_timeout = 1000; //timeout 1s
  switch (FSM_state)
  {

  case 0:
    lightup();
    digitalWrite(Ledx, LOW);
    if (sensor1 == 1)
    {
      FSM_state = 1;
    }
    if (sensor4 == 1)
    {
      FSM_state = 2;
    }

    break;

  case 1:
    timer1 = millis(); // activate timer_r for sensor 2
    lightup();
    digitalWrite(Ledx, HIGH);
    FSM_state = 3;
    break;

  case 2:
    timer2 = millis(); // activate timer_t for sensor 3
    lightup();
    digitalWrite(Ledx, HIGH);
    FSM_state = 4;
    break;

  case 3:
    // sensor 2 detect within timer1
    distance2 = backsensor(trigPinB, echoPinB);

    timer1_diff = millis() - timer1;

    // sensor2 activated within timer1

    if (timer1_diff < detect_timeout)
    {
      if (distance2 >= 1 && distance2 < wall_distance)
      {
        FSM_state = 5;
      }
    }
    else
    {
      FSM_state = 6;
    }
    break;

  case 4:
    // sensor 3 detect within timer2
    distance3 = backsensor(trigPinC, echoPinC);

    timer2_diff = millis() - timer2;

    if (timer2_diff < detect_timeout)
    {
      if (distance3 >= 1 && distance3 < wall_distance)
      {
        FSM_state = 5;
      }
    }
    else
    {
      FSM_state = 6;
    }

    break;

  case 5:
    walking = 1;
    digitalWrite(Ledx, HIGH);
    lightup();

    Serial.println();
    Serial.print("-----------IN-------------- ");
    Serial.println();
    sensor1 = 0;
    sensor4 = 0;
    FSM_state = 0;

    break;

  case 6:
    walking = 0;
    digitalWrite(Ledx, LOW);
    lightup();
    Serial.println();
    Serial.print("-----------OUT -------------- ");
    Serial.println();

    sensor1 = 0;
    sensor4 = 0;
    FSM_state = 0;

    break;
  }
}
