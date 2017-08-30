#include "WaitingState.h"
#include "colors.h"
#include "TFT.h"

WaitingState::WaitingState() {
    tft.fillScreen(WHITE);
    tft.fillRoundRect(10, 10, 50, 50, 3, GREEN);
}

int WaitingState::loop() {
}

WaitingState::~WaitingState() {
}