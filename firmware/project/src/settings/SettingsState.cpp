#include "SettingsState.h"
#include "communication/communication.h"
#include "screen/TFT.h"
#include "screen/colors.h"
#include "screen/touch.h"
#include "settings/settings.h"
#include "sound/sound.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

const int BUTTONS_POS[7][4] = {
    {131, 203, 195, 229}, // OK  // x1, x2, y1, y2
    {165, 239, 65, 99},   // Left
    {245, 319, 65, 99},   // Right
    {165, 239, 107, 141}, // Sound ON
    {245, 319, 107, 141}, // Sound OFF
    {165, 239, 149, 183}, // Remember ON
    {245, 319, 149, 183}  // Remember OFF
};

void SettingsState::drawButton(int button, int text_padding, char *text, uint16_t background)
{
    int *pos = BUTTONS_POS[button];
    tft.fillRoundRect(pos[0], pos[2], pos[1] - pos[0], pos[3] - pos[2], 4, background);
    tft.setCursor(pos[0] + text_padding, pos[2] + 10);
    tft.print(text);
}

void SettingsState::drawInitialScreen()
{
    tft.fillScreen(BACKGROUND);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setTextWrap(false);
    tft.setCursor(95, 20);
    tft.print("Settings");
    tft.setTextSize(2);
    tft.setCursor(12, 75);
    tft.print("Cable");
    tft.setCursor(12, 117);
    tft.print("Sound");
    tft.setCursor(12, 159);
    tft.print("Remember PWD");
    drawButton(0, 26, "Ok", DARKGREEN);
    drawButtons();
}

void SettingsState::drawButtons()
{
    bool right = settings_getScreenIsRightOrientation();
    drawButton(1, 15, "Left", right ? MESSAGE_BACKGROUND : ANDROID_KB_ACTIVE);
    drawButton(2, 10, "Right", right ? ANDROID_KB_ACTIVE : MESSAGE_BACKGROUND);

    bool sound = settings_getSoundIsOn();
    drawButton(3, 25, "On",  sound ? ANDROID_KB_ACTIVE : MESSAGE_BACKGROUND);
    drawButton(4, 20, "Off", sound ? MESSAGE_BACKGROUND : ANDROID_KB_ACTIVE);

    bool remember = settings_getRemeberPwd();
    drawButton(5, 25, "On",  remember ? ANDROID_KB_ACTIVE : MESSAGE_BACKGROUND);
    drawButton(6, 20, "Off", remember ? MESSAGE_BACKGROUND : ANDROID_KB_ACTIVE);
}

SettingsState::SettingsState()
{
    drawInitialScreen();
}

int getButtonPress()
{
    int touch[2];
    if (!touch_getPoint(touch))
        return 0;

    for (int i = 0; i < 7; i++)
    {
        int *pos = BUTTONS_POS[i];
        if (touch[0] >= pos[0] && touch[0] <= pos[1] && touch[1] >= pos[2] && touch[1] <= pos[3])
            return i + 1;
    }
    return 0;
}
int SettingsState::loop()
{
    int buttonPress = getButtonPress();
    if (buttonPress != 0)
        sound_playTouch();
        
    switch (buttonPress)
    {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        settings_setScreenIsRightOrientation(false);
        TFT_updateScreenOrientation();
        touch_setup();
        drawInitialScreen();
        break;
    case 3:
        settings_setScreenIsRightOrientation(true);
        TFT_updateScreenOrientation();
        touch_setup();
        drawInitialScreen();
        break;
    case 4:
        settings_setSoundOn(true);
        drawButtons();
        break;
    case 5:
        settings_setSoundOn(false);
        drawButtons();
        break;
    case 6:
        settings_setRemeberPwd(true);
        drawButtons();
        break;
    case 7:
        settings_setRemeberPwd(false);
        drawButtons();
        break;
    }
    return 0;
}

SettingsState::~SettingsState()
{
}