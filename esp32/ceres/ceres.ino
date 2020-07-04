
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <string>
#include <ESPmDNS.h>
#include "sensors.h"

using namespace std;

const char* ssid = "Azul-ai7i";
const char* password = "r3n4t4n3g4";


// Pinout
#define humidity_sensor_pin 33
#define light_sensor_pin 32

// Server config

WebServer server(80);

// setup API resources
void setup_routing() {
  server.on("/", handle_OnConnect);
  server.on("/temperature", getTemperature);
  server.on("/light", getLight);
  server.on("/humidity", getHumidity);
  server.on("/settings", HTTP_GET, getSettings);
  server.onNotFound(handle_NotFound);
  
  // start server
  server.begin();
}


void getSettings() {
    String response = "{";
 
    response+= "\"ip\": \""+WiFi.localIP().toString()+"\"";
    response+= ",\"gw\": \""+WiFi.gatewayIP().toString()+"\"";
    response+= ",\"nm\": \""+WiFi.subnetMask().toString()+"\"";
 
    if (server.arg("signalStrength")== "true"){
        response+= ",\"signalStrengh\": \""+String(WiFi.RSSI())+"\"";
    }
 
    if (server.arg("chipInfo")== "true"){
//        response+= ",\"chipId\": \""+String(ESP.getChipId())+"\"";
//        response+= ",\"flashChipId\": \""+String(ESP.getFlashChipId())+"\"";
//        response+= ",\"flashChipSize\": \""+String(ESP.getFlashChipSize())+"\"";
//        response+= ",\"flashChipRealSize\": \""+String(ESP.getFlashChipRealSize())+"\"";
    }
    if (server.arg("freeHeap")== "true"){
        response+= ",\"freeHeap\": \""+String(ESP.getFreeHeap())+"\"";
    }
    response+="}";
 
    server.send(200, "text/json", response);
}

void handle_NotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handle_OnConnect()
{
  server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}


void getTemperature() {
  String temperature = "temperature1234";
  Serial.println("Get temperature");
  server.send(200, "text/json", temperature);
}
 
void getHumidity() {
  int humidity = getSensor(humidity_sensor_pin);
  Serial.println("Get humidity");
  server.send(200, "text/json", "{\"value\": \"" +  String(humidity) + "\"}" );
}
 
void getLight() {
  int light = getSensor(light_sensor_pin);
  Serial.println("Get light");
  server.send(200, "text/json", "{\"value\": \"" +  String(light) + "\"}" );
}
 
// void getEnv() {
//   Serial.println("Get env");
//   jsonDocument.clear(); // Clear json buffer
//   add_json_object("temperature", temperature, "°C");
//   add_json_object("humidity", humidity, "%");
//   add_json_object("pressure", pressure, "mBar");
//   serializeJson(jsonDocument, buffer);
//   server.send(200, "application/json", buffer);
// }


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
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

  // Call server routing
  setup_routing();
}


void loop (){
  server.handleClient();

} 
