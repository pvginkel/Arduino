#include "support.h"

void setup() {
  Serial.begin(9600);
}

time_t lastMillis = 0;
i32 loops = 0;

void loop(){
  loops++;

  auto currentMillis = millis();
  auto diff = currentMillis - lastMillis;

  if (currentMillis - lastMillis >= 1000) {
    LOG("LOOPS ", (loops * 1000) / diff);
    loops = 0;
    lastMillis = millis();
  }
}
