#include <EEPROM.h>
#include "support.h"

#define IO_LED 8
#define IO_BUTTON 10

time_t blinkInterval;
time_t lastMillis = 0;
time_t programmingStart = 0;
bool isProgramming = false;

void setup() {
  pinMode(IO_BUTTON, INPUT_PULLUP);
  pinMode(IO_LED, OUTPUT);

  Serial.begin(9600);
  while (!Serial) ;

  EEPROM.get(0, blinkInterval);
  LOG("READ BLINK INTERVAL ", blinkInterval);
}

void loop() {
  if (isProgramming) {
    if (isButtonPressed()) {

      lastMillis = millis();

      blinkInterval = lastMillis - programmingStart;
      isProgramming = false;

      EEPROM.put(0, blinkInterval);

      LOG("END PROGRAMMING interval ", blinkInterval);

      blinkLed();
      delay(100);
    }
  } else {
    if (isButtonPressed()) {
      LOG("START PROGRAMMING");

      programmingStart = millis();
      isProgramming = true;

      blinkLed();
    } else {
      time_t currentMillis = millis();

      if (currentMillis - lastMillis >= blinkInterval) {
        blinkLed();
        lastMillis = currentMillis;
      }
    }
  }
}

int isButtonPressed() {
  if (digitalRead(IO_BUTTON) == LOW) {
    time_t currentMillis = millis();
    while (digitalRead(IO_BUTTON) == LOW) {
      delay(1);
    }
    time_t diff = millis() - currentMillis;
    LOG("BUTTON PRESS TIME ", diff);
    return diff;
  }
  
  return 0;
}

bool blinkLed() {
  digitalWrite(IO_LED, HIGH);
  delay(50);
  digitalWrite(IO_LED, LOW);
}
