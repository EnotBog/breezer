#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <Arduino.h>  // Добавьте эту строку для определения типа byte

void setup_wifi();
void reconnect();
void callback(char* topic, byte* payload, unsigned int length);
void updateValues();
String creatJsonString();
#endif