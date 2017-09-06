#ifndef _ASK_PWD_STATE_H
#define _ASK_PWD_STATE_H

#include "screen/TFT.h"
#include "stateMachines/BaseState.h"

extern char* masterPwd;

class AskPwdState : public BaseState {
   public:
    AskPwdState();
    int loop();
    ~AskPwdState();

   private:
    MCUFRIEND_kbv& tft = buildTFT();
    void drawAskPwdStateScreen();
    void parseMessage();
};

#endif