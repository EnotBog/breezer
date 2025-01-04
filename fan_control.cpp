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


