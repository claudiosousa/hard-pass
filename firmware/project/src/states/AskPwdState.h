#ifndef _ASK_PWD_STATE_H
#define _ASK_PWD_STATE_H

#include "BaseState.h"
#include "TFT.h"

class AskPwdState : public BaseState {
   public:
    AskPwdState();
    int loop();
    ~AskPwdState();

   private:
    MCUFRIEND_kbv& tft = buildTFT();
};

#endif