#include <Adafruit_GFX.h>
#include "comunication.h"
#include "sound.h"
#include "stateMachine.h"

void setup() {
    communication_setup();
    statemachine_setup();
    sound_setup();
}

void loop() {
    statemachine_loop();
    sound_loop();
    communication_loop();
}
