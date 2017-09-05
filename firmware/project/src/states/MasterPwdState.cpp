#include "MasterPwdState.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include "touch.h"

char* masterPwd;

MasterPwdState::MasterPwdState() {
    kb = new Keyboard();
    kb->draw();
}

int MasterPwdState::loop() {
    masterPwd = kb->processKeys();
    if (masterPwd)
        return 2;  // move to waiting state

    return 0;
}

MasterPwdState::~MasterPwdState() {
    delete kb;
}