#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// JSON data buffer
StaticJsonDocument<250> jsonDocument;
char buffer[250];


const char* ssid = "Azul-ai7i";
const char* password = "r3n4t4n3g4";

WiFiServer server(80);

// setup API resources
void setup_routing() {
  server.on("/temperature", getTemperature);
  server.on("/pressure", getPressure);
  server.on("/humidity", getHumidity);
 
  // start server
  server.begin();
}

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
}

void getTemperature() {
  temperature = ''
  Serial.println("Get temperature");
  create_json("temperature", temperature, "°C");
  server.send(200, "application/json", buffer);
}
 
void getHumidity() {
  humidity = ''
  Serial.println("Get humidity");
  create_json("humidity", humidity, "%");
  server.send(200, "application/json", buffer);
}
 
void getPressure() {
  pressure = ''
  Serial.println("Get pressure");
  create_json("pressure", pressure, "mBar");
  server.send(200, "application/json", buffer);
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

void create_json(char *tag, float value, char *unit) {  
  jsonDocument.clear();
  jsonDocument["type"] = tag;
  jsonDocument["value"] = value;
  jsonDocument["unit"] = unit;
  serializeJson(jsonDocument, buffer);  
}
 
void add_json_object(char *tag, float value, char *unit) {
  JsonObject obj = jsonDocument.createNestedObject();
  obj["type"] = tag;
  obj["value"] = value;
  obj["unit"] = unit; 
}

void loop (){
    Serial.println("Entered loop")
    delay(500);  
} 