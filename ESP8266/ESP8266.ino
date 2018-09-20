/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "chts230";
const char* password = "12345678";

const char* host = "henjorly.ddns.net";
const char* streamId   = "....................";
const char* privateKey = "....................";
WiFiServer server(8888);
void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

//  Serial.println();
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
  
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  server.begin();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
//  Serial.println(WiFi.localIP());
  //delay(1000);
  ++value;
    
//  Serial.print("connecting to ");
//  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
    WiFiClient client=server.available();
    if (!client) {return;}
    Serial.println("New client");
    String request=client.readStringUntil("\r");
    Serial.println(request);
    const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
//    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/WEB/Library/API/getIP";
//  url += streamId;
//  url += "?private_key=";
//  url += privateKey;
//  url += "&value=";
//  url += value;
  
//  Serial.print("Requesting URL: ");
//  Serial.println(url);
  
  // This will send the request to the server
// client.println(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" + 
//               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
//      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    uint8_t line = client.read();
//    if(line.startsWith("{")){
      Serial.print(line);
      Serial.write(line);
//    }
  }
  
//  Serial.println();
//  Serial.println("closing connection");
}
