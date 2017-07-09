#include "RedKeyboard.h"
#include "TFT.h"
#include <MCUFRIEND_kbv.h>
#include <avr/pgmspace.h>
#include "colors.h"

MCUFRIEND_kbv& tft = buildTFT();

const bool USB_CABLE_RIGHT = true;
const char KEYBOARD_LETTERS[3][12] PROGMEM = {
    {0, 10, 'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P'},
    {1, 9, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
    {3, 7, 'Y', 'X', 'C', 'V', 'B', 'N', 'M'},
};

const int KEY_TEXT_LPADDING = 8;
const int KEY_TEXT_TPADDING = 5;
const int KEY_HEIGHT = 25;
const int KEY_WIDTH = 25;
const int KEY_OUTER_WIDTH = 30;
const int KEY_OUTER_HEIGHT = 30;
const int KEYBOARD_LMARGIN = 15;
const int KEYBOARD_TOP = 100;

const int KEYBOARD_FIXED_KEYS_SIZE[5][3] = {
    {KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 2, KEY_OUTER_WIDTH + 10},
    {KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH + 10},
    {9 * KEY_OUTER_WIDTH, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 2, KEY_OUTER_WIDTH + 10},
    {9 * KEY_OUTER_WIDTH, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH + 10},
    {2 * KEY_OUTER_WIDTH, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 6 + KEY_WIDTH},
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

void drawButton(const int x, const int y, const int w, const int h) {
    tft.fillRoundRect(x + 2, y + 2, w, h, 3, GREY);                 // Button Shading
    tft.fillRoundRect(x, y, w, h, 3, WHITE);                        // outter button color
    tft.fillRoundRect(x + 1, y + 1, w - 1 * 2, h - 1 * 2, 3, RED);  // inner button color
}

void drawKey(const int x, const int y, const char* c, const int w = KEY_WIDTH, const int lpad = KEY_TEXT_LPADDING,
             const int h = KEY_HEIGHT, const int tpad = KEY_TEXT_TPADDING) {
    drawButton(x, y, w, h);
    tft.setCursor(x + lpad, y + tpad);
    tft.print(c);
}

void drawKeyboard(const char type[3][12]) {
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    for (int y = 0; y < 3; y++) {
        int shiftRight = KEYBOARD_LMARGIN + KEY_OUTER_WIDTH / 2 * pgm_read_byte(&(type[y][0]));
        int characters = pgm_read_byte(&(type[y][1]));
        for (int x = 0; x < characters; x++) {
            char c[2] = {char(pgm_read_byte(&(type[y][x + 2]))), '\0'};
            drawKey(KEY_OUTER_WIDTH * x + shiftRight, KEYBOARD_TOP + KEY_OUTER_HEIGHT * y, c);
        }
    }

    drawKey(KEYBOARD_FIXED_KEYS_SIZE[0][0], KEYBOARD_FIXED_KEYS_SIZE[0][1], "^", KEYBOARD_FIXED_KEYS_SIZE[0][2], 15);
    drawKey(KEYBOARD_FIXED_KEYS_SIZE[1][0], KEYBOARD_FIXED_KEYS_SIZE[1][1], "#", KEYBOARD_FIXED_KEYS_SIZE[1][2], 15);
    drawKey(KEYBOARD_FIXED_KEYS_SIZE[2][0], KEYBOARD_FIXED_KEYS_SIZE[2][1], "<-", KEYBOARD_FIXED_KEYS_SIZE[2][2]);
    drawKey(KEYBOARD_FIXED_KEYS_SIZE[3][0], KEYBOARD_FIXED_KEYS_SIZE[3][1], "OK", KEYBOARD_FIXED_KEYS_SIZE[3][2]);
    // Spacebar
    drawButton(KEYBOARD_FIXED_KEYS_SIZE[4][0], KEYBOARD_FIXED_KEYS_SIZE[4][1], KEYBOARD_FIXED_KEYS_SIZE[4][2],
               KEY_HEIGHT);
}

Keyboard::Keyboard() {
}

void Keyboard::draw() {
    tft.begin(0x9341);
    tft.fillScreen(BLUE);
    tft.setRotation(USB_CABLE_RIGHT ? 3 : 1);
    drawKeyboard(KEYBOARD_LETTERS);
}
