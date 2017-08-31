#include "comunication.h"
#include <Arduino.h>

void communication_setup() {
    Serial.begin(115200);
}

const char TERMINATOR = 'x';

String s;

void communication_loop() {
    if (!Serial.available())
        return;
    s = Serial.readStringUntil(TERMINATOR);
}

char* communication_read() {
    if (!s.length())
        return NULL;
    return s.c_str();
}
void communication_clear_read() {
    s = String();
}

void communication_write(char* msg) {
    Serial.print(msg);
    Serial.print(TERMINATOR);
}