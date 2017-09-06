#ifndef _SETTTING_STATE_H
#define _SETTTING_STATE_H

#include "stateMachines/BaseState.h"
#include "screen/TFT.h"

class SettingsState : public BaseState {
   public:
    SettingsState();
    int loop();
    ~SettingsState();

   private:
    MCUFRIEND_kbv& tft = buildTFT();
    void drawInitialScreen();
    void drawButton(int button, int text_padding, char * text, uint16_t background);
};

#endif