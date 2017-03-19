#define red_LED 43
#define green_LED 29

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

  // declare outputs
  pinMode(red_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);  
}

void loop() {

  digitalWrite(red_LED,HIGH);
      digitalWrite(green_LED,LOW);

  delay(500);
    digitalWrite(red_LED,LOW);

    digitalWrite(green_LED,HIGH);
    delay(500);

  // put your main code here, to run repeatedly:

}
