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
//  digitalWrite(ledPinA, HIGH);
//  digitalWrite(ledPinB, HIGH);
//  digitalWrite(ledPinC, HIGH);
  Serial.println("HELLO");
 
  int x;
 for(x=1; x<= 7; x++)
 {
   digitalWrite(ledPinC, x & 4 );   // sets the LED on
   digitalWrite(ledPinB, x & 2 );   // sets the LED on
   digitalWrite(ledPinA, x & 1);   // sets the LED on
 
   delay(200);                  
 }

}
