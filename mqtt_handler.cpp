#include "mqtt_handler.h"
#include "auto_control.h"
#include "stepper_control.h"
#include "set_programm.h"
#include "config.h"

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  randomSeed(micros());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266-" + WiFi.macAddress();
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password, mqttTopicLWT, 1, true, "offline")) {
      client.publish(mqttTopicLWT, "online", true);
      client.subscribe((temp_topic + "/vozduh/openness").c_str());
      client.subscribe((temp_topic + "/vozduh/speed").c_str());
      client.subscribe((temp_topic + "/vozduh/power").c_str());
      client.subscribe((temp_topic + "/vozduh/programm").c_str());
      client.subscribe((temp_topic + "/vozduh/CO2").c_str());  // ТОПИК СО2
      Serial.println("connected");
      check_error = 0;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      check_error = 2;
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Home_67/vozduh/openness управление открытостью
  // Home_67/vozduh/programm управление программой на управление всего три программы 1. полное 2. частичное. 3 автомат. 4 пользовательская
  // Home_67/vozduh/speed скорости
  // Home_67/vozduh/off управление отключением закрывает клапан и выключает
  // Home_67/vozduh/CO2 качество воздуха

  String data_pay;
  for (int i = 0; i < length; i++) {
    data_pay += String((char)payload[i]);
  }

  if (String(topic) == "Home_67/vozduh/speed") {
    Serial.println("Home_67/vozduh/speed");
    switch (data_pay.toInt()) {
      case 0:
        digitalWrite(REL_1, HIGH);
        digitalWrite(REL_2, HIGH);
        fan_speed = 0;
        break;
      case 1:
        digitalWrite(REL_1, LOW);
        digitalWrite(REL_2, HIGH);
        fan_speed = 1;
        break;
      case 2:
        digitalWrite(REL_1, HIGH);
        digitalWrite(REL_2, LOW);
        fan_speed = 2;
        break;
    }
    set_programm = 4;
  }

  if (String(topic) == "Home_67/vozduh/openness") {
    Serial.println("Home_67/vozduh/openness");
    Serial.println(data_pay.toInt());
    moving(data_pay.toInt());
    set_programm = 4;
  }

  if (String(topic) == "Home_67/vozduh/power") {
    Serial.println("Home_67/vozduh/power");
    if (data_pay == "0") {
      digitalWrite(REL_1, HIGH);
      digitalWrite(REL_2, HIGH);
      fan_speed = 0;
      initPosition();
      power_state = 0;
    }  // выключить всё
    if (data_pay == "3") {
      programm(3);  // включить автоматический режим
    }
  }

  if (String(topic) == "Home_67/vozduh/programm") {
    Serial.println("Home_67/vozduh/programm");
    programm(data_pay.toInt());
  }

  if (String(topic) == "Home_67/vozduh/CO2") {
    CO2 = data_pay.toInt();
  }
}

void updateValues() {
  // Home_67/vozduh/openness/state текущая открытость
  // Home_67/vozduh/programm/state текущая программа
  // Home_67/vozduh/speed/state текущая скорость вентилятора
  // Home_67/vozduh/closed/state закрыт ли клапан полностью
  // Home/vozduh/fan/state dhfotybt dtynbkznjf
  // Home/vozduh/temperature/state датчик температуры
  checkPosition();
  if (!buttom_z || (fan_speed > 0 && check_error != 0)) {
    power_state = 3;
  }

  if (openness == 0 && buttom_z == 1) {
    digitalWrite(REL_1, HIGH);
    digitalWrite(REL_2, HIGH);
    fan_speed = 0;
    power_state = 0;
  }

  if (fan_speed != 3 && fan_speed != 0) {
    fan_state = 1;
  } else {
    fan_state = 0;
  }

  client.publish((temp_topic + "/vozduh/openness/state").c_str(), (String(openness)).c_str());
  client.publish((temp_topic + "/vozduh/programm/state").c_str(), (String(set_programm)).c_str());
  client.publish((temp_topic + "/vozduh/speed/state").c_str(), (String(fan_speed)).c_str());
  client.publish((temp_topic + "/vozduh/closed/state").c_str(), (String(!buttom_z)).c_str());
  client.publish((temp_topic + "/vozduh/power/state").c_str(), (String(power_state)).c_str());
  client.publish((temp_topic + "/vozduh/fan/state").c_str(), (String(fan_state)).c_str());
  client.publish((temp_topic + "/vozduh/temperature/state").c_str(), (String(temperature)).c_str());
}