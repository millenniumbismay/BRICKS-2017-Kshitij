#define threshold_min 100
#define low_threshold_weight 565
#define sensor A0

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
#define red_LED 6
#define green_LED 7

// variable to store serial data
char incomingByte = 0;

// variable to store speed value
int speed_val = 0, cylinder=0, cube=0, flag=-1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);

  //7-segment display
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
 
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

  char str[5];
  int i=0;
  Serial1.print("Enter the string: ");
  while(i<5)
    if(Serial1.available() > 0)
    {
      str[i]=Serial1.read();
      i++;
    }
  Serial1.print(str);
  cube = (int)str[1] - 48;
  segment_compare(cube);
  cylinder = (int)str[3] - 48;
  segment_compare(cylinder);  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!(cube || cylinder))
    while(1)
    {
      digitalWrite(red_LED, HIGH);
      digitalWrite(green_LED, LOW);
      delay(250);
      digitalWrite(red_LED, LOW);
      digitalWrite(green_LED, HIGH);
      delay(250);
    }
  // check for serial data
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();
    // if available, blink LED and print serial data received.
    digitalWrite(13, HIGH);
    // delay 10 milliseconds to allow serial update time
    delay(10);

    if (incomingByte == 'V' || incomingByte == 'v')
    {
      segment_compare(cube);
      if(cube==0)
      {
        digitalWrite(red_LED, HIGH);
        delay(500);
        digitalWrite(red_LED, LOW);
        delay(500);
        digitalWrite(red_LED, HIGH);
        delay(500);
        digitalWrite(red_LED, LOW);
        delay(500);
        digitalWrite(red_LED, HIGH);
        delay(500);
        digitalWrite(red_LED, LOW);
      }
      else
      {
        flag=0;
        digitalWrite(green_LED, HIGH);
        delay(500);
        digitalWrite(green_LED, LOW);
        delay(500);
        digitalWrite(green_LED, HIGH);
        delay(500);
        digitalWrite(green_LED, LOW);
        delay(500);
        digitalWrite(green_LED, HIGH);
        delay(500);
        digitalWrite(green_LED, LOW);
      }
    }
.........................................
    else if (incomingByte == 'X' || incomingByte == 'x')
    {
      segment_compare(cylinder);
      if(cylinder==0)
      {
        digitalWrite(red_LED, HIGH);
        delay(500);
        digitalWrite(red_LED, LOW);
        delay(500);
        digitalWrite(red_LED, HIGH);
        delay(500);
        digitalWrite(red_LED, LOW);
        delay(500);
        digitalWrite(red_LED, HIGH);
        delay(500);
        digitalWrite(red_LED, LOW);
      }
      else
      {
        flag=1;
        digitalWrite(green_LED, HIGH);
        delay(500);
        digitalWrite(green_LED, LOW);
        delay(500);
        digitalWrite(green_LED, HIGH);
        delay(500);
        digitalWrite(green_LED, LOW);
        delay(500);
        digitalWrite(green_LED, HIGH);
        delay(500);
        digitalWrite(green_LED, LOW);
      }
    }
    
    else if (incomingByte == 'W')
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
      speed_val = 20;
    }
    
    else if (incomingByte == '2')
    {
      speed_val = 40;
    }
    
    else if (incomingByte == '3')
    {
      speed_val = 60;
    }
    
    else if (incomingByte == '4')
    {
      speed_val = 80;
    }
    
    else if (incomingByte == '5')
    {
      speed_val = 100;
    }
    
    else if (incomingByte == '6')
    {
      speed_val = 120;
    }
    
    else if (incomingByte == '7')
    {
      speed_val = 140;
    }
    
    else if (incomingByte == '8')
    {
      speed_val = 160;
    }
    
    else if (incomingByte == '9')
    {
      speed_val = 180;
    }
    
    else if (incomingByte == 'q')
    {
      speed_val = 200;
    }
     
    //Forward
    else if (incomingByte == 'F')
    {
      Serial.println("Forward");
      left_forward(speed_val);
      right_forward(speed_val);
      delay(25);
    }

    //Left
    else if (incomingByte == 'L')
    {
      Serial.println("Left fast");
      left_reverse(speed_val);
      right_forward(speed_val);
      delay(25);
    }

    //Right
    else if (incomingByte == 'R')
    {
      Serial.println("Right fast");
      left_forward(speed_val);
      right_reverse(speed_val);
      delay(25);
    }

    //Front Left
    else if (incomingByte == 'G')
    {
      Serial.println("Front Left");
      left_stop();
      right_forward(speed_val);
      delay(25);
    }

    //Front Right
    else if (incomingByte == 'I')
    {
      Serial.println("Front Right");
      left_forward(speed_val);
      right_stop();
      delay(25);
    }

    //Back Left
    else if (incomingByte == 'H')
    {
      Serial.println("Back Left");
      left_stop();
      right_reverse(speed_val);
      delay(25);
    }

    //Back Right
     else if (incomingByte == 'J')
    {
      Serial.println("Back Right");
      left_reverse(speed_val);
      right_stop();
      delay(25);
    }

    //Reverse
    else if (incomingByte == 'B')
    {
      Serial.println("Reverse");
      left_reverse(speed_val);
      right_reverse(speed_val);
      delay(25);
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

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                id process_weight()
{
   int a[20];
  int i;
  int sum=0;
  int pressure;
  for(i=0;i<20;i++)
  {
    a[i]=analogRead(sensor);
    sum=sum+a[0];
  }
  
  pressure=sum/20;
  if(pressure<threshold_min)
  {
    digitalWrite(red_LED,LOW);
    digitalWrite(green_LED,LOW);
  }
  else if(pressure<threshold_weight)
  {
    digitalWrite(red_LED,HIGH);----------
    digitalWrite(green_LED,LOW);
  }
  else
  {
    digitalWrite(red_LED,LOW);
    digitalWrite(green_LED,HIGH);
    if(flag==0)
      --cube;
    else
      --cylinder;
    flag=-1;
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
  analogWrite(lift_pwm, 50);
}

void lift_down()
{
  digitalWrite(lift1, LOW);
  digitalWrite(lift2, HIGH);
  analogWrite(lift_pwm, 50);
}

void lift_stop()
{
  digitalWrite(lift2, LOW);
  digitalWrite(lift1, LOW);
  digitalWrite(lift_pwm, LOW);
}

/////////////////7-segment display/////////////////

void off()
{
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}
void one()
{
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}
void zero()
{
  //0
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  delay(2000);
}

void one()
{
  //1
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  delay(2000);
}

void two()
{
  //2
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
}

void three()
{
  //3
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
}

void four()
{
  //4
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
}

void five()
{
  //5
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
}

void six()
{
  //6
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
}

void seven()
{
  //7
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  delay(2000);
}

void eight()
{
  //8
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
}

void nine()
{
  //9
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
}

void segment_compare(int temp)
{
  if(temp == 0)
    zero();
  else if(temp == 1)
    one();
  else if(temp == 2)
    two();
  else if(temp == 3)
    three();
  else if(temp == 4)
    four();
  else if(temp == 5)
    five();
  else if(temp == 6)
    six();
  else if(temp == 7)
    seven();
  else if(temp == 8)
    eight();
  else if(temp == 9)
    nine();
  else
      off();
  off();
}



