#include "TFT.h"

#define MCUFRIEND

#if defined(MCUFRIEND)
#include <MCUFRIEND_kbv.h>
uint16_t scrollbuf[240];  // my biggest screen is 320x480
MCUFRIEND_kbv& buildTFT() {
    MCUFRIEND_kbv* tft = new MCUFRIEND_kbv();
    return *tft;
}
#else
#define LCD_CS A3             // Chip Select goes to Analog 3
#define LCD_CD A2             // Command/Data goes to Analog 2
#define LCD_WR A1             // LCD Write goes to Analog 1
#define LCD_RD A0             // LCD Read goes to Analog 0
#define LCD_RESET A4          // Can alternately just connect to Arduino's reset pin
#include <Adafruit_TFTLCD.h>  // Hardware-specific library
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#endif
#include <TouchScreen.h>
#define YP A3
#define XM A2
#define YM 9
#define XP 8
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
