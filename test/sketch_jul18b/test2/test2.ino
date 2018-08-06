#include <SoftwareSerial.h>
SoftwareSerial sSerial(10, 11); // RX, TX
String address = "henjorly.ddns.net";
int port = 80;
int ledPin = 13;
int a= 753;
String send ="";
int relay = 7;//繼電器腳位
void setup() {
  sSerial.begin(115200);  //設定軟體序列埠速率 (to ESP8266)
  Serial.begin(115200);  //設定軟體序列埠速率 (to PC) 
  send = "GET /test1.php?test="+String(a);
  Serial.println(send);
  Serial.print("Set working mode as station ... ");
  sSerial.println("AT+CWMODE=1");  //設定為 Station 模式
  delay(5000);
  if (sSerial.find("OK") || sSerial.find("no change")) {
    Serial.println("OK");
  }
  else {
    Serial.println("No response");
  }
   pinMode(13,OUTPUT);
   pinMode(4,OUTPUT);
   pinMode(relay, OUTPUT);  
   digitalWrite(relay, LOW);
 Serial.println("Connect to henjorly....."+start_tcp(address, port));
 Serial.println("Send GET : " + send_data(send));
  
}

void loop() { // run over and over
   if (sSerial.available()) {   //若軟體序列埠 Rx 收到資料 (來自 ESP8266)
    Serial.write(sSerial.read());  //讀取後寫入硬體序列埠 Tx (PC)
    }
  if (Serial.available()) {  //若硬體序列埠 Rx 收到資料 (來自 PC)
    sSerial.write(Serial.read());  //讀取後寫入軟體序列埠 Tx (ESP8266)
    } 
      digitalWrite(relay, HIGH);
      
}

String get_ESP8266_response() {  //取得 ESP8266 的回應字串
  String str="";  //儲存接收到的回應字串
  char c;  //儲存接收到的回應字元
  while (sSerial.available()) {  //若軟體序列埠接收緩衝器還有資料
    c=sSerial.read();  //必須放入宣告為 char 之變數 (才會轉成字元)
    str.concat(c);  //串接回應字元 
    delay(10);  //務必要延遲, 否則太快
    }
  str.trim();  //去除頭尾空白字元
  return str;
  } 

String start_tcp(String address, byte port) {
  sSerial.println("AT+CIPSTART=\"TCP\",\"" + address + "\"," + String(port)); 
  sSerial.flush();  //等待序列埠傳送完畢
  delay(2000);
  String str=get_ESP8266_response();  //取得 ESP8266 回應字串
  if (str.indexOf("OK") != -1) {return "OK";}
  else {return "NG";}
  }

String send_data(String s) {
  String s1=s + "\r\n";  //務必加上跳行
  sSerial.println("AT+CIPSEND=" + String(s1.length())); 
  sSerial.flush();  //等待序列埠傳送完畢
  delay(1000);
  String str=get_ESP8266_response();  //取得 ESP8266 回應字串
  if (str.indexOf(">") != -1) {  //收到 > 開始傳送資料
    sSerial.println(s1); //傳送資料
    sSerial.flush();  //等待序列埠傳送完畢
    delay(7000);   
    str=get_ESP8266_response();  //取得 ESP8266 回應字串
    Serial.println(str);
    if (str.indexOf("123") != -1) {
      digitalWrite(relay, HIGH);
       digitalWrite(4, HIGH);
      return "OK";
    }  //傳送成功會自動拆線
    else {  //傳送不成功須自行拆線
       digitalWrite(relay, HIGH);
      digitalWrite(13, HIGH);
      close_ip();  //關閉 IP 連線 
      return "NG";
      }   
    }
  else {  //傳送不成功須自行拆線
    close_ip();  //關閉 IP 連線
    return "NG";
    }
  }

String close_ip() {
  sSerial.println("AT+CIPCLOSE");  //關閉 IP 連線
  sSerial.flush();  //等待序列埠傳送完畢
  delay(1000);
  String str=get_ESP8266_response();  //取得 ESP8266 回應字串
  if (str.indexOf("OK") != -1) {return "OK";}
  else {return "NG";}
}

