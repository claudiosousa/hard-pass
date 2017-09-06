#include "WaitingState.h"
#include "screen/TFT.h"
#include "screen/colors.h"
#include "communication/communication.h"

#define BACKGROUND ANDROID_KB_BG
#define MESSAGE_BACKGROUND ANDROID_KB_KEY

void WaitingState::drawWaitingScreen(){
    tft.fillScreen(BACKGROUND);
    tft.setCursor(90, 107);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setTextWrap(false);
    tft.print("Waiting");
    time = millis();
}

WaitingState::WaitingState() {
    drawWaitingScreen();
}

void WaitingState::drawScreenLoop() {
    unsigned long time2 = millis();
    const int16_t position_x = 220;

    if (time2 < time + 1000)
        return;

    if (counter == 3) {
        counter = 0;
        tft.fillRect(position_x, 102, 30, 29, BACKGROUND);
    }

    tft.drawChar(position_x + counter * 10, 114, '.', WHITE, BACKGROUND, 2);
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