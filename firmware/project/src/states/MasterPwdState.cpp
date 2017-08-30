#include "MasterPwdState.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include "TouchManager.h"

MasterPwdState::MasterPwdState() {
    kb = new Keyboard();
    kb->draw();
}

int MasterPwdState::loop() {
    char* enteredText = kb->processKeys();
    if (enteredText) {
        //Serial.print("Submited text :" + String(enteredText) + "\n");
        return 2;
    }
    return 0;
}

MasterPwdState::~MasterPwdState() {
    delete kb;
}