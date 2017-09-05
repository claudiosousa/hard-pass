#include <Adafruit_GFX.h>
#include "TFT.h"
#include "comunication.h"
#include "sound.h"
#include "stateMachine.h"
#include "touch.h"
#include "states/settings.h"

void setup() {
    settings_setup();

    TFT_setup();
    touch_setup();
    communication_setup();
    statemachine_setup();
    sound_setup();
}

void loop() {
    statemachine_loop();
    sound_loop();
    communication_loop();
}
