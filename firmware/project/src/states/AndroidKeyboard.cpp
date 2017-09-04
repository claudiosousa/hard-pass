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

const int KEY_TEXT_LPADDING = 10;
const int KEY_TEXT_TPADDING = 11;
const int KEY_HEIGHT = 36;
const int KEY_WIDTH = 29;
const int KEY_OUTER_WIDTH = 32;
const int KEY_OUTER_HEIGHT = 40;
const int KEYBOARD_LMARGIN = 1;
const int KEYBOARD_TOP = 83;

const int KEYBOARD_TB_SIZE[4] = {5, 30, 310, 30};  // x, y, w, h

const int KEYBOARD_TB_TEXT_SPACE[3] = {5, 8, 13};  // lpad, tpad, width

const char MAX_TEXT_LENGTH = 23;
char enteredText[MAX_TEXT_LENGTH];
char currentTextLegth = 0;

bool shiftPressed = false;
bool symbolsPressed = false;

const char KEYBOARD_UPPER_CAPS[3][12] PROGMEM = {
    {0, 10, 'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P'},
    {1, 9, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
    {3, 7, 'Y', 'X', 'C', 'V', 'B', 'N', 'M'},
};

const char KEYBOARD_LOWER_CAPS[3][12] PROGMEM = {
    {0, 10, 'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p'},
    {1, 9, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'},
    {3, 7, 'y', 'x', 'c', 'v', 'b', 'n', 'm'},
};

const char KEYBOARD_SYMBOLS_CAPS[3][12] PROGMEM = {
    {0, 10, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    {1, 9, '<', '>', '"', '/', '(', ')', '!', '=', '$'},
    {3, 7, '\\', '+', '-', ';', ',', '.', '_'},
};

const int KEYBOARD_FIXED_KEYS_SIZE[5][3] = {
    {KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 2, KEY_OUTER_WIDTH * 1.5 - 3},
    {KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 1.5 - 3},
    {8.5 * KEY_OUTER_WIDTH + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 2, KEY_OUTER_WIDTH * 1.5 - 3},
    {8.5 * KEY_OUTER_WIDTH + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 1.5 - 3},
    {KEY_OUTER_WIDTH * 1.5 + KEYBOARD_LMARGIN, KEYBOARD_TOP + KEY_OUTER_HEIGHT * 3, KEY_OUTER_WIDTH * 6 + KEY_WIDTH}};

const char* KEYBOARD_FIXED_KEYS_LETTERS[5] = {"^", "#", "<-", "OK", ""};

char (*currentCaps)[12];

MCUFRIEND_kbv& tft = buildTFT();

void drawButton(const int x, const int y, const int w, const int h, int bg) {
    tft.fillRoundRect(x, y, w, h, 3, BUTTON_SHADOW);  // Button Shading
    tft.fillRoundRect(x, y, w, h - 2, 3, bg);         // inner button color
}

void drawKey(const int x, const int y, const char* c, const int w = KEY_WIDTH, const int lpad = KEY_TEXT_LPADDING,
             const int bg = BUTTON_BACKGROUND, const int fg = ANDROID_KB_WHITE) {
    drawButton(x, y, w, KEY_HEIGHT, bg);
    tft.setCursor(x + lpad, y + KEY_TEXT_TPADDING);
    tft.setTextColor(fg);
    tft.print(c);
}

void drawKeyPos(int x, int y, bool active = false) {
    int bg = active ? ANDROID_KB_ACTIVE : BUTTON_BACKGROUND;
    int fg = ANDROID_KB_WHITE;
    if (y >= 0) {
        int shiftRight = KEYBOARD_LMARGIN + KEY_OUTER_WIDTH / 2 * pgm_read_byte(&(currentCaps[y][0]));
        char c = char(pgm_read_byte(&(currentCaps[y][x + 2])));
        char s[2] = {c, '\0'};
        drawKey(KEY_OUTER_WIDTH * x + shiftRight, KEYBOARD_TOP + KEY_OUTER_HEIGHT * y, s, KEY_WIDTH, KEY_TEXT_LPADDING,
                bg);
    } else {
        y = -y - 1;

        int padding = y < 2 ? 17 : KEY_TEXT_LPADDING;

        if (y < 4 && bg == BUTTON_BACKGROUND) {
            bg = y == 3 ? ANDROID_KB_RETURN : BUTTON_SPECIAL_BACKGROUND;
        }
        if (y == 0 && shiftPressed || y == 1 && symbolsPressed) {
            fg = BUTTON_BACKGROUND;
            bg = ANDROID_KB_WHITE;
        }

        drawKey(KEYBOARD_FIXED_KEYS_SIZE[y][0], KEYBOARD_FIXED_KEYS_SIZE[y][1], KEYBOARD_FIXED_KEYS_LETTERS[y],
                KEYBOARD_FIXED_KEYS_SIZE[y][2], padding, bg, fg);
    }
}
void drawTextBox() {
    tft.fillRoundRect(KEYBOARD_TB_SIZE[0], KEYBOARD_TB_SIZE[1], KEYBOARD_TB_SIZE[2], KEYBOARD_TB_SIZE[3], 3,
                      ANDROID_KB_WHITE);  // Button Shading
}

void resetText() {
    for (int i = 0; i < MAX_TEXT_LENGTH; i++)
        enteredText[i] = 0;
}

void drawKeyboard() {
    if (shiftPressed)
        currentCaps = (char(*)[12])KEYBOARD_UPPER_CAPS;
    else if (symbolsPressed)
        currentCaps = (char(*)[12])KEYBOARD_SYMBOLS_CAPS;
    else
        currentCaps = (char(*)[12])KEYBOARD_LOWER_CAPS;

    tft.setTextSize(2);
    for (int y = 0; y < 3; y++) {
        int characters = pgm_read_byte(&(currentCaps[y][1]));
        for (int x = 0; x < characters; x++)
            drawKeyPos(x, y);
    }

    for (int y = 0; y < 5; y++)
        drawKeyPos(0, -y - 1);
}

Keyboard::~Keyboard(){

}

void Keyboard::draw() {

    tft.fillScreen(BACKGROUND);

    resetText();
    drawTextBox();

    drawKeyboard();
}

bool isInButton(const int x, const int y, const int w, const int h, const int tx, const int ty) {
    return tx >= x && tx <= x + w && ty >= y && ty <= y + h;
}

char getPointTouch(const int point[2], int pos[2]) {
    for (int y = 0; y < 3; y++) {
        int shiftRight = KEYBOARD_LMARGIN + KEY_OUTER_WIDTH / 2 * pgm_read_byte(&(currentCaps[y][0]));
        int characters = pgm_read_byte(&(currentCaps[y][1]));
        for (int x = 0; x < characters; x++) {
            if (!isInButton(KEY_OUTER_WIDTH * x + shiftRight, KEYBOARD_TOP + KEY_OUTER_HEIGHT * y, KEY_WIDTH,
                            KEY_HEIGHT, point[0], point[1]))
                continue;

            pos[0] = x;
            pos[1] = y;
            return char(pgm_read_byte(&(currentCaps[y][x + 2])));
        }
    }
    for (int y = 0; y < 5; y++) {
        if (!isInButton(KEYBOARD_FIXED_KEYS_SIZE[y][0], KEYBOARD_FIXED_KEYS_SIZE[y][1], KEYBOARD_FIXED_KEYS_SIZE[y][2],
                        KEY_HEIGHT, point[0], point[1]))
            continue;
        pos[0] = 0;
        pos[1] = -y - 1;
        return y == 4 ? 32 /*space*/ : y + 1;
    }
    return 0;
}

int point[2];
int pos[2];
char lastTouch = 0;
int lastTouchPos[2];
unsigned long lastTouchTime = 0;
char getPressedTouch() {
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

void printTbChar(char c) {
    tft.setCursor(KEYBOARD_TB_SIZE[0] + KEYBOARD_TB_TEXT_SPACE[0] + currentTextLegth * KEYBOARD_TB_TEXT_SPACE[2],
                  KEYBOARD_TB_SIZE[1] + KEYBOARD_TB_TEXT_SPACE[1]);
    tft.setTextColor(ANDROID_KB_BG, ANDROID_KB_WHITE);
    tft.print(c);
}

char* Keyboard::processKeys() {
    char key = getPressedTouch();
    if (!key)
        return NULL;

    if (key < 5) {
        // TODO: handle special keys

        switch (key) {
            case 1:  // shift
                shiftPressed = !shiftPressed;
                drawKeyboard();
                drawKeyPos(0, -1);
                if (symbolsPressed) {
                    symbolsPressed = false;
                    drawKeyPos(0, -2);
                }
                break;
            case 2:  // hash
                symbolsPressed = !symbolsPressed;

                if (shiftPressed) {
                    shiftPressed = false;
                    drawKeyboard();
                    drawKeyPos(0, -1);
                } else
                    drawKeyboard();

                drawKeyPos(0, -2);
                break;
            case 3:  // backspace
                if (currentTextLegth > 0) {
                    currentTextLegth--;
                    enteredText[currentTextLegth] = 0;
                    printTbChar(' ');
                }
                break;
            case 4:  // OK
                if (currentTextLegth > 0) {
                    return enteredText;
                }
                break;
        }
        return NULL;
    }

    if (currentTextLegth == MAX_TEXT_LENGTH)
        return NULL;
    tft.setCursor(KEYBOARD_TB_SIZE[0] + KEYBOARD_TB_TEXT_SPACE[0] + currentTextLegth * KEYBOARD_TB_TEXT_SPACE[2],
                  KEYBOARD_TB_SIZE[1] + KEYBOARD_TB_TEXT_SPACE[1]);
    printTbChar('*');
    enteredText[currentTextLegth] = key;
    currentTextLegth++;
    return NULL;
}