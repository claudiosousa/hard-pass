#include <Adafruit_GFX.h>
#include <Arduino.h>

#include "TouchManager.h"
#include <AndroidKeyboard.h>

Keyboard kb = Keyboard();

void setup() {
  Serial.begin(115200);

  kb.draw();
}

void loop() {
  char* enteredText = kb.processKeys();
  if (enteredText)
    Serial.print("Submited text :" + String(enteredText) + "\n");
}
