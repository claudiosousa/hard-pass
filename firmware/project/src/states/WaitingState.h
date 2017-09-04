#ifndef _WAITING_STATE_H
#define _WAITING_STATE_H

#include "BaseState.h"
#include "TFT.h"

class WaitingState : public BaseState {
   public:
    WaitingState();
    int loop();
    ~WaitingState();

   private:
    void drawScreenLoop();
    MCUFRIEND_kbv& tft = buildTFT();
    void drawWaitingScreen();
};

#endif