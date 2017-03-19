#define red_LED 43
#define green_LED 29

char incomingByte=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(green_LED, OUTPUT);
    pinMode(red_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    incomingByte=Serial.read();
if (incomingByte == 'X')
    {
      while(incomingByte != 'x')
      {
        digitalWrite(red_LED, HIGH);
        digitalWrite(green_LED, LOW);
        delay(500);
        digitalWrite(red_LED, LOW);
        digitalWrite(green_LED, HIGH);
        delay(500);
        if(Serial.available() > 0)
          incomingByte = Serial.read();
      }
    }
      digitalWrite(red_LED, LOW);
      digitalWrite(green_LED, LOW);
      delay(10);
    }
}
