#include "comunication.h"
#include <Arduino.h>
#include "Sha/sha1.h"

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

void communication_sendhash(char* msg) {
    uint8_t* hash;
    Sha1.init();
    Sha1.print(msg);
    hash = Sha1.result();
    Serial.print("0x");
    for (int i = 0; i < 20; i++) {
        if (hash[i] < 0x10)
            Serial.print("0");
        Serial.print(hash[i], HEX);
    }
    Serial.print(TERMINATOR);
}