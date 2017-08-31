#include "comunication.h"
#include <Arduino.h>

void communication_setup() {
    Serial.begin(115200);
}

const char TERMINATOR = '\0';

String s;

void communication_loop() {
    if (!Serial.available())
        return;
    s = Serial.readStringUntil(TERMINATOR);
    Serial.print(s + TERMINATOR);
}

char* communication_message() {
    if (!s.length())
        return NULL;
    return s.c_str();
}