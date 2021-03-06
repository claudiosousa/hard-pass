#include "AskPwdState.h"
#include <string.h>
#include "Sha/sha1.h"
#include "communication/communication.h"
#include "screen/TFT.h"
#include "screen/colors.h"
#include "screen/touch.h"
#include "settings/settings.h"
#include "sound/sound.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

const int BUTTONS_SIZE[2] = {100, 50};
const int BUTTONS_POS[2][2] = {{50, 150}, {170, 150}};
const unsigned int BUTTONS_COLOR[2] = {DARKRED, DARKGREEN};

char *domain;
char *pwdModifier;
const char *errMsg = "";

void AskPwdState::drawAskPwdStateScreen() {
    tft.fillScreen(BACKGROUND);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setTextWrap(false);
    tft.setCursor(30, 35);
    tft.print("Password asked:");
    int len = strlen(domain);
    int center_position = ((260 - len * 12) / 2) + 30;
    tft.fillRoundRect(30, 82, 260, 40, 4, MESSAGE_BACKGROUND);
    tft.setCursor(center_position, 95);
    tft.setTextColor(ORANGE);
    tft.setTextSize(2);
    tft.print(domain);
    
    for (int i = 0; i < 2; i++) {
        int *pos = BUTTONS_POS[i];
        tft.fillRoundRect(pos[0], pos[1], BUTTONS_SIZE[0], BUTTONS_SIZE[1], 3, BUTTONS_COLOR[i]);
    }    
    
    tft.setTextColor(WHITE);
    tft.setCursor(65, 168);
    tft.print("Cancel");
    tft.setCursor(210, 168);
    tft.print("Ok");
}

void AskPwdState::parseMessage() {
    domain = communication_read();
    int i = 0;
    while (domain[i] != '\n')
        i++;
    domain[i] = 0;

    pwdModifier = domain + (i + 1);
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
                    
        sound_playTouch();

        if (i == 1) {  // OK
            uint8_t *hash;
            Sha1.init();
            Sha1.print(masterPwd);
            Sha1.print('|');
            Sha1.print(domain);
            Sha1.print('|');
            Sha1.print(pwdModifier);
            hash = Sha1.result();

            communication_writebytes(hash, 20);
        } else
            communication_write(errMsg);

        communication_clear_read();
        
        if (settings_getRemeberPwd())
            return 2;
        else
            return 1;
    }

    return 0;
}

AskPwdState::~AskPwdState() {
}