int DS_pin = 8;
int STCP_pin = 9;
int SHCP_pin = 10;

boolean registers[8];

void writeReg()
{
  digitalWrite(SHCP_pin, LOW);

  for(int i=7; i>=0; i--)
  {
      digitalWrite(STCP_pin, LOW);
      digitalWrite(DS_pin, registers[i]);
      digitalWrite(STCP_pin, HIGH);
  }
  digitalWrite(SHCP_pin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  
    pinMode(DS_pin, OUTPUT);
    pinMode(STCP_pin, OUTPUT);
    pinMode(SHCP_pin, OUTPUT);

    writeReg();  
}

void loop()
{
  
  for(int i = 0; i<8 ; i++)
  {
    registers[i]=HIGH;
    delay(100);
    writeReg();
  }
  for(int i = 8; i>0; i--)
  {
    registers[i]=LOW;
    delay(100);
    writeReg();
  }
}
