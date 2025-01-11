
#include "mqtt_handler.h"
#include "fan_control.h"
#include "stepper_control.h"
#include "auto_control.h"
#include "temperature.h"
#include "config.h"
#include "check_error.h"
#include "set_programm.h"
#include "time_ntp.h"

void setup() {
  pinMode(REL_1, OUTPUT);
  pinMode(REL_2, OUTPUT);
  pinMode(BUT_ZAS, INPUT);
  pinMode(S_GREEN, OUTPUT);
  pinMode(S_RED, OUTPUT);
  pinMode(S_ERROR, OUTPUT);

  digitalWrite(REL_1, HIGH);
  digitalWrite(REL_2, HIGH);
  digitalWrite(S_GREEN, LOW);
  digitalWrite(S_RED, LOW);

  Serial.begin(115200);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  myStepper.setSpeed(250);
  sensors.begin();
  initPosition();
}

void loop() {
  if (millis() - btnTimer3 > 1000) {
    setS();
    if (check_error != 0) {
      checkError(check_error);
    }
    client.loop();
    btnTimer3 = millis();
  }
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - btnTimer2 > 10000) {
    Serial.println(check_error);
    getTemp();
    updateValues();
    btnTimer2 = millis();
    if (!CO2_online) {
      digitalWrite(REL_1, HIGH);
      digitalWrite(REL_2, HIGH);
      fan_speed = 0;
      initPosition();
      programm(4);
      power_state = 0;
    }  // выключить всё
  }

  if ((millis() - btnTimer > 5000) && (set_programm == 3)) {
    autoMode();
    btnTimer = millis();
    getTime();
  }
}
