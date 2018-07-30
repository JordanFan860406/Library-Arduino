#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // Arduino RX:4, TX:5  
void setup()
{
  // Open serial communications and wait for port to open:
  mySerial.begin(115200);
  Serial.begin(115200);
//  while (!mySerial) {
//    Serial.write("YES")
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }
  
}
void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}
