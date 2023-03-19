#include <Arduino.h>



#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include "SPIFFS.h"

#include <Arduino_JSON.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

// Replace with your network credentials
const char* ssid = "------";
const char* password = "---------";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Set LED GPIO
const int ledPin = 23;
const int ledPin2 = 22;
const int ledPin3 = 21;
const int ledPin4 = 18;

const int WYL=5;

// Stores LED state
String ledState;
// Initialize SPIFFS
void initSPIFFS() {
 if (!SPIFFS.begin()) {
 Serial.println("An error has occurred while mounting SPIFFS");
 }
 Serial.println("SPIFFS mounted successfully");
}
// Initialize WiFi
void initWiFi() {
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi ..");
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print('.');
 delay(1000);
 }
 Serial.println(WiFi.localIP());
}
// Replaces placeholder with LED state value
/*String processor(const String& var){
 if(var == "STATE") {
 if(digitalRead(ledPin)) {
 ledState = "ON";
 }
 else {
 ledState = "OFF";
 }
 return ledState;
 }
 return String();
}*/
void setup() {
// Serial port for debugging purposes
 Serial.begin(9600);
 initWiFi();
 initSPIFFS();
 
 // Set GPIO2 as an OUTPUT
 pinMode(ledPin , OUTPUT);
 pinMode(ledPin2 , OUTPUT);
  pinMode(ledPin3, OUTPUT);
 pinMode(ledPin4 , OUTPUT);
 pinMode(WYL,INPUT_PULLUP);
 

 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 request->send(SPIFFS, "/index.html", "text/html", false);
 if(digitalRead(WYL)==LOW)
  {
    digitalWrite(ledPin,HIGH);
    digitalWrite(ledPin2,HIGH);
  }else{
    digitalWrite(ledPin,LOW);
     digitalWrite(ledPin2,LOW);

  }
 
 });
 server.serveStatic("/", SPIFFS, "/");
 // Route to set GPIO state to HIGH
 server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin, HIGH);
 digitalWrite(ledPin2, HIGH);
 digitalWrite(ledPin3, HIGH);
 digitalWrite(ledPin4, HIGH);

 
 
 request->send(SPIFFS, "/index.html", "text/html", false);
 });
 server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin, HIGH);
 digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, HIGH);
 digitalWrite(ledPin4, HIGH);
 
 request->send(SPIFFS, "/index.html", "text/html", false);
 });
 server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin, LOW);
 digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
 digitalWrite(ledPin4, HIGH);
 
 request->send(SPIFFS, "/index.html", "text/html", false);
 });
 server.on("/zawroc", HTTP_GET, [](AsyncWebServerRequest *request){
digitalWrite(ledPin, LOW);
 digitalWrite(ledPin2, HIGH);
 digitalWrite(ledPin3, HIGH);
 digitalWrite(ledPin4, LOW);
 
 request->send(SPIFFS, "/index.html", "text/html", false);
 });

 server.on("/prosto", HTTP_GET, [](AsyncWebServerRequest *request){
 digitalWrite(ledPin, HIGH);
 digitalWrite(ledPin2, LOW);
 digitalWrite(ledPin3, LOW);
 digitalWrite(ledPin4, HIGH);
 
 request->send(SPIFFS, "/index.html", "text/html", false);
 });
 





 // Start server
 server.begin();
}
void loop() {
}


/*
#include <Arduino.h>
#define WYL 5
#define W1 23
#define W2 22
void setup() {
  Serial.begin(9600);
  pinMode(W1,OUTPUT);
  pinMode(W2,OUTPUT);
  pinMode(WYL,INPUT_PULLUP);
  digitalWrite(W1,LOW);
  digitalWrite(W2,LOW);


  // put your setup code here, to run once:
}

void loop() {
  
   if(digitalRead(WYL)==LOW)
  {
    digitalWrite(W1,HIGH);
    digitalWrite(W2,HIGH);
  }else{
    digitalWrite(W1,LOW);
     digitalWrite(W2,LOW);

  }


  // put your main code here, to run repeatedly:
}
*/
