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
};

#endif