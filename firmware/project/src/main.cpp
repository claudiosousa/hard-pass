#include <Adafruit_GFX.h>
#include <Arduino.h>

#include <AndroidKeyboard.h>
#include "TouchManager.h"

Keyboard kb = Keyboard();

void setup() {
    Serial.begin(115200);

    kb.draw();
}

void loop() {
    int point[3];
    char touch = kb.getPressedTouch();
    if (touch) {
        Serial.print("Key " + String(touch) + "\n");
    }
}
