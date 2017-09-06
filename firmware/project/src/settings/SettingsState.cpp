#include "SettingsState.h"
#include "communication/communication.h"
#include "screen/TFT.h"
#include "screen/colors.h"
#include "screen/touch.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

const int BUTTONS_POS[7][4] = {
    {131, 203, 195, 229},    // OK  // x1, x2, y1, y2
    {165, 239, 65, 99},      // Left
    {245, 319, 65, 99},      // Right
    {165, 239, 107, 141},    // Sound ON    165, 107, 74, 34
    {245, 319, 107, 141},    // Sound OFF
    {165, 239, 149, 183},    // Remember ON
    {245, 319, 149, 183}     // Remember OFF    
};

void SettingsState::drawButton(int button, int text_padding, char * text, uint16_t background) {
    int *pos = BUTTONS_POS[button];
    tft.fillRoundRect(pos[0], pos[2], pos[1]-pos[0], pos[3]-pos[2], 4, background);
    tft.setCursor(pos[0]+text_padding, pos[2]+10);
    tft.print(text);
}

void SettingsState::drawInitialScreen(){
    tft.fillScreen(BACKGROUND);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setTextWrap(false);
    tft.setCursor(95, 20);
    tft.print("Settings");
    tft.setTextSize(2);
    
    tft.setCursor(12, 75);
    tft.print("Cable");
    drawButton(1, 15, "Left", MESSAGE_BACKGROUND);
    drawButton(2, 10, "Right", MESSAGE_BACKGROUND);

    tft.setCursor(12, 117);
    tft.print("Sound");
    drawButton(3, 25, "On", MESSAGE_BACKGROUND);
    drawButton(4, 20, "Off", MESSAGE_BACKGROUND);

    tft.setCursor(12, 159);
    tft.print("Remember PWD");
    drawButton(5, 25, "On", MESSAGE_BACKGROUND);
    drawButton(6, 20, "Off", MESSAGE_BACKGROUND);

    drawButton(0, 26, "Ok", DARKGREEN);
    
   /*    
    tft.fillRoundRect(131, 195, 72, 34, 4, DARKGREEN);
    tft.setCursor(157, 205);
    tft.print("Ok");
    tft.fillRoundRect(165, 107, 74, 34, 4, MESSAGE_BACKGROUND);
    tft.setCursor(190, 117);
    tft.print("On");
    tft.fillRoundRect(245, 107, 74, 34, 4, MESSAGE_BACKGROUND);
    tft.setCursor(265, 117);
    tft.print("Off");
    tft.fillRoundRect(165, 65, 74, 34, 4, MESSAGE_BACKGROUND);
    tft.setCursor(180, 75);
    tft.print("Left");
    tft.fillRoundRect(245, 65, 74, 34, 4, MESSAGE_BACKGROUND);
    tft.setCursor(255, 75);
    tft.print("Right");
    tft.fillRoundRect(165, 149, 74, 34, 4, MESSAGE_BACKGROUND);
    tft.setCursor(190, 159);
    tft.print("On");
    tft.fillRoundRect(245, 149, 74, 34, 4, MESSAGE_BACKGROUND);
    tft.setCursor(265, 159);
    tft.print("Off");*/
}

SettingsState::SettingsState()
{
    drawInitialScreen();
}

int SettingsState::loop(){
    int touch[2];
    if (!touch_getPoint(touch))
        return 0;

    for (int i = 0; i < 7; i++) {
        int *pos = BUTTONS_POS[i];
        if (touch[0] >= pos[0] && touch[0] <= pos[1] && touch[1] >= pos[2] && touch[1] <= pos[3])
            return 1;
    }
}

SettingsState::~SettingsState()
{
}