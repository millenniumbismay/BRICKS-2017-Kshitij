void setup() {
  // put your setup code here, to run once:
  //7-segment display for cylinder
  pinMode(42, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(53, OUTPUT);

  //7-segment display for cube
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(38, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(26, HIGH);
  digitalWrite(28, LOW);
  digitalWrite(30, LOW);
  digitalWrite(32, HIGH);
  digitalWrite(34, HIGH);
  digitalWrite(36, HIGH);
  digitalWrite(38, HIGH);
  //delay(2000);
  
  /*digitalWrite(26, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(30, HIGH);
  digitalWrite(32, HIGH);
  digitalWrite(34, HIGH);
  digitalWrite(36, HIGH);
  digitalWrite(38, HIGH);
*/
  digitalWrite(42, HIGH);
  digitalWrite(40, LOW);
  digitalWrite(44, LOW);
  digitalWrite(46, HIGH);
  digitalWrite(48, HIGH);
  digitalWrite(50, HIGH);
  digitalWrite(53, HIGH);
  //delay(2000);
/*
  digitalWrite(42, HIGH);
  digitalWrite(40, HIGH);
  digitalWrite(44, HIGH);
  digitalWrite(46, HIGH);
  digitalWrite(48, HIGH);
  digitalWrite(50, HIGH);
  digitalWrite(53, HIGH);
 */ 
}
