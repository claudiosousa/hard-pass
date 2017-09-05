
#include <EEPROM.h>
#include "settings.h"

int address = 200;
uint8_t config;

void settings_setup() {
    config = EEPROM.read(address);
}

bool settings_soundIsOn() {
    return config & 0b10000000;
}

void settings_save() {
    EEPROM.write(address, config);
}