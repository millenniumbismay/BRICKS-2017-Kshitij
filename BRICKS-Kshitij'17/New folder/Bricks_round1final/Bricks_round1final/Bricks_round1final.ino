#define threshold_min 200
#define low_threshold_weight 600


#define sensor A6

#define left1 7 
#define left_pwm 6 
#define left2 5 

#define right1 3
#define right_pwm 4
#define right2 2

#define lift1 9    
#define lift_pwm 11
#define lift2 10 

// LED pin attached to Arduino D6
#define red_LED 43
#define green_LED 29

// variable to store serial data
char incomingByte = 0;

// variable to store speed value
int speed_val = 0;
int pressure=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // declare outputs
  pinMode(red_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  
  pinMode(left1, OUTPUT);
  pinMode(left_pwm, OUTPUT);
  pinMode(left2, OUTPUT);

  pinMode(right1, OUTPUT);
  pinMode(right_pwm, OUTPUT);
  pinMode(right2, OUTPUT);

  pinMode(lift1, OUTPUT);
  pinMode(lift_pwm, OUTPUT);
  pinMode(lift2, OUTPUT);

  // turn motors Off by default
  left_stop();
  right_stop();
  lift_stop();

  delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // check for serial data
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    // if available, blink LED and print serial data received.
    digitalWrite(13, HIGH);
    // delay 10 milliseconds to allow serial update time
    delay(10);

    if (incomingByte == 'W')
    {
      lift_up();
      while(incomingByte != 'w')
        if(Serial.available() > 0)
          incomingByte = Serial.read();
      lift_stop();      
    }

    else if (incomingByte == 'U')
    {
      lift_down();
      while(incomingByte != 'u')
        if(Serial.available() > 0)
          incomingByte = Serial.read();
      lift_stop();
    }

    else if (incomingByte == '0')
    {
      speed_val = 0;
    }

    else if (incomingByte == '1')
    {
      speed_val = 190;
    }
    
    else if (incomingByte == '2')
    {
      speed_val = 195;
    }
    
    else if (incomingByte == '3')
    {
      speed_val = 200;
    }
    
    else if (incomingByte == '4')
    {
      speed_val = 225;
    }
    
    else if (incomingByte == '5')
    {
      speed_val = 230;
    }
    
    else if (incomingByte == '6')
    {
      speed_val = 235;
    }
    
    else if (incomingByte == '7')
    {
      speed_val = 240;
    }
    
    else if (incomingByte == '8')
    {
      speed_val = 245;
    }
    
    else if (incomingByte == '9')
    {
      speed_val = 250;
    }
    
    else if (incomingByte == 'q')
    {
      speed_val = 255;
    }
     
    //Forward
    else if (incomingByte == 'F')
    {
      Serial.println("Forward");
      left_forward(speed_val);
      right_forward(speed_val);
      delay(10);
    }

    //Left
    else if (incomingByte == 'L')
    {
      Serial.println("Left fast");
      left_reverse(speed_val);
      right_forward(speed_val);
            delay(10);

    }

    //Right
    else if (incomingByte == 'R')
    {
      Serial.println("Right fast");
      left_forward(speed_val);
      right_reverse(speed_val);
            delay(10);

    }

    //Front Left
    else if (incomingByte == 'G')
    {
      Serial.println("Front Left");
      left_stop();
      right_forward(speed_val);
            delay(10);


    }

    //Front Right
    else if (incomingByte == 'I')
    {
      Serial.println("Front Right");
      left_forward(speed_val);
      right_stop();
            delay(10);

    }

    //Back Left
    else if (incomingByte == 'H')
    {
      Serial.println("Back Left");
      left_stop();
      right_reverse(speed_val);
            delay(10);

    }

    //Back Right
     else if (incomingByte == 'J')
    {
      Serial.println("Back Right");
      left_reverse(speed_val);
      right_stop();
            delay(10);

    }

    //Reverse
    else if (incomingByte == 'B')
    {
      Serial.println("Reverse");
      left_reverse(speed_val);
      right_reverse(speed_val);
            delay(10);

    }
    
      // otherwise, stop both motors
    else 
    {
      Serial.println("Stop");
      left_stop();
      right_stop();
    }
    process_weight();
  }
}

void process_weight()
{
  //pressure=calc_pressure();
  if((analogRead(sensor))<threshold_min)
  {
    digitalWrite(red_LED,LOW);
    digitalWrite(green_LED,LOW);
  }
  else if((analogRead(sensor))<low_threshold_weight)
  {
    digitalWrite(red_LED,HIGH);
    digitalWrite(green_LED,LOW);
  }
  else
  {
    digitalWrite(red_LED,LOW);
    digitalWrite(green_LED,HIGH);
  }
}


/////////// motor functions ////////////////

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

void right_stop()
{
  digitalWrite(right2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right_pwm, LOW);
}

void lift_up()
{
  digitalWrite(lift2, LOW);
  digitalWrite(lift1, HIGH);
  analogWrite(lift_pwm, 250);
}

void lift_down()
{
  digitalWrite(lift1, LOW);
  digitalWrite(lift2, HIGH);
  analogWrite(lift_pwm, 250);
}

void lift_stop()
{
  digitalWrite(lift2, LOW);
  digitalWrite(lift1, LOW);
  digitalWrite(lift_pwm, LOW);
}

