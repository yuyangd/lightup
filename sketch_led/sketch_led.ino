// test out our LEDs

#define ledPinA 10

void setup()
{
  Serial.begin(9600);
  pinMode(ledPinA, OUTPUT);
}

void loop()
{
  digitalWrite(ledPinA, HIGH);

//  delay(1000);
//
//  digitalWrite(ledPinA, LOW);
//
//  delay(1000);
}
