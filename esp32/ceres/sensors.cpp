#include "sensors.h"
#include <Arduino.h>

int getSensor(int sensorPin){
  analogRead(sensorPin);
  Serial.println(analogRead(sensorPin));
  return analogRead(sensorPin) ;
}
