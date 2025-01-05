#include "config.h"
bool verified_error = 0;
int auto_mode;
int CO2;
int check_error;
int power_state;
int fan_state;
int step;
int openness;
int fan_speed;
int set_programm;
float temperature;
const int stepsPerRevolution = 128;  // 700 ШАГОВ

uint32_t btnTimer;
uint32_t btnTimer2;
uint32_t btnTimer3;
bool buttom_z;

Stepper myStepper(stepsPerRevolution, IN4, IN3, IN2, IN1);
WiFiClient espClient;
PubSubClient client(espClient);
OneWire oneWire(32);
DallasTemperature sensors(&oneWire);

