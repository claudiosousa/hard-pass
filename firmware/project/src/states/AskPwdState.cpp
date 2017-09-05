#include "AskPwdState.h"
#include <string.h>
#include "MasterPwdState.h"
#include "Sha/sha1.h"
#include "TFT.h"
#include "touch.h"
#include "colors.h"
#include "comunication.h"
#include "sound.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

const int BUTTONS_SIZE[2] = {100, 50};
const int BUTTONS_POS[2][2] = {{50, 150}, {170, 150}};
const unsigned int BUTTONS_COLOR[2] = {DARKRED, DARKGREEN};

char *msg;
char *pwdModifier;
const char *errMsg = "";

void AskPwdState::drawAskPwdStateScreen() {
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

void AskPwdState::parseMessage() {
    msg = communication_read();
    int i = 0;
    while (msg[i] != '\n')
        i++;
    msg[i] = 0;

    pwdModifier = msg + (i + 1);
}
AskPwdState::AskPwdState() {
    sound_passwordRequest();
    parseMessage();
    drawAskPwdStateScreen();
}

int AskPwdState::loop() {
    int touch[2];
    if (!touch_getPoint(touch))
        return 0;

    for (int i = 0; i < 2; i++) {
        int *pos = BUTTONS_POS[i];

        if (touch[0] < pos[0] || touch[0] > pos[0] + BUTTONS_SIZE[0] || touch[1] < pos[1] ||
            touch[1] > pos[1] + BUTTONS_SIZE[1])
            continue;

        if (i == 1) {  // OK
            uint8_t *hash;
            Sha1.init();
            Sha1.print(msg);
            hash = Sha1.result();

            communication_writebytes(hash, 20);
        } else
            communication_write(errMsg);

        communication_clear_read();

        return 2;
    }

    return 0;
}

AskPwdState::~AskPwdState() {
}