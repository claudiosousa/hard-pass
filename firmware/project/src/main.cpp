#include <Adafruit_GFX.h>
#include "comunication.h"
#include "sound.h"
#include "stateMachine.h"
#include "states/settings.h"
#include "TFT.h"

#define USB_CABLE_RIGHT true

void setup() {
    MCUFRIEND_kbv& tft = buildTFT();
    tft.begin(0x9341);
    tft.setRotation(USB_CABLE_RIGHT ? 3 : 1);

    settings_setup();
    communication_setup();
    statemachine_setup();
    sound_setup();
}

void loop() {
    statemachine_loop();
    sound_loop();
    communication_loop();
}
