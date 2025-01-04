
#include "mqtt_handler.h"
#include "fan_control.h"
#include "stepper_control.h"
#include "auto_control.h"
#include "temperature.h"
#include "config.h"

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

  myStepper.setSpeed(250);
  sensors.begin();
  initPosition();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - btnTimer2 > 10000) {
    Serial.println(check_error);
    getTemp();
    updateValues();
    setS();
    btnTimer2 = millis();
  }

  if ((millis() - btnTimer > 5000) && (set_programm == 3)) {
    autoMode();
    btnTimer = millis();
  }
}
