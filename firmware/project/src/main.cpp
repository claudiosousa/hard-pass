#include <Adafruit_GFX.h>
#include <AndroidKeyboard.h>
#include "TouchManager.h"
#include "comunication.h"
#include "sound.h"

Keyboard kb = Keyboard();

void setup() {
    kb.draw();
    sound_setup();
    communication_setup();
}
void loop() {
    sound_loop();
    communication_loop();

    char* enteredText = kb.processKeys();
    if (enteredText)
        Serial.print("Submited text :" + String(enteredText) + "\n");
}
