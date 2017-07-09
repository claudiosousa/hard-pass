#include "AndroidKeyboard.h"
#include <MCUFRIEND_kbv.h>
#include <avr/pgmspace.h>
#include "TFT.h"
#include "TouchManager.h"
#include "colors.h"

#define BACKGROUND ANDROID_KB_BG
#define BUTTON_SHADOW ANDROID_KB_SHADOW
#define BUTTON_BORDER ANDROID_KB_SHADOW
#define BUTTON_BACKGROUND ANDROID_KB_KEY
#define BUTTON_SPECIAL_BACKGROUND ANDROID_KB_SPECIAL_KEY

#define KEY_PRESS_HIGHLIGHT_DEBOUNCE 100

static const int KEY_TEXT_LPADDING = 10;
static const int KEY_TEXT_TPADDING = 11;
static const int KEY_HEIGHT = 36;
static const int KEY_WIDTH = 29;
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
    {KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 2, KEY_OUTER_WIDTH * 1.5 - 3},
    {KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 1.5 - 3},
    {8.5 * KEY_OUTER_WIDTH + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 2, KEY_OUTER_WIDTH * 1.5 - 3},
    {8.5 * KEY_OUTER_WIDTH + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 1.5 - 3},
    {KEY_OUTER_WIDTH * 1.5 + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 6 + KEY_WIDTH}};

static const char* KEYBOARD_FIXED_KEYS_LETTERS[5] = {"^", "#", "<-", "OK", ""};

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
    tft.fillRoundRect(x, y, w, h, 3, BUTTON_SHADOW);  // Button Shading
    tft.fillRoundRect(x, y, w, h - 2, 3, bg);         // inner button color
}

void drawKey(const int x, const int y, const char* c, const int w = KEY_WIDTH, const int lpad = KEY_TEXT_LPADDING,
             const int bg = BUTTON_BACKGROUND) {
    drawButton(x, y, w, KEY_HEIGHT, bg);
    tft.setCursor(x + lpad, y + KEY_TEXT_TPADDING);
    tft.print(c);
}

void drawKeyPos(int x, int y, bool active = false) {
    int bg = active ? ANDROID_KB_ACTIVE : BUTTON_BACKGROUND;

    if (y >= 0) {
        int shiftRight = KEYBOARD_LMARGIN + KEY_OUTER_WIDTH / 2 * pgm_read_byte(&(KEYBOARD_LETTERS[y][0]));
        char c = char(pgm_read_byte(&(KEYBOARD_LETTERS[y][x + 2])));
        char s[2] = {c, '\0'};
        drawKey(KEY_OUTER_WIDTH * x + shiftRight, KEYBOARD_TOP + KEY_OUTER_HEIGHT * y, s, KEY_WIDTH, KEY_TEXT_LPADDING,
                bg);
    } else {
        y = -y - 1;

        int padding = y < 2 ? 17 : KEY_TEXT_LPADDING;
        if (y < 4 && bg == BUTTON_BACKGROUND)
            bg = y == 3 ? ANDROID_KB_RETURN : BUTTON_SPECIAL_BACKGROUND;
        drawKey(KEYBOARD_FIXED_KEYS_SIZE[y][0], KEYBOARD_FIXED_KEYS_SIZE[y][1], KEYBOARD_FIXED_KEYS_LETTERS[y],
                KEYBOARD_FIXED_KEYS_SIZE[y][2], padding, bg);
    }
}
void drawTextBox(){
    tft.setTextSize(2);
    tft.setTextColor(ANDROID_KB_BG);
    tft.fillRoundRect(5, 30, 310, 30, 3, ANDROID_KB_WHITE);  // Button Shading
    tft.setCursor(10, 38);
    //tft.print("********************");
    tft.print("*******");
}

void drawKeyboard(const char type[3][12]) {

    drawTextBox();

    tft.setTextSize(2);
    tft.setTextColor(ANDROID_KB_WHITE);
    for (int y = 0; y < 3; y++) {
        int characters = pgm_read_byte(&(type[y][1]));
        for (int x = 0; x < characters; x++)
            drawKeyPos(x, y);
    }

    for (int y = 0; y < 5; y++)
        drawKeyPos(0, -y - 1);
}

void Keyboard::draw() {
    tft.begin(0x9341);

    tft.fillScreen(BACKGROUND);
    tft.setRotation(USB_CABLE_RIGHT ? 3 : 1);
    drawKeyboard(KEYBOARD_LETTERS);
}

bool isInButton(const int x, const int y, const int w, const int h, const int tx, const int ty) {
    return tx >= x && tx <= x + w && ty >= y && ty <= y + h;
}

char getPointTouch(const int point[2], int pos[2]) {
    for (int y = 0; y < 3; y++) {
        int shiftRight = KEYBOARD_LMARGIN + KEY_OUTER_WIDTH / 2 * pgm_read_byte(&(KEYBOARD_LETTERS[y][0]));
        int characters = pgm_read_byte(&(KEYBOARD_LETTERS[y][1]));
        for (int x = 0; x < characters; x++) {
            if (!isInButton(KEY_OUTER_WIDTH * x + shiftRight, KEYBOARD_TOP + KEY_OUTER_HEIGHT * y, KEY_WIDTH,
                            KEY_HEIGHT, point[0], point[1]))
                continue;

            pos[0] = x;
            pos[1] = y;
            return char(pgm_read_byte(&(KEYBOARD_LETTERS[y][x + 2])));
        }
    }
    for (int y = 0; y < 5; y++) {
        if (!isInButton(KEYBOARD_FIXED_KEYS_SIZE[y][0], KEYBOARD_FIXED_KEYS_SIZE[y][1], KEYBOARD_FIXED_KEYS_SIZE[y][2],
                        KEY_HEIGHT, point[0], point[1]))
            continue;
        pos[0] = 0;
        pos[1] = -y - 1;
        return y + 48;
    }
    return 0;
}

int point[2];
int pos[2];
char lastTouch = 0;
int lastTouchPos[2];
unsigned long lastTouchTime = 0;
char Keyboard::getPressedTouch() {
    char res = 0;
    if (TouchManager_getPoint(point))
        res = getPointTouch(point, pos);

    unsigned long ms = millis();
    if (lastTouch && res != lastTouch) {
        if (res || (ms - lastTouchTime) > KEY_PRESS_HIGHLIGHT_DEBOUNCE) {
            drawKeyPos(lastTouchPos[0], lastTouchPos[1]);
            lastTouch = 0;
        }
    }
    if (res) {
        lastTouchTime = ms;
        if (res != lastTouch)
            drawKeyPos(pos[0], pos[1], true);
    }
    if (!res || lastTouch == res)
        return 0;
    lastTouchPos[0] = pos[0];
    lastTouchPos[1] = pos[1];
    lastTouch = res;
    return res;
}
