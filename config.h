#ifndef CONFIG_H
#define CONFIG_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <Stepper.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <esp_sleep.h>

// Определение GPIO
#define BUT_ZAS 33
#define REL_1 22
#define REL_2 21
#define IN1 19
#define IN2 17
#define IN3 18
#define IN4 16
#define S_GREEN 13
#define S_RED 12
#define S_ERROR 27

extern int auto_mode;
extern bool verified_error;
extern int CO2;
extern int check_error;
extern int power_state;
extern int fan_state;
extern int step;
extern int openness;
extern int fan_speed;
extern int set_programm;
extern float temperature;
extern const int stepsPerRevolution;  // 700 ШАГОВ

extern uint32_t btnTimer;
extern uint32_t btnTimer2;
extern uint32_t btnTimer3;
extern bool buttom_z;

extern Stepper myStepper;
extern WiFiClient espClient;
extern PubSubClient client;
extern OneWire oneWire;
extern DallasTemperature sensors;
//////////////////////////////////// LWT
extern const char* mqttTopicLWT;

/////////////////// SETTINGS /////////////////////////////

// Wi-Fi
extern const char* ssid;
extern const char* password;

// MQTT
extern const char* mqtt_server;
extern const int mqtt_port;
extern const char* mqtt_user;
extern const char* mqtt_password;

/////////////////////////////////////////////////////////
// TOPIC
extern const String temp_topic;

#endif
