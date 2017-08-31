#include "WaitingState.h"
#include "colors.h"
#include "TFT.h"

WaitingState::WaitingState() {
    tft.fillScreen(WHITE);
    tft.drawChar(40, 100, 'W', RED, WHITE, 5);
    tft.drawChar(70, 100, 'a', RED, WHITE, 5);
    tft.drawChar(100, 100, 'i', RED, WHITE, 5);
    tft.drawChar(130, 100, 't', RED, WHITE, 5);
    tft.drawChar(160, 100, 'i', RED, WHITE, 5);
    tft.drawChar(190, 100, 'n', RED, WHITE, 5);
    tft.drawChar(220, 100, 'g', RED, WHITE, 5);
    tft.drawChar(250, 120, '.', RED, WHITE, 2);
    tft.drawChar(260, 120, '.', RED, WHITE, 2);
    tft.drawChar(270, 120, '.', RED, WHITE, 2);
    
}

int WaitingState::loop() {
}

WaitingState::~WaitingState() {
}