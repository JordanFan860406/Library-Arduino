#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // Arduino RX:4, TX:5  
void setup()
{
  // Open serial communications and wait for port to open:
  mySerial.begin(115200);
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
//  while (!mySerial) {
//    Serial.write("YES")
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }
  
}
void loop() // run over and over
{ 
  String response="";  
  char c; 
  while (Serial.available()) {  
    c=Serial.read();
    response.concat(c);   
    delay(10);  
    }
  response.trim(); 
  if (response.indexOf("New") !=-1){
    Serial.println(response);
  }
  if (response.indexOf("IP") !=-1){
    Serial.println(response);
  }
  if (response.indexOf("pin=3") !=-1){
    digitalWrite(13,HIGH);
  }
  if (response.indexOf("pin=4") !=-1){
    digitalWrite(13,LOW);
  }
  
   
}
