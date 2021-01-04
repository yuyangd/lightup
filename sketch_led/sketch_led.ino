// test out our LEDs

#define ledPinA 11
#define ledPinB 12
#define ledPinC 13

void setup()
{
  Serial.begin(9600);
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinC, OUTPUT);
}

void loop()
{
  digitalWrite(ledPinA, HIGH);
  digitalWrite(ledPinB, HIGH);
  digitalWrite(ledPinC, HIGH);
  Serial.println("HELLO");
//  delay(1000);
//
//  digitalWrite(ledPinA, LOW);
//
//  delay(1000);
}
