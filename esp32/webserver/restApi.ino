#include <Arduino.h>
#include <WiFi.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"

const char* ssid = "Azul-ai7i";
const char* password = "r3n4t4n3g4";

aREST rest = aREST();
WiFiServer server(80);

int testFunction(String command) {
  Serial.println("Received rest request");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  rest.function("test",testFunction);
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


void loop() {
 
  WiFiClient client = server.available();
  if (client) {
 
    while(!client.available()){
      delay(5);
    }
    rest.handle(client);
  }
}
