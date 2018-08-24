//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(115200);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  if (Serial.available() > 0)
//  {
//    char str = Serial.read();
//    Serial.print(str);
//  }
//}

#include <ESP8266WiFi.h>
const char* ssid="chts230";
const char* password="12345678";
const int LED=2;      // GPIO2
int value=LOW;
WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    delay(10);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        }
    Serial.println("");
    Serial.println("WiFi connected");
    server.begin();
    Serial.println("Server started");
    Serial.print("Use this URL to connect: ");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
    }
  
void loop() {
    WiFiClient client=server.available();
    if (!client) {return;}
    Serial.println("New client");
    while (!client.available()) {delay(1);}
    String request=client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    if (request.indexOf("/LED=ON") != -1) {value=HIGH;}
    if (request.indexOf("/LED=OFF") != -1) {value=LOW;}
    Serial.print("value=");
    Serial.println(value);
    digitalWrite(LED, value);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("");
    client.println("");
    client.print("Led pin is now: ");
    if (value==HIGH) {client.print("On");}
    else {client.print("Off");}
    client.println("<br><br>");
    client.println("Click <a href='/LED=ON'>here</a> turn the LED on pin 2 ON<br>");
    client.println("Click <a href='/LED=OFF'>here</a> turn the LED on pin 2 OFF<br>");
    client.println("</p><p>");
    delay(1);
    Serial.println("Client disonnected");
    Serial.println("");
    }
