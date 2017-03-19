#define threshold_min 175
#define low_threshold_weight 500

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

/*int a[2][7]={{26, 28, 30, 32, 34, 36, 38},
              {42, 40, 44, 46, 48, 50, 53}};*/

// variable to store speed value
int l_speed_val = 0, l_last_speed=0;
int r_speed_val = 0, r_last_speed=0;
int pressure=0;
int cylinder=0, cube=0, flag=-1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  //7-segment display for cylinder
 /* pinMode(42, OUTPUT);
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
  pinMode(38, OUTPUT);*/
 
 
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

  //delay(200);

  char str[5];
  int i=0;
  Serial1.print("Enter the string: ");
  while(i<5)
  {
    if(Serial1.available() > 0)
    {
      str[i]=Serial1.read();
      //Serial.print(char(str[i]));
      Serial1.print(char(str[i]));
      i++;
    }
  }
   digitalWrite(red_LED,HIGH);
   digitalWrite(green_LED,HIGH);
  
    
  cube = (int)str[1] - 48;
  Serial1.println(cube);
  //segment_compare(cube, 0);
  cylinder = (int)str[3] - 48;
    Serial1.println(cylinder);

  //segment_compare(cylinder, 1);

  delay(2000);
   digitalWrite(red_LED,LOW);
  digitalWrite(green_LED,LOW);
  //segment_compare(10,0);
  //segment_compare(10,1);
delay(1000);
  glow_led(cube,cylinder);
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
      l_speed_val = 0;
      r_speed_val = 0;
    }

    else if (incomingByte == '1')
    {
      l_speed_val = 190;
      r_speed_val = 190;
    }
    
    else if (incomingByte == '2')
    {
      l_speed_val = 195;
      r_speed_val = 195;
    }
    
    else if (incomingByte == '3')
    {
      l_speed_val = 200;
      r_speed_val = 190;
    }
    
    else if (incomingByte == '4')
    {
      l_speed_val = 225;
      r_speed_val = 205;
    }
    
    else if (incomingByte == '5')
    {
      l_speed_val = 230;
      r_speed_val = 215;
    }
    
    else if (incomingByte == '6')
    {
      l_speed_val = 235;
      r_speed_val = 220;
    }
    
    else if (incomingByte == '7')
    {
      l_speed_val = 240;
      r_speed_val = 215;
    }
    
    else if (incomingByte == '8')
    {
      l_speed_val = 245;
      r_speed_val = 220;
    }
    
    else if (incomingByte == '9')
    {
      l_speed_val = 250;
      r_speed_val = 225;
    }
    
    else if (incomingByte == 'q')
    {
      l_speed_val = 255;
      r_speed_val = 230;
    }
     
    //Forward
    else if (incomingByte == 'F')
    {
      Serial.println("Forward");
      left_forward(l_speed_val);
      right_forward(r_speed_val);
      delay(10);
    }

    //Left
    else if (incomingByte == 'L')
    {
      Serial.println("Left fast");
      left_reverse(l_speed_val);
      right_forward(r_speed_val);
            delay(10);

    }

    //Right
    else if (incomingByte == 'R')
    {
      Serial.println("Right fast");
      left_forward(l_speed_val);
      right_reverse(r_speed_val);
            delay(10);

    }

    //Front Left
    else if (incomingByte == 'G')
    {
      Serial.println("Front Left");
      left_stop();
      right_forward(r_speed_val);
            delay(10);


    }

    //Front Right
    else if (incomingByte == 'I')
    {
      Serial.println("Front Right");
      left_forward(l_speed_val);
      right_stop();
            delay(10);

    }

    //Back Left
    else if (incomingByte == 'H')
    {
      Serial.println("Back Left");
      left_stop();
      right_reverse(r_speed_val);
            delay(10);

    }

    //Back Right
     else if (incomingByte == 'J')
    {
      Serial.println("Back Right");
      left_reverse(l_speed_val);
      right_stop();
            delay(10);

    }

    //Reverse
    else if (incomingByte == 'B')
    {
      Serial.println("Reverse");
      left_reverse(l_speed_val);
      right_reverse(r_speed_val);
            delay(10);

    }

    else if (incomingByte == 'X')
    {
      
        digitalWrite(red_LED, HIGH);
        digitalWrite(green_LED, LOW);
        delay(250);
        digitalWrite(red_LED, LOW);
        digitalWrite(green_LED, HIGH);
        delay(250);
        digitalWrite(red_LED, HIGH);
        digitalWrite(green_LED, LOW);
        delay(250);
        digitalWrite(red_LED, LOW);
        digitalWrite(green_LED, HIGH);
        delay(250);
        digitalWrite(red_LED, HIGH);
        digitalWrite(green_LED, LOW);
        delay(250);
        digitalWrite(red_LED, LOW);
        digitalWrite(green_LED, HIGH);
        delay(250);
        digitalWrite(red_LED, HIGH);
        digitalWrite(green_LED, LOW);
        delay(250);
        digitalWrite(red_LED, LOW);
        digitalWrite(green_LED, HIGH);
        delay(250);
        digitalWrite(red_LED, HIGH);
        digitalWrite(green_LED, LOW);
        delay(250);
        digitalWrite(red_LED, LOW);
        digitalWrite(green_LED, HIGH);
        delay(250);
      digitalWrite(red_LED, LOW);
      digitalWrite(green_LED, LOW);
    }

    else if (incomingByte == 'V')
    {
      l_last_speed=l_speed_val;
      r_last_speed=r_speed_val;
      l_speed_val=170;
      r_speed_val=170;
      delay(10);
    }

    else if (incomingByte == 'v')
    {
      l_speed_val=l_last_speed;
      r_speed_val=r_last_speed;
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

//////////////sensor process weight////////////
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

void glow_led(int c,int d)
{
  for(int i=0; i<c; i++)
  {
    digitalWrite(red_LED,LOW);
    digitalWrite(green_LED,HIGH);
    delay(500);
    digitalWrite(red_LED,LOW);
    digitalWrite(green_LED,LOW);
    delay(500);
  }
  for(int j=0; j<d; j++)
  {
    digitalWrite(red_LED,HIGH);
    digitalWrite(green_LED,LOW);
    delay(500);
    digitalWrite(red_LED,LOW);
    digitalWrite(green_LED,LOW);
    delay(500);
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
/*
//7 segment display
void zero(int type)
{
  //0
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], LOW);
  digitalWrite(a[type][4], LOW);
  digitalWrite(a[type][5], LOW);
  digitalWrite(a[type][6], HIGH);
}

void one(int type)
{
  //1
  digitalWrite(a[type][0], HIGH);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], HIGH);
  digitalWrite(a[type][4], HIGH);
  digitalWrite(a[type][5], HIGH);
  digitalWrite(a[type][6], HIGH);
}

void two(int type)
{
  //2
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], HIGH);
  digitalWrite(a[type][3], LOW);
  digitalWrite(a[type][4], LOW);
  digitalWrite(a[type][5], HIGH);
  digitalWrite(a[type][6], LOW);
}

void three(int type)
{
  //3
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], LOW);
  digitalWrite(a[type][4], HIGH);
  digitalWrite(a[type][5], HIGH);
  digitalWrite(a[type][6], LOW);
}

void four(int type)
{
  //4
  digitalWrite(a[type][0], HIGH);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], HIGH);
  digitalWrite(a[type][4], HIGH);
  digitalWrite(a[type][5], LOW);
  digitalWrite(a[type][6], LOW);
}

void five(int type)
{
  //5
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], HIGH);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], LOW);
  digitalWrite(a[type][4], HIGH);
  digitalWrite(a[type][5], LOW);
  digitalWrite(a[type][6], LOW);
}

void six(int type)
{
  //6
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], HIGH);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], LOW);
  digitalWrite(a[type][4], LOW);
  digitalWrite(a[type][5], LOW);
  digitalWrite(a[type][6], LOW);
}

void seven(int type)
{
  //7
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], HIGH);
  digitalWrite(a[type][4], HIGH);
  digitalWrite(a[type][5], HIGH);
  digitalWrite(a[type][6], HIGH);
}

void eight(int type)
{
  //8
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], LOW);
  digitalWrite(a[type][4], LOW);
  digitalWrite(a[type][5], LOW);
  digitalWrite(a[type][6], LOW);
}

void nine(int type)
{
  //9
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], LOW);
  digitalWrite(a[type][4], HIGH);
  digitalWrite(a[type][5], LOW);
  digitalWrite(a[type][6], LOW);
}

void off(int type)
{
  digitalWrite(a[type][0], LOW);
  digitalWrite(a[type][1], LOW);
  digitalWrite(a[type][2], LOW);
  digitalWrite(a[type][3], LOW);
  digitalWrite(a[type][4], LOW);
  digitalWrite(a[type][5], LOW);
  digitalWrite(a[type][6], LOW);
}

/*
void segment_compare(int temp, int type)
{
  if(temp == 0)
    zero(type);
  else if(temp == 1)
    one(type);
  else if(temp == 2)
    two(type);
  else if(temp == 3)
    three(type);
  else if(temp == 4)
    four(type);
  else if(temp == 5)
    five(type);
  else if(temp == 6)
    six(type);
  else if(temp == 7)
    seven(type);
  else if(temp == 8)
    eight(type);
  else if(temp == 9)
    nine(type);
  else
      off(type);
}*/
