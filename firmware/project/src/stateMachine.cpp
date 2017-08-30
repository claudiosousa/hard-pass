#include "stateMachine.h"
#include "states/BaseState.h"
#include "states/MasterPwdState.h"
#include "states/WaitingState.h"

typedef enum StateName { MasterPwd = 1, Waiting = 2 } StateName;

BaseState* currentState;

void setState(StateName newStateName) {
    switch (newStateName) {
        case MasterPwd:
            currentState = new MasterPwdState();
            break;
        case Waiting:
            currentState = new WaitingState();
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
