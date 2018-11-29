#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
const char* ssid     = "JordanFan"; // wifi name
const char* password = "12345678"; // wifi pass word
//"168016831686";

const char* host = "apps.nknu.edu.tw"; // dns host or ip host
const char* wakehost = "140.127.49.168"; // dns host or ip host
const char* streamId   = "....................";
const char* privateKey = "....................";
WiFiServer server(8888); //set wifi server port
SimpleTimer timer;
void repeatMe() {
    
  WiFiClient client2;

  //Serial.printf("\n[Connecting to %s ... ", host);
  if (client2.connect(wakehost, 80))
  {
    
    client2.print(String("GET /") +"World/API/nknulib/iPassHx/0000"+ " HTTP/1.1\r\n" +
                 "Host: " + wakehost + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

    while (client2.connected())
    { 
      client2.setTimeout(200);
      if (client2.available())
      {
        String line = client2.readStringUntil('\n');
      
        if(line.startsWith("{")){
          
          line.replace("{", "");
          line.replace("}", "");
          //Serial.println("debug2");
          //Serial.println(line);
          if(line=="OK"){
            Serial.println("OK");
          }
        }
        
      }
    }
    client2.stop();
    //Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client2.stop();
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(0, OUTPUT);
  // We start by connecting to a WiFi network

//  Serial.println();
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
  
  WiFi.mode(WIFI_AP_STA);//set wifi mode with AP+Station
  WiFi.begin(ssid, password);
  //WiFi.begin(ssid);
  server.begin();
  while (WiFi.status() != WL_CONNECTED) {  //check wifi connect to user's AP
    delay(500);
//    Serial.print(".");
  }
  timer.setInterval(10000, repeatMe);
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  timer.run();
  ++value;
    WiFiClient client=server.available(); // Use WiFiClient class to create TCP connections
    if (!client) {
    }
    else{
      String request=client.readStringUntil('\r');
      if(request.indexOf("pin=on") !=-1){
        Serial.println(request);
        digitalWrite(0, HIGH);
        Serial.println(request);
      }else if(request.indexOf("pin=off") !=-1){
        Serial.println(request);
        digitalWrite(0, LOW);
      }
      
    }
  // We now create a URI for the request
  String url = "iTaker/RedAPI/firUpdate?";//API url
  String response="";  
  char c; 
  while (Serial.available()) {  
    c=Serial.read();
    response.concat(c);   
    delay(10); 
      //Serial.println(Serial.read());
  }
  response.trim(); 
  if (response.indexOf("touch_time=") !=-1){ //check Serial String
    Serial.println("OK1");
    url += response;
    ClientReceive(url);//update data to DB
    Serial.println("OK2");
  }
  
}

void ClientReceive(String url) // send data to API or web
{
  WiFiClient client2;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client2.connect(host, 80))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client2.print(String("GET /") +url+ " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Response:]");
    while (client2.connected())
    {
      if (client2.available())
      {
        String line = client2.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client2.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client2.stop();
  }
  delay(5000);
}
