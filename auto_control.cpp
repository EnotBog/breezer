#include "auto_control.h"
#include "config.h"
#include "fan_control.h" // Для доступа к fan_speed и другим переменным
#include "stepper_control.h"

void setAutoMode(int op, int fan, int lvl) {
    moving(op); // Нужно, чтобы функция moving была видна
    setSpeedFan(fan);
    auto_mode = lvl; // Предполагается, что auto_mode объявлена в config.h
}

void autoMode() {
    Serial.println("автоматический режим");
    int lvlCO2 = 0;

    if (CO2 >= 400 && CO2 < 480) {
        lvlCO2 = 4;
    } else if (CO2 >= 500 && CO2 < 580) {
        lvlCO2 = 5;
    } else if (CO2 >= 600 && CO2 < 680) {
        lvlCO2 = 6;
    } else if (CO2 >= 700 && CO2 < 780) {
        lvlCO2 = 7;
    } else if (CO2 >= 800 && CO2 < 880) {
        lvlCO2 = 8;
    } else if (CO2 >= 900 && CO2 < 980) {
        lvlCO2 = 9;
    } else if (CO2 >= 1000 && CO2 < 1080) {
        lvlCO2 = 10;
    } else if ((CO2 > 1080 || CO2 < 400) && CO2 != 0) {
        check_error = 3;
        return;
    } else {
        lvlCO2 = auto_mode;
    }

    if (lvlCO2 == auto_mode) {
        Serial.println("Показания не изменились ");
        return;
    }

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
