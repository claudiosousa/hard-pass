#ifndef _MASTER_PWD_STATE_H
#define _MASTER_PWD_STATE_H

#include <MCUFRIEND_kbv.h>
#include "AndroidKeyboard.h"
#include "BaseState.h"

extern char* masterPwd;

class MasterPwdState : public BaseState {
   public:
    MasterPwdState();
    int loop();
    ~MasterPwdState();

   private:
    Keyboard *kb;
};

#endif