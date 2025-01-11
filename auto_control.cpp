#include "auto_control.h"
#include "config.h"
#include "fan_control.h"  // Для доступа к fan_speed и другим переменным
#include "stepper_control.h"
#include "time_ntp.h"


void setAutoMode(int op, int fan, int lvl) {
  moving(op);  // Нужно, чтобы функция moving была видна
  setSpeedFan(fan);
  auto_mode = lvl;  // Предполагается, что auto_mode объявлена в config.h
}

// 800<->2300
/*
if!(t<=2300&&t>800){

}
*/
// 801<2300&&801>800 входит в промежуток 8-23
// 500<2300&&500>800 не входит в промежуток 8-23

void nightMode(int *lvlCO2) {
  if (*lvlCO2 == 10) { *lvlCO2 = 8; }
  if (*lvlCO2 == 9) { *lvlCO2 = 8; }
}


void autoMode() {
  Serial.println("автоматический режим");
  Serial.print("CO2: ");
  Serial.println(CO2);
  int lvlCO2 = 0;

  if (CO2 >= 700 && CO2 < 780) {
    lvlCO2 = 4;
  } else if (CO2 >= 800 && CO2 < 880) {
    lvlCO2 = 5;
  } else if (CO2 >= 900 && CO2 < 980) {
    lvlCO2 = 6;
  } else if (CO2 >= 1000 && CO2 < 1080) {
    lvlCO2 = 7;
  } else if (CO2 >= 1100 && CO2 < 1180) {
    lvlCO2 = 8;
  } else if (CO2 >= 1200 && CO2 < 1280) {
    lvlCO2 = 9;
  } else if (CO2 >= 1300 && CO2 < 1500) {
    lvlCO2 = 10;
  } else if ((CO2 > 1580 || CO2 < 300) && CO2 != 0) {
    check_error = 3;
    Serial.println("erorr");
    return;
  } else {  ///////  запилить ошибу check_error если нет показаний выключить устройство.
    lvlCO2 = auto_mode;
  }
  Serial.print("auto_mode: ");
  Serial.println(auto_mode);

  if (lvlCO2 == auto_mode) {
    Serial.println("Показания не изменились ");
    return;
  }

  if (night_now) {
    nightMode(&lvlCO2);
    Serial.println("Ночной режим изменение параметров");
  }    // проверка на ночной

  Serial.println("Изменение параметров автоматического режима ");
  switch (lvlCO2) {
    case 4:
      setAutoMode(1, 0, lvlCO2);
      break;
    case 5:
      setAutoMode(50, 0, lvlCO2);
      break;
    case 6:
      setAutoMode(100, 0, lvlCO2);
      break;
    case 7:
      setAutoMode(50, 1, lvlCO2);
      break;
    case 8:
      setAutoMode(100, 1, lvlCO2);
      break;
    case 9:
      setAutoMode(100, 2, lvlCO2);
      break;
    case 10:
      setAutoMode(100, 2, lvlCO2);
      break;
    default:
      setAutoMode(0, 0, lvlCO2);
      break;
  }
  Serial.println("Автоматическая программа установлена");
}
