#include "WaitingState.h"
#include "colors.h"
#include "TFT.h"

unsigned long time;
const int16_t x = 260;
int counter = 1;

WaitingState::WaitingState()
{

    tft.fillScreen(WHITE);
    tft.setCursor(40, 100);
    tft.setTextColor(BLACK);
    tft.setTextSize(5);
    tft.setTextWrap(false);
    tft.print("Waiting");
    time = millis();
}

int WaitingState::loop()
{

    unsigned long time2 = millis();

    if (time2 < time + 1000)
        return 0;

    if (counter == 3)
    {
        counter = 1;
        tft.fillRect(x, 110, 20, 10, YELLOW);
    }
    tft.drawChar(x + counter * 10, 120, '.', BLACK, WHITE, 2);
    counter++;

    time = millis();
}

WaitingState::~WaitingState()
{
}