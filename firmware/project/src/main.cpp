#include <Adafruit_GFX.h>
#include <Arduino.h>

#include <AndroidKeyboard.h>

Keyboard kb = Keyboard();

void setup() {
    Serial.begin(115200);

    kb.draw();
}

void loop() {
}
