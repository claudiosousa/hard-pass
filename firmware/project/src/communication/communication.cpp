#include "communication/communication.h"
#include <Arduino.h>

void communication_setup() {
    Serial.begin(115200);
}

const char TERMINATOR = 4;

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

void communication_writebytes(uint8_t* bytes, int len) {
    for (int i = 0; i < len; i++) {
        if (bytes[i] < 0x10)
            Serial.print("0");
        Serial.print(bytes[i], HEX);
    }
    Serial.print(TERMINATOR);
}