#include "config.h"
#include "set_programm.h"
#include "stepper_control.h"
void programm(int programm) {
  Serial.print("programm");
  power_state = 3;
  switch (programm) {
    case 1:  // минимальный режим работы
      moving(30);
      digitalWrite(REL_1, LOW);
      digitalWrite(REL_2, HIGH);
      set_programm = 1;
      fan_speed = 1;
      auto_mode = 0;
      Serial.print("programm 1");
      break;
    case 2:  // максимальное открытие и максимальный режим вентилятора
      moving(100);
      digitalWrite(REL_1, HIGH);
      digitalWrite(REL_2, LOW);
      set_programm = 2;
      fan_speed = 2;
      Serial.print("programm 2");
      auto_mode = 0;
      break;
    case 3:  // автоматический режим
      set_programm = 3;
      power_state = 3;
      auto_mode = 0;
      Serial.print("programm 3");
      break;
    case 4:  // пользовательский
      set_programm = 4;
      Serial.print("programm 4");
      break;
  }
}