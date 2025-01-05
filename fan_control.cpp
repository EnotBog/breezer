#include "fan_control.h"
#include "config.h"
#include "auto_control.h"

void setSpeedFan(int speed) {
  if (speed == 0) {
    digitalWrite(REL_1, HIGH);
    digitalWrite(REL_2, HIGH);
    fan_speed = 0;
  } else if (speed == 1) {
    digitalWrite(REL_1, LOW);
    digitalWrite(REL_2, HIGH);
    fan_speed = 1;
  } else if (speed == 2) {
    digitalWrite(REL_1, HIGH);
    digitalWrite(REL_2, LOW);
    fan_speed = 2;
  }
}




