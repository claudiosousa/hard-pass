#include "AskPwdState.h"
#include "MasterPwdState.h"
#include "TFT.h"
#include "TouchManager.h"
#include "colors.h"
#include "comunication.h"

char* msg;
const int BUTTONS_SIZE[2] = {100, 50};
const int BUTTONS_POS[2][2] = {{40, 150}, {160, 150}};
const unsigned int BUTTONS_COLOR[2] = {RED, GREEN};

AskPwdState::AskPwdState() {
    tft.fillScreen(WHITE);

    for (int i = 0; i < 2; i++) {
        int* pos = BUTTONS_POS[i];
        tft.fillRoundRect(pos[0], pos[1], BUTTONS_SIZE[0], BUTTONS_SIZE[1], 3, BUTTONS_COLOR[i]);
    }

    msg = communication_read();
}

int AskPwdState::loop() {
    int touch[2];
    if (!TouchManager_getPoint(touch))
        return 0;

    for (int i = 0; i < 2; i++) {
        int* pos = BUTTONS_POS[i];

        if (touch[0] < pos[0] || touch[0] > pos[0] + BUTTONS_SIZE[0] || touch[1] < pos[1] ||
            touch[1] > pos[1] + BUTTONS_SIZE[1])
            continue;

        if (i == 1)  // OK
            communication_write(msg);
        communication_clear_read();
        return 2;
    }

    return 0;
}