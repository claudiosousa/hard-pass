#ifndef _SETTTING_STATE_H
#define _SETTTING_STATE_H

#include "BaseState.h"
#include "TFT.h"

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