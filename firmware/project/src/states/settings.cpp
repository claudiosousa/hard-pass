
#include "settings.h"
#include <EEPROM.h>

int address = 200;
uint8_t config;

void settings_setup() {
    config = EEPROM.read(address);
}

void settings_save() {
    EEPROM.write(address, config);
}

bool settings_getbit(char bitpos) {
    return config & 1 << bitpos;
}

void settings_setbit(char bitpos, bool setbit) {
    if (setbit)
        config |= 1 << bitpos;
    else
        config &= ~(1 << bitpos);
    settings_save();
}

bool settings_getSoundIsOn() {
    return settings_getbit(1);
}

void settings_setSoundOn(bool soundOn) {
    settings_setbit(1, soundOn);
}

bool settings_getScreenIsRightOrientation() {
    return settings_getbit(2);
}

void settings_setScreenIsRightOrientation(bool rightOrientation) {
    settings_setbit(2, rightOrientation);
}

bool settings_getRemeberPwd() {
    return settings_getbit(3);
}

void settings_setRemeberPwd(bool remember) {
    settings_setbit(3, remember);
}