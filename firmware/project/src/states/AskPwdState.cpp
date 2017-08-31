#include "AskPwdState.h"
#include "TFT.h"
#include "colors.h"

AskPwdState::AskPwdState() {
    tft.fillScreen(WHITE);
    tft.fillRoundRect(10, 10, 50, 50, 3, RED);
}

int AskPwdState::loop() {
    return 0;
}

AskPwdState::~AskPwdState() {
}