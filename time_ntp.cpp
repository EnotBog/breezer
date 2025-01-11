#include "config.h"
#include "time_ntp.h"
#include "time.h"
#include "check_error.h"

const long gmtOffset_sec = 10800;
const int daylightOffset_sec = 3600;
const char* ntpServer = "pool.ntp.org";
int time_esp;
bool night_now = false;
struct tm timeinfo;

void getTime() {
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    check_error = 5;
  }
  int buf;
  buf += timeinfo.tm_hour * 100 + timeinfo.tm_min;
  time_esp = buf;
  Serial.println(time_esp);
  setNight();
};

void setNight() {
  if (!(time_esp <= 2300 && time_esp > 800)) {
    night_now = true;
  }
}