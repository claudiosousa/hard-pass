#include "stateMachine.h"
#include "states/AskPwdState.h"
#include "states/BaseState.h"
#include "states/MasterPwdState.h"
#include "states/SettingsState.h"
#include "states/WaitingState.h"

typedef enum StateName { MasterPwd = 1, Waiting = 2, AskPwd = 3, Settings = 4 } StateName;

BaseState* currentState;

void setState(StateName newStateName) {
    switch (newStateName) {
        case MasterPwd:
            currentState = new MasterPwdState();
            break;
        case Waiting:
            currentState = new WaitingState();
            break;
        case AskPwd:
            currentState = new AskPwdState();
            break;
        case Settings:
            currentState = new SettingsState();
            break;
        default:
            break;
    }
    // deleet causes reboot loop
    // delete currentState;
}

void statemachine_setup() {
    setState(MasterPwd);
}

void statemachine_loop() {
    int op = currentState->loop();
    if (!op)
        return;
    setState((StateName)op);
}
