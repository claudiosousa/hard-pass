#include "stateMachine.h"
#include "states/BaseState.h"
#include "states/MasterPwdState.h"

typedef enum StateEnum { MasterPwd, Waiting } StateEnum;

BaseState* state;
void setState(StateEnum newState) {
    switch (newState) {
        case MasterPwd: {
            state = new MasterPwdState();
            break;
        }
        case Waiting:
            break;
        default:
            break;
    }
}

void statemachine_setup() {
    setState(MasterPwd);
}

void statemachine_loop() {
    state->loop();
}
