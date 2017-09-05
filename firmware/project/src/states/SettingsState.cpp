#include "SettingsState.h"
#include "TFT.h"
#include "colors.h"
#include "comunication.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

void SettingsState::drawInitialScreen() {
    tft.fillScreen(BACKGROUND);
    tft.fillRoundRect(40, 100, 250, 40, 4, MESSAGE_BACKGROUND);
    tft.setCursor(110, 115);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setTextWrap(false);
    tft.print("Settings");
}

SettingsState::SettingsState() {
    drawInitialScreen();
}

int SettingsState::loop() {
    return 0;
}

SettingsState::~SettingsState() {
}