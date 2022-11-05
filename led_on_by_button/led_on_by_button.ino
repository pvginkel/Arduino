#include "support.h"

#define IO_LED 8
#define IO_BUTTON 10

#define time_t unsigned long
#define bool int
#define true 1
#define false 0

time_t blinkInterval = 1000;
time_t lastMillis = 0;
time_t programmingStart = 0;
bool isProgramming = false;

void setup() {
   pinMode(IO_BUTTON, INPUT_PULLUP);
   pinMode(IO_LED, OUTPUT);

   Serial.begin(9600);
}

void loop(){
  if (isProgramming) {
    if (isButtonPressed()) {

      lastMillis = millis();

      blinkInterval = lastMillis - programmingStart;
      isProgramming = false;

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
