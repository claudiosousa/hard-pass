#include "WaitingState.h"
#include "TFT.h"
#include "colors.h"
#include "comunication.h"

unsigned long time;
const int16_t x = 220;
int counter = 0;

WaitingState::WaitingState() {
    tft.fillScreen(WHITE);
    tft.setCursor(40, 100);
    tft.setTextColor(BLACK);
    tft.setTextSize(4);
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
        tft.fillRect(x, 110, 40, 40, WHITE);
    }

    tft.drawChar(x + counter * 10, 115, '.', BLACK, WHITE, 2);
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