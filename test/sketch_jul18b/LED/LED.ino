#include <IRremote.h>
IRsend irsend;
void setup() {
 Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 50; i++) { 
    irsend.sendNEC(0x77E14050, 32); // Sony电视电源开关编码
    delay(10); 
  } 

}
