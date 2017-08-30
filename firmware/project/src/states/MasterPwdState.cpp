#include "MasterPwdState.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include "TouchManager.h"

MasterPwdState::MasterPwdState() {
    Serial.println("Started...");

    Serial.println("Started1...");
    kb = new Keyboard();

    Serial.println("Started2...");
    kb->draw();

    Serial.println("Started3...");
}

int MasterPwdState::loop() {
    char* enteredText = kb->processKeys();
    if (enteredText)
        Serial.print("Submited text :" + String(enteredText) + "\n");
    return 0;
}

MasterPwdState::~MasterPwdState() {
    delete kb;
}