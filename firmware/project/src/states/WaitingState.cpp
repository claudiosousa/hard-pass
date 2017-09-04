#include "WaitingState.h"
#include "TFT.h"
#include "colors.h"
#include "comunication.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

unsigned long time;
const int16_t x = 210;
int counter = 0;

WaitingState::WaitingState() {
    tft.fillScreen(BACKGROUND);
    tft.fillRoundRect(40, 100, 250, 40, 4, MESSAGE_BACKGROUND);
    tft.setCursor(110, 115);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setTextWrap(false);
    tft.print("Waiting");
    time = millis();
}

void WaitingState::drawScreenLoop() {
    unsigned long time2 = millis();

    if (time2 < time + 1000)
        return;

    if (counter == 3) {
        counter = 0;
        tft.fillRect(x, 110, 30, 29, MESSAGE_BACKGROUND);
    }

    tft.drawChar(x + counter * 5, 120, '.', WHITE, MESSAGE_BACKGROUND, 1);
    counter++;

    time = millis();
}
int WaitingState::loop() {
    drawScreenLoop();

    char* msg = communication_read();
    return msg ? 3 : 0;
}

WaitingState::~WaitingState() {
}