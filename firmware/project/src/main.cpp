#include <Adafruit_GFX.h>
#include "communication/communication.h"
#include "screen/TFT.h"
#include "screen/touch.h"
#include "settings/settings.h"
#include "sound/sound.h"
#include "stateMachines/stateMachine.h"

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
