#include "AskPwdState.h"
#include <string.h>
#include "MasterPwdState.h"
#include "TFT.h"
#include "TouchManager.h"
#include "colors.h"
#include "comunication.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

const int BUTTONS_SIZE[2] = {100, 50};
const int BUTTONS_POS[2][2] = {{50, 150}, {170, 150}};
const unsigned int BUTTONS_COLOR[2] = {DARKRED, DARKGREEN};

char *msg;
char *pwdModifier;
const char *errMsg = "";

AskPwdState::AskPwdState() {
    pwdModifier = communication_read();
    int i = 0;
    while (pwdModifier[i] != '\n')
        i++;
    pwdModifier[i] = 0;
    msg = pwdModifier + (i + 1);

    communication_write(String(i).c_str());
    communication_write(pwdModifier);
    communication_write(msg);

    tft.fillScreen(BACKGROUND);

    tft.fillRoundRect(30, 40, 260, 40, 4, MESSAGE_BACKGROUND);
    tft.setCursor(76, 52);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setTextWrap(false);
    tft.print("Password asked:");

    int len = strlen(msg);
    int center_position = ((260 - len * 12) / 2) + 30;

    tft.fillRoundRect(30, 90, 260, 40, 4, MESSAGE_BACKGROUND);
    tft.setCursor(center_position, 102);
    tft.setTextColor(ORANGE);
    tft.setTextSize(2);
    tft.setTextWrap(false);
    tft.print(msg);

    for (int i = 0; i < 2; i++) {
        int *pos = BUTTONS_POS[i];
        tft.fillRoundRect(pos[0], pos[1], BUTTONS_SIZE[0], BUTTONS_SIZE[1], 3, BUTTONS_COLOR[i]);
    }
    tft.setCursor(65, 168);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setTextWrap(false);
    tft.print("Cancel");

    tft.setCursor(210, 168);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setTextWrap(false);
    tft.print("Ok");
}

int AskPwdState::loop() {
    int touch[2];
    if (!TouchManager_getPoint(touch))
        return 0;

    for (int i = 0; i < 2; i++) {
        int *pos = BUTTONS_POS[i];

        if (touch[0] < pos[0] || touch[0] > pos[0] + BUTTONS_SIZE[0] || touch[1] < pos[1] ||
            touch[1] > pos[1] + BUTTONS_SIZE[1])
            continue;

        if (i == 1)  // OK
            communication_write(msg);
        else
            communication_write(errMsg);

        communication_clear_read();

        return 2;
    }

    return 0;
}