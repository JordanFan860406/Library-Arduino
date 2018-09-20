#include <SoftwareSerial.h>
#include <IRremote.h>
#define LEDR 6
#define LEDG 5
#define LEDB 4
int RECV_PIN = 3;
int count = 0;
String address = "henjorly.ddns.net";
int port = 80;
String send ="";
IRrecv irrecv(RECV_PIN);
boolean temp = false;
decode_results results;
SoftwareSerial mySerial(10, 11); // Arduino RX:10, TX:11  
void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
  Serial.begin(115200);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  irrecv.enableIRIn();
  Serial.print("Set working mode as station ... ");
  mySerial.println("AT+CWMODE=1");  //設定為 Station 模式
  delay(7000);
  if (mySerial.find("OK") || mySerial.find("no change")) {
    Serial.println("OK");
  }
  else {
    Serial.println("No response");
  }
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
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
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDR, LOW);
  }
  if(count>=20){
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDR, LOW);
  }
  if(count==30){
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDR, HIGH);

  }
  if(count>=31){
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDR, HIGH);
  }

}

String get_ESP8266_response() {  //取得 ESP8266 的回應字串
  String str="";  //儲存接收到的回應字串
  char c;  //儲存接收到的回應字元
  while (mySerial.available()) {  //若軟體序列埠接收緩衝器還有資料
    c=mySerial.read();  //必須放入宣告為 char 之變數 (才會轉成字元)
    str.concat(c);  //串接回應字元 
    delay(10);  //務必要延遲, 否則太快
    }
  str.trim();  //去除頭尾空白字元
  return str;
  } 

String start_tcp(String address, byte port) {
  mySerial.println("AT+CIPSTART=\"TCP\",\"" + address + "\"," + String(port)); 
  mySerial.flush();  //等待序列埠傳送完畢
  delay(2000);
  String str=get_ESP8266_response();  //取得 ESP8266 回應字串
  if (str.indexOf("OK") != -1) {return "OK";}
  else {return "NG";}
  }

String send_data(String s) {
  String s1=s + "\r\n";  //務必加上跳行
  mySerial.println("AT+CIPSEND=" + String(s1.length())); 
  mySerial.flush();  //等待序列埠傳送完畢
  delay(1000);
  String str=get_ESP8266_response();  //取得 ESP8266 回應字串
  Serial.println(str);
  if (str.indexOf(">") != -1) {  //收到 > 開始傳送資料
    mySerial.println(s1); //傳送資料
    mySerial.flush();  //等待序列埠傳送完畢
    delay(7000);   
    str=get_ESP8266_response();  //取得 ESP8266 回應字串
    Serial.println(str);
    if (str.indexOf("30") != -1) {
   digitalWrite(8, HIGH);
      return "OK";
    }  //傳送成功會自動拆線
    else {  //傳送不成功須自行拆線
      digitalWrite(2, HIGH);
      close_ip();  //關閉 IP 連線 
      return "NG";
      }   
    }
  else {  //傳送不成功須自行拆線
    close_ip();  //關閉 IP 連線
    digitalWrite(13, HIGH);
    return "NG";
    }
  }

String close_ip() {
  mySerial.println("AT+CIPCLOSE");  //關閉 IP 連線
  mySerial.flush();  //等待序列埠傳送完畢
  delay(1000);
  String str=get_ESP8266_response();  //取得 ESP8266 回應字串
  if (str.indexOf("OK") != -1) {return "OK";}
  else {return "NG";}
}
