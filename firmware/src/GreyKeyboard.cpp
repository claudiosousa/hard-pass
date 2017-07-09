#include "GreyKeyboard.h"
#include <MCUFRIEND_kbv.h>
#include <avr/pgmspace.h>
#include "TFT.h"
#include "colors.h"

#define BACKGROUND ANDROID_KB_BG
#define BUTTON_SHADOW ANDROID_KB_SHADOW
#define BUTTON_BORDER ANDROID_KB_SHADOW
#define BUTTON_BACKGROUND ANDROID_KB_KEY
#define BUTTON_SPECIAL_BACKGROUND ANDROID_KB_SPECIAL_KEY

static const int KEY_TEXT_LPADDING = 11;
static const int KEY_TEXT_TPADDING = 11;
static const int KEY_HEIGHT = 36;
static const int KEY_WIDTH = 30;
static const int KEY_OUTER_WIDTH = 32;
static const int KEY_OUTER_HEIGHT = 40;
static const int KEYBOARD_LMARGIN = 1;
static const int KEYBOARD_TOP = 83;
static const bool USB_CABLE_RIGHT = true;

static const char KEYBOARD_LETTERS[3][12] PROGMEM = {
    {0, 10, 'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P'},
    {1, 9, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
    {3, 7, 'Y', 'X', 'C', 'V', 'B', 'N', 'M'},
};

static const int KEYBOARD_FIXED_KEYS_SIZE[5][3] = {
    {KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 2, KEY_OUTER_WIDTH * 1.5 - 2},
    {KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 1.5 - 2},
    {8.5 * KEY_OUTER_WIDTH + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 2, KEY_OUTER_WIDTH * 1.5 - 2},
    {8.5 * KEY_OUTER_WIDTH + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 1.5 - 2},
    {KEY_OUTER_WIDTH * 1.5 + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 6 + KEY_WIDTH},
};

// const char Mobile_kb[3][12] PROGMEM = {
//   {0, 10, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
//   {1,  9, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'},
//   {3, 7, 'y', 'x', 'c', 'v', 'b', 'n', 'm'},
// };

// const char Mobile_NumKeys[3][12] PROGMEM = {
//   {0, 10, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
//   {0, 10, '-', '/', ':', ';', '(', ')', '$', '&', '@', '"'},
//   {5, 5, '.', ',', '?', '!', '\''}
// };

// const char Mobile_SymKeys[3][12] PROGMEM = {
//   {0, 10, '[', ']', '{', '}', '#', '%', '^', '*', '+', '='},
//   {4, 6, '_', '\\', '|', '~', '<', '>'}, //4
//   {5, 5, '.', ',', '?', '!', '\''}
//};

MCUFRIEND_kbv& tft = buildTFT();
void drawButton(const int x, const int y, const int w, const int h, int bg) {
    tft.fillRoundRect(x, y + 2, w, h, 4, BUTTON_SHADOW);  // Button Shading
    tft.fillRoundRect(x, y, w, h - 2, 4, bg);             // inner button color
}

void drawKey(const int x, const int y, const char* c, const int w = KEY_WIDTH, const int lpad = KEY_TEXT_LPADDING,
             const int bd = BUTTON_BACKGROUND) {
    drawButton(x, y, w, KEY_HEIGHT, bd);
    tft.setCursor(x + lpad, y + KEY_TEXT_TPADDING);
    tft.print(c);
}

void drawKeyboard(const char type[3][12]) {
    tft.setTextSize(2);
    tft.setTextColor(ANDROID_KB_WHITE);
    for (int y = 0; y < 3; y++) {
        int shiftRight = KEYBOARD_LMARGIN + KEY_OUTER_WIDTH / 2 * pgm_read_byte(&(type[y][0]));
        int characters = pgm_read_byte(&(type[y][1]));
        for (int x = 0; x < characters; x++) {
            char c[2] = {char(pgm_read_byte(&(type[y][x + 2]))), '\0'};
            drawKey(KEY_OUTER_WIDTH * x + shiftRight, KEYBOARD_TOP + KEY_OUTER_HEIGHT * y, c);
        }
    }

    drawKey(KEYBOARD_FIXED_KEYS_SIZE[0][0], KEYBOARD_FIXED_KEYS_SIZE[0][1], "^", KEYBOARD_FIXED_KEYS_SIZE[0][2], 17,
            BUTTON_SPECIAL_BACKGROUND);
    drawKey(KEYBOARD_FIXED_KEYS_SIZE[1][0], KEYBOARD_FIXED_KEYS_SIZE[1][1], "#", KEYBOARD_FIXED_KEYS_SIZE[1][2], 17,
            BUTTON_SPECIAL_BACKGROUND);
    drawKey(KEYBOARD_FIXED_KEYS_SIZE[2][0], KEYBOARD_FIXED_KEYS_SIZE[2][1], "<-", KEYBOARD_FIXED_KEYS_SIZE[2][2],
            KEY_TEXT_LPADDING, BUTTON_SPECIAL_BACKGROUND);
    drawKey(KEYBOARD_FIXED_KEYS_SIZE[3][0], KEYBOARD_FIXED_KEYS_SIZE[3][1], "OK", KEYBOARD_FIXED_KEYS_SIZE[3][2],
            KEY_TEXT_LPADDING, ANDROID_KB_RETURN);
    // Spacebar
    drawButton(KEYBOARD_FIXED_KEYS_SIZE[4][0], KEYBOARD_FIXED_KEYS_SIZE[4][1], KEYBOARD_FIXED_KEYS_SIZE[4][2],
               KEY_HEIGHT, BUTTON_BACKGROUND);
}

void Keyboard::draw() {
    tft.begin(0x9341);

    tft.fillScreen(BACKGROUND);
    tft.setRotation(USB_CABLE_RIGHT ? 3 : 1);
    drawKeyboard(KEYBOARD_LETTERS);
}
