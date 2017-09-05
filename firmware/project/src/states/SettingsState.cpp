#include "SettingsState.h"
#include "TFT.h"
#include "colors.h"
#include "comunication.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

void SettingsState::drawInitialScreen() {
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
    tft.fillRoundRect(131, 200, 72, 34, 4, DARKGREEN);
    tft.setCursor(144, 210);
    tft.print("Save");
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
    tft.print("Off");
}

SettingsState::SettingsState() {
    drawInitialScreen();
}

int SettingsState::loop() {
    return 0;
}

SettingsState::~SettingsState() {
}