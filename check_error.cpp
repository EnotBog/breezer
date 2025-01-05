#include "check_error.h"
#include "config.h"
#include "fan_control.h"
#include "stepper_control.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc.h"
#include "driver/rtc_io.h"

void checkError(int err) {
  switch (err) {
    case 1:
      stopJob();
      break;
    case 2:
      setSpeedFan(0);
      power_state = 0;
      initPosition();
      verified_error = 1;
    case 3:  //отписаться от паблика сбросить показания CO2
      setSpeedFan(0);
      client.unsubscribe((temp_topic + "/vozduh/CO2").c_str());
      set_programm = 4;
      CO2 = 0;
      power_state = 0;
      initPosition();
      verified_error = 1;
      break;
  }
};

void stopJob() {
  digitalWrite(S_ERROR, HIGH);
  gpio_hold_en((gpio_num_t)S_ERROR);
  esp_deep_sleep_start();
};

void setS() {
  int buf = (power_state == 0) ? 1 : 2;
  if (check_error != 0) {
    buf = 3;
  }
  switch (buf) {
    case 1:
      digitalWrite(S_RED, HIGH);
      digitalWrite(S_GREEN, LOW);
      break;
    case 2:
      digitalWrite(S_RED, LOW);
      digitalWrite(S_GREEN, HIGH);
      break;
    case 3:
      digitalWrite(S_RED, LOW);
      digitalWrite(S_GREEN, LOW);
      digitalWrite(S_ERROR, HIGH);
      break;
  }
}
