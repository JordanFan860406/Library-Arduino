#include <IRremote.h>
#include <SoftwareSerial.h>
int RECV_PIN = 3;
int count = 0;
String id="1";
IRrecv irrecv(RECV_PIN);
boolean temp = false; 
decode_results results;
const int btnPin = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(btnPin, INPUT);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(btnPin)==1){
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    count = 0;
    dataReset();
    delay(500);
  }
  if(irrecv.decode(&results)){
    if(results.value==0x77E14050){
      if(temp){
        temp = false;
        count++;
      }
      //Serial.println("Yes");
    }
    else{
      //Serial.println(results.value, HEX);
      temp = true;
    }
    irrecv.resume();
  }
//  Serial.print("次數: ");
//  Serial.println(count);
  if(count>=10 && count<20){
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
  if(count>=20 && count<30){
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
  }
  if(count==30){
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
    sendNum();
    Serial.println(123);
    count++;
  }
  if(count>=31){
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
//    Serial.print("次數: ");
//    Serial.println(count);
  }
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
  if (response.indexOf("OK") !=-1){
    Serial.println(response);
  }
  if (response.indexOf("receive") !=-1){
    Serial.println(response);
  }
}

void sendNum()
{
    String num = "time="+String(count)+"&id="+id;
    Serial.println(num); 
}
void dataReset()
{
    String num = "time=0+&id=1";
    Serial.println(num); 
}
