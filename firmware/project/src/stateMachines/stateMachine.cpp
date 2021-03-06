#include "stateMachine.h"
#include "BaseState.h"
#include "askPwd/AskPwdState.h"
#include "masterPwd/MasterPwdState.h"
#include "settings/SettingsState.h"
#include "waiting/WaitingState.h"

typedef enum StateName { MasterPwd = 1, Waiting = 2, AskPwd = 3, Settings = 4 } StateName;

BaseState* currentState = NULL;

void setState(StateName newStateName) {
    if (currentState != NULL)
        delete currentState;

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
