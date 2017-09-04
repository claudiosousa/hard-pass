#include "AskPwdState.h"
#include "MasterPwdState.h"
#include "TFT.h"
#include "TouchManager.h"
#include "colors.h"
#include "comunication.h"
#include <string.h>

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

const int BUTTONS_SIZE[2] = {100, 50};
const int BUTTONS_POS[2][2] = {{50, 150}, {170, 150}}; // j'ai déplacé tes boutons de 10 pixels à droite, ils n'étaient pas centrés
const unsigned int BUTTONS_COLOR[2] = {RED, DARKGREEN};

char *msg;

AskPwdState::AskPwdState()
{
    msg = communication_read();
    tft.fillScreen(BACKGROUND);

    tft.fillRoundRect(30, 40, 260, 40, 4, MESSAGE_BACKGROUND);
    tft.setCursor(76, 52);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setTextWrap(false);
    tft.print("Password asked:");

    int len = strlen(msg);
    int center_position = ((260 -len * 12) / 2) + 30;

    tft.fillRoundRect(30, 90, 260, 40, 4, MESSAGE_BACKGROUND);
    tft.setCursor(center_position, 102);
    tft.setTextColor(ORANGE);
    tft.setTextSize(2);
    tft.setTextWrap(false);
    tft.print(msg);

    for (int i = 0; i < 2; i++)
    {
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

int AskPwdState::loop()
{
    int touch[2];
    if (!TouchManager_getPoint(touch))
        return 0;

    for (int i = 0; i < 2; i++)
    {
        int *pos = BUTTONS_POS[i];

        if (touch[0] < pos[0] || touch[0] > pos[0] + BUTTONS_SIZE[0] || touch[1] < pos[1] ||
            touch[1] > pos[1] + BUTTONS_SIZE[1])
            continue;

        if (i == 1)
        { // OK
            communication_write(msg);
        }
        communication_clear_read();
        return 2;
    }

    return 0;
}