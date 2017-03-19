

#define left1 7 
#define left_pwm 6 
#define left2 5 

#define right1 2
#define right_pwm 4
#define right2 3
char incomingByte;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  pinMode(left1, OUTPUT);
  pinMode(left_pwm, OUTPUT);
  pinMode(left2, OUTPUT);

  pinMode(right1, OUTPUT);
  pinMode(right_pwm, OUTPUT);
  pinMode(right2, OUTPUT);

   left_stop();
  right_stop();


}

void loop() {

  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    // if available, blink LED and print serial data received.
    digitalWrite(13, HIGH);
    // delay 10 milliseconds to allow serial update time
    delay(10);

     //Forward
    if (incomingByte == 'F')
    {
      Serial.println("Forward");
      left_forward(160);
      right_forward(160);
      delay(5);
    }

    //Left
    else if (incomingByte == 'L')
    {
      Serial.println("Left fast");
      left_reverse(160);
      right_forward(160);
      delay(5);
    }

    //Right
    else if (incomingByte == 'R')
    {
      Serial.println("Right fast");
      left_forward(160);
      right_reverse(160);
      delay(5);
    }

    //Front Left
    else if (incomingByte == 'G')
    {
      Serial.println("Front Left");
      left_stop();
      right_forward(160);
      delay(5);
    }

    //Front Right
    else if (incomingByte == 'I')
    {
      Serial.println("Front Right");
      left_forward(160);
      right_stop();
      delay(5);
    }

    //Back Left
    else if (incomingByte == 'H')
    {
      Serial.println("Back Left");
      left_stop();
      right_reverse(160);
      delay(5);
    }

    //Back Right
     else if (incomingByte == 'J')
    {
      Serial.println("Back Right");
      left_reverse(160);
      right_stop();
      delay(5);
    }

    //Reverse
    else if (incomingByte == 'B')
    {
      Serial.println("Reverse");
      left_reverse(160);
      right_reverse(160);
      delay(5);
    }
    
    // otherwise, stop both motors
  }
}
  void left_forward(int x)
{
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  analogWrite(left_pwm, x);
}

void left_reverse(int x)
{
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  analogWrite(left_pwm, x);
}

void left_stop()
{
  digitalWrite(left2, LOW);
  digitalWrite(left1, LOW);
  digitalWrite(left_pwm, LOW);
}
void right_stop()
{
  digitalWrite(right2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right_pwm, LOW);
}
void right_forward(int y)
{
  digitalWrite(right2, HIGH);
  digitalWrite(right1, LOW);
  analogWrite(right_pwm, y);
}

void right_reverse(int y)
{
  digitalWrite(right2, LOW);
  digitalWrite(right1, HIGH);
  analogWrite(right_pwm, y);
}
