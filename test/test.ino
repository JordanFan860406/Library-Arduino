#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("Goodnight moon!");
  mySerial.begin(115200);
  mySerial.println("Hello WorLd");
}

void loop() { // run over and over
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  
}

