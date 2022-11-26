#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"

//---------------------------------------------------------------
#include "DHT.h"
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define LED D7
#define buzz D6

//SSID and Password of your WiFi router
const char* ssid = "Chlorine";
const char* password = "mantub48";

ESP8266WebServer server(80);
String s = FPSTR(MAIN_page);  //Read HTML contents
int x = 0;

void handleRoot() {
  Serial.println("You called root page");
  server.send(200, "text/html", s);  //Send web page
}

void ledOn() {
  Serial.println("LED ON");
  x = 0;
  digitalWrite(LED, HIGH);
  if (x == 0) {
    digitalWrite(LED, HIGH);
  }
  server.send(200, "text/html", "ON");  //Send ADC value only to client ajax request
}

void ledOff() {
  Serial.println("LED OFF");
  digitalWrite(LED, LOW);  //LED off
  x = 0;
  server.send(200, "text/html", "OFF");  //Send ADC value only to client ajax request
}
void ledBlink() {
  server.send(200, "text/html", "BLINKING");
  x++;
  if (x >= 2) {
    x = 0;
    ledOff();
    Serial.print("STOP ");
  } else if (x == 1) {
    Serial.print("STRART ");
  }
  Serial.println("LED BLINKING");
}

void temp() {
  float t = dht.readTemperature();

  if (t >= 30) {
    tone(buzz, 600);
    digitalWrite(LED, HIGH);
  } else {
    tone(buzz, 0);
    digitalWrite(LED, LOW);
  }

  /* long t = random(20, 100);
  long h = random(20, 100); */

  String temp = String(t);
  server.send(200, "text/html", temp);
}

void hum() {
  float h = dht.readHumidity();
  String hum = String(h);
  server.send(200, "text/html", hum);
}
//==============================================================
// SETUP
//==============================================================
void setup(void) {
  Serial.begin(115200);

  WiFi.begin(ssid, password);  //Connect to your WiFi router
  Serial.println("");
  pinMode(LED, OUTPUT);
  pinMode(buzz, OUTPUT);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  server.on("/", handleRoot);  //Which routine to handle at root location. This is display page
  server.on("/ledOn", ledOn);  //as Per <a href="ledOn">, Subroutine to be called
  server.on("/ledOff", ledOff);
  server.on("/ledBlink", ledBlink);
  server.on("/temp", temp);
  server.on("/hum", hum);

  dht.begin();
  server.begin();  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
// LOOP
//==============================================================
void loop() {
  server.handleClient();  //Handle client requests
  if (x == 1) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
}