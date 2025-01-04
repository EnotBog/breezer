#include "temperature.h"
#include "config.h"
void getTemp() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  Serial.println(temperature);
}