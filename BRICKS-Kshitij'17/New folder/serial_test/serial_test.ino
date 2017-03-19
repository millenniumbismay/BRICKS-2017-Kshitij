void setup() {
  // put your setup code here, to run once:
  char str[5];
  int i=0;
  Serial.begin(9600);
  Serial1.begin(9600);
  while(i<5)
  {
    if(Serial1.available() > 0)
    {
      str[i]=Serial1.read();
      i++;
    }
  }
  Serial.print(char(str[1]));
  Serial.print(char(str[3]));
}

void loop() {
  // put your main code here, to run repeatedly:

}
