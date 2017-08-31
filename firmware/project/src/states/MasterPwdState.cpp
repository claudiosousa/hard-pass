#include "MasterPwdState.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include "TouchManager.h"

char* masterPwd;

MasterPwdState::MasterPwdState() {
    kb = new Keyboard();
    kb->draw();
}

int MasterPwdState::loop() {
    masterPwd = kb->processKeys();
    if (masterPwd) {
        Serial.print("Submited text: " + String(masterPwd) + "\n");
        return 2;
    }
    return 0;
}

MasterPwdState::~MasterPwdState() {
    delete kb;
}