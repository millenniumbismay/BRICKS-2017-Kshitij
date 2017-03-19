#define lift1 9    
#define lift_pwm 11
#define lift2 10 

int fsrpin=A6;
int fsrreading;
int pressure;
int a[100];
int sum=0;
int i;
int rms;
char incomingByte=0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial1.begin(9600);

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

void loop() {

  // put your main code here, to run repeatedly:
/* for (i=0;i<100;i++)
  {
     fsrreading=analogRead(fsrpin);
     a[i]=fsrreading;
     sum=a[i]+sum;
  }
  rms=sum/100;
  Serial.println(rms);*/

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
    else{} 
  }

  int a=analogRead(fsrpin);

    if(a>=0 && a<1024)
      Serial1.println(a);
  //delay(100);
  
}
