#include "comunication.h"
#include <Arduino.h>

void communication_setup() {
    Serial.begin(115200);
}

const char TERMINATOR = '\0';

void communication_loop() {
    if (!Serial.available())
        return;
    String s = Serial.readStringUntil(TERMINATOR);
    Serial.print(s + s + TERMINATOR);
}