#include <IRremote.h>
int RECV_PIN = 3;
int count = 0;
IRrecv irrecv(RECV_PIN);
boolean temp = false;
decode_results results;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results)){
    if(results.value==0x77E14050){
      if(temp){
        temp = false;
        count++;
      }
      Serial.println("Yes");
    }
    else{
      Serial.println(results.value, HEX);
      temp = true;
    }
    irrecv.resume();
  }
  Serial.print("次數: ");
  Serial.println(count);
  if(count>=10){
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
  if(count>=20){
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
  }
  if(count>=30){
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
  }
}
