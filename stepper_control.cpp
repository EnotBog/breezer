#include "stepper_control.h"
#include "config.h"
#include "auto_control.h"

void moving(int targetOpenness) {
  int steps = (openness - targetOpenness) * 7;
  openness = targetOpenness;

  if (steps != 0) {
    myStepper.step(steps);
  }
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void initPosition() {
  btnTimer = millis();
  if (!digitalRead(BUT_ZAS)) {
    while (true) {
      myStepper.step(50);
      if (millis() - btnTimer > 3000) {
        if (!digitalRead(BUT_ZAS)) {
          power_state = 0;
          check_error = 1;
          break;
        }
      }
      if (digitalRead(BUT_ZAS)) {
        openness = 0;
        set_programm = 4;
        break;
      }
    }

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

void checkPosition() {
  bool buttom_z_buf = digitalRead(BUT_ZAS);
  if (buttom_z_buf != buttom_z && millis() - btnTimer > 50) {
    buttom_z = buttom_z_buf;
    btnTimer = millis();
  }
}
