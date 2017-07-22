#include <Adafruit_GFX.h>
#include <Arduino.h>

#include <AndroidKeyboard.h>
#include "TouchManager.h"
#include "sound.h"

Keyboard kb = Keyboard();

void setup() {
    Serial.begin(115200);

    kb.draw();
    sound_setup();
}
int i = 0;
void loop() {
    char* enteredText = kb.processKeys();
    if (enteredText)
        Serial.print("Submited text :" + String(enteredText) + "\n");

    if (!sound_isPlaying()) {
        switch (i) {
            case 1:
                sound_play(&startSound);
                break;
            case 3:
                sound_play(&gameOverSound);
                break;
            case 2:
                sound_play(&winSound);
                break;
            case 0:
                sound_play(&submitMoveSound);
                break;
        }
        i++;
        if (i == 4)
            i = 0;
    }

    sound_loop();
}
