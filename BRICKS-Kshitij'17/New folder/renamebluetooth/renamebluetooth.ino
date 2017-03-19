int LED = 13;                                     // select the pin for the LED
int RESET = 7;                                    // BT module uses pin 7 for reset

void setup() {
  pinMode(LED,OUTPUT);                            // declare the LED and BT RESET pins as output
  pinMode(RESET,OUTPUT);  

  Serial.begin(115200);                           // connect to the serial port

  digitalWrite(RESET, HIGH);  
  delay(10);
  digitalWrite(RESET, LOW);
  delay(2000);

                                                   // the following "SET BT" commands are one-time commands 
                                                   // that only need to be uploaded to your BT module and run 
                                                   // when you want to change the BlueGiga's configuration.

                                                   // ok. First, the easy to change configuration commands:

    Serial.println("SET BT NAME Arduino_BT");      // you can change the name of your module here. 
                                                   // No spaces allowed in the name; names can be up to 256 charcters.
//  Serial.println("SET BT NAME KarlMarx");        // example


    Serial.println("SET BT AUTH * 12345");         // 12345 == 0 to 16 digit Bluetooth passkey/PIN code

//  Serial.println("SET BT AUTH * 987654321");     // example


                                                   // And now the tricky configuration commands. 
                                                   // Change these only if you know what you're doing. 
                                                   // See the IWRAP manual for details.

  Serial.println("SET CONTROL BAUD 115200,8n1");   // set the BT module serial rate to 115200. Don't change this.

  Serial.println("SET BT PAGEMODE 3 2000 1");      // 3 == IWRAP visible and answers
                                                   // 2000 == 5120ms timeout
                                                   // 1 == iWRAP is connectable every 1.28 sec

  Serial.println("SET BT ROLE 0 f 7d00");          // 0 == allows master-slave switch when calling; 
                                                   // f == enable sniff, park, hold and role switch modes; 
                                                   // 7d00 == keep connection  alive 20 seconds

  Serial.println("SET CONTROL ECHO 0");            // don't echo back module commands

  Serial.println("SET CONTROL ESCAPE - 00 1");     // - == character to escape from comand mode to data mode; 
                                                   // 00 == DTR bitmask; 1 == return to command mode when DTR dropped


}

                                                   // and now a few blinks of the  LED, 
                                                   // so that we know the program is running.

void loop () {                                    
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  Serial.println("ciao");
  delay(1000);
}

