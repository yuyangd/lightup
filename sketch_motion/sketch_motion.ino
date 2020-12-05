//code for motion sensor circuit
const int ledPinA = 1;
const int ledPinB = 2;
const int ledPinC = 3;
const int ledPinD = 4;

const int echoAPin = 6; // Echo Pin of Ultrasonic Sensor A
const int pingAPin = 7; // Trigger Pin of Ultrasonic Sensor A

const int echoBPin = 8; // Echo Pin of Ultrasonic Sensor B
const int pingBPin = 9; // Trigger Pin of Ultrasonic Sensor B

volatile int FSM_state = 0; //state
unsigned long r, s, x;
float durationA, distanceA, distanceB, durationB;

int sensorA = 0;
int sensorB = 0;

int ledA_state = LOW;
int ledB_state = LOW;
int ledC_state = LOW;
int ledD_state = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  pinMode(ledPinD, OUTPUT);

  pinMode(pingAPin, OUTPUT);
  pinMode(echoAPin, INPUT);
  pinMode(pingBPin, OUTPUT);
  pinMode(echoBPin, INPUT);
}

void loop()
{

  digitalWrite(pingAPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingAPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingAPin, LOW);
  durationA = pulseIn(echoAPin, HIGH);
  distanceA = microsecondsToCentimeters(durationA);
  Serial.print("A: ");
  Serial.print(distanceA);
  Serial.print("cm");
  Serial.println();

  led_loop();

  if (distanceA < 5)
  {
    sensorA = 1;

    if (sensorA == 1)
    {

      FSM();
    }
  }
  else
  {
    sensorA = 0;
  }

}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void FSM()
{
  int s = 1000; // 1 second

  switch (FSM_state)
  {

  case 0: // when sensorA == 1 && FSM == 0
    FSM_state = 1;
    break;

  case 1:         // when sensorA == 1 && FSM == 1
    r = millis(); // start timer
    FSM_state = 2;
    break;

  case 2: // when sensorA == 1 && FSM == 2

    delay(60);
    digitalWrite(pingBPin, LOW); // start sensorB
    delayMicroseconds(2);
    digitalWrite(pingBPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingBPin, LOW);
    durationB = pulseIn(echoBPin, HIGH);
    distanceB = microsecondsToCentimeters(durationB);
    Serial.print("B: ");
    Serial.print(distanceB);
    Serial.print("cm");
    Serial.println();
    x = millis() - r; // time between now and sensor1 == 1

    if ((distanceB < 5) && (x < s))
    { // sensor B active : A => B

      FSM_state = 3;
    }
    else
    { // sensor B not active : B => A
      FSM_state = 4;
    }
    break;

  case 3: // when sensorA==1 && FSM == 3, both sensors are active : A => B
    // LED off
    led_off();
    Serial.println();
    Serial.print("-------------- A => B --------------------");
    Serial.println();
    FSM_state = 0; // FSM set to 0
    break;

  case 4: // when sensor1==1 && FSM == 4, sensor 2 not activated: B => A
    led_move_down();
    Serial.println();
    Serial.print("--------------- B => A ------------------");
    Serial.println();
    delay(200);
    FSM_state = 0; // FSM set to 0
    break;
  }
}

void led_loop()
{
  digitalWrite(ledPinA, ledA_state);
  digitalWrite(ledPinB, ledB_state);
  digitalWrite(ledPinC, ledC_state);
  digitalWrite(ledPinD, ledD_state);
}

void led_move_down()
{
  
  ledA_state = HIGH;
  digitalWrite(ledPinA, ledA_state);
  delay(200);
  
  ledB_state = HIGH;
  digitalWrite(ledPinB, ledB_state);
  delay(200);
  
  ledB_state = HIGH;
  digitalWrite(ledPinC, ledB_state);
  delay(200);
  
  ledB_state = HIGH;
  digitalWrite(ledPinD, ledB_state);
}

void led_off()
{
  ledD_state = LOW;
  digitalWrite(ledPinD, ledD_state);
  delay(200);
  ledC_state = LOW;
  digitalWrite(ledPinC, ledC_state);
  delay(200);
  ledB_state = LOW;
  digitalWrite(ledPinB, ledB_state);
  delay(200);
  ledA_state = LOW;
  digitalWrite(ledPinA, ledA_state);
}
