#include <SoftwareSerial.h>
#include "Timer.h"
Timer t;
SoftwareSerial debug(10,11); // make RX Arduino line is pin 4, make TX Arduino line is pin 5.
#define SSID "chts230"
#define PASS "12345678"
void setup(){
  Serial.begin(115200);
  debug.begin(115200); // your esp's baud rate might be different
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW);
  t.every(500, Wifi_main);
}
void loop(){
  t.update();
}
int Wifi_State,delaytime;
String cmd;
void Wifi_main(){
  switch (Wifi_State) {
    case 0://--------------------------------------------------Test Wifi Module
      sendDebug("AT");
      if (Loding("Sent AT")){ 
        Wifi_State++;
      }
    break;
    case 1://--------------------------------------------------Wifi Mode
      sendDebug("AT+CWMODE=3");
      if (Loding("AT+CWMODE=3")){ 
        Wifi_State++;
      }
    break;
    case 2://--------------------------------------------------Wifi connect
      cmd="AT+CWJAP=\"";
      cmd+=SSID;
      cmd+="\",\"";
      cmd+=PASS;
      cmd+="\"";
      sendDebug(cmd);
      Wifi_State++;
      if (Loding("Wifi connect")){ 
        Wifi_State++; //next setting wifi mode
      }
      else{Wifi_State--;}
    break;
    case 3://--------------------------------------------------Get ip address 數據機"http://192.168.0.6:8888/"  手機熱點" http://172.20.10.8:8888/pin="  <=== ip 
      sendDebug("AT+CIFSR");
      if (Loding("Get ip address")){ //delay 1 sec
        Wifi_State++; //next setting wifi mode
      }
      else{Wifi_State--;}
    break;
    case 4://--------------------------------------------------configure for multiple connections
      sendDebug("AT+CIPMUX=1");
      if (Loding("Set CIPMUX")){ 
          Wifi_State++; //next setting wifi mode
      }
      else{Wifi_State--;}
    break;
    case 5://--------------------------------------------------turn on server on port 8888
      sendDebug("AT+CIPSERVER=1,8888");
      Wifi_State++; //next setting wifi mode
    break;
    case 6:// check if the esp is sending a message 
      if(debug.available()) {
        if(debug.find("+IPD,")){
          Serial.println(123);
          Wifi_State++;
          }
      }
    break;
    case 7:// wait for the serial buffer to fill up (read all the serial data)
        delay(10);
        //int connectionId = debug.read()-48; // subtract 48 because the read() function returns 
        Serial.println(debug.read());
        // the ASCII decimal value and 0 (the first decimal number) starts at 4
//        debug.find("pin="); // advance cursor to "pin="
//        int pinNumber = (debug.read()-48); // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
        // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
        //digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin    
        // make close command
        int pinNumber;
        String str=get_response();  //取得 ESP8266 回應字串
        Serial.println(str);
        if (str.indexOf("pin=3") !=-1) {
           pinNumber = 3;
           digitalWrite(pinNumber, !digitalRead(pinNumber));
           close_ip();
           return "OK";
        }  //傳送成功會自動拆線
        else if (str.indexOf("pin=4") !=-1){  //傳送不成功須自行拆線
          pinNumber = 4;
          digitalWrite(pinNumber, !digitalRead(pinNumber));
          close_ip();  //關閉 IP 連線 
          return "OK";
        }
        else if (str.indexOf("pin=5") !=-1){  //傳送不成功須自行拆線
          pinNumber = 5;
          digitalWrite(pinNumber, !digitalRead(pinNumber));
          close_ip();  //關閉 IP 連線 
          return "OK";
        }   
        else if (str.indexOf("pin=6") !=-1){  //傳送不成功須自行拆線
          pinNumber = 6;
          digitalWrite(pinNumber, !digitalRead(pinNumber));
          close_ip();  //關閉 IP 連線 
          return "OK";
        }      
//        String closeCommand = "AT+CIPCLOSE="; 
//        closeCommand+=connectionId; // append connection id
//        closeCommand+="\r\n";
        Serial.print("Turn Pin");
        Serial.print(pinNumber);
        Serial.print(":");
        Serial.print(digitalRead(pinNumber));
        Serial.println("!");
        //sendDebug(closeCommand); // close connection
        Wifi_State--; //next setting wifi mode
     break;
  }
}
String get_response() {  //get esp responce without "Serial.find()".
  String response="";  
  char c; 
  while (debug.available()) {  
    c=debug.read();
    response.concat(c);   
    delay(10);  
    }
  response.trim();  
  return response;
}
boolean Loding(String state){
  String response=get_response();
  for (int timeout=0 ; timeout<30 ; timeout++)
  {
    if(response.indexOf("OK") != -1 || response.indexOf("no change") != -1) 
    {
        Serial.print(" OK ! ");
        if(timeout>=2){
          Serial.print("This commend waste ");
          Serial.print(timeout/2);
          Serial.println(" sec.");
        }
        else Serial.println("");
        return 1; 
        break;
    }
    else if(timeout==29){ //after 15 sec for wait esp without responce.
      Serial.print(state);
      Serial.println(" fail...\nExit2");
      return 0; 
    }
    else{
      response=get_response(); //reget
      if(timeout==0)
        Serial.print("Wifi Loading.");
      else
        Serial.print(".");
      delay(500);
    }
  }
}
void sendDebug(String sent_cmd)
{
    Serial.print("SEND: ");
    Serial.println(sent_cmd);
    debug.println(sent_cmd);
} 
String close_ip() {
  debug.println("AT+CIPCLOSE");  //關閉 IP 連線
  debug.flush();  //等待序列埠傳送完畢
  delay(1000);
  String str=get_response();  //取得 ESP8266 回應字串
  if (str.indexOf("OK") != -1) {return "OK";}
  else {return "NG";}
}
