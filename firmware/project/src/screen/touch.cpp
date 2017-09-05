
#include "touch.h"
#include <Arduino.h>
#include <TouchScreen.h>
#include "settings/settings.h"

#define YP A3
#define XM A2
#define YM 9
#define XP 8
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

const uint16_t TS_LEFT = 121;
const uint16_t TS_RT = 910;
const uint16_t TS_TOP = 900;
const uint16_t TS_BOT = 78;

uint16_t top, bottom, right, left;

void touch_setup() {
    if (settings_getScreenIsRightOrientation()) {
        top = TS_TOP;
        bottom = TS_BOT;
        right = TS_RT;
        left = TS_LEFT;
    } else {
        top = TS_BOT;
        bottom = TS_TOP;
        right = TS_LEFT;
        left = TS_RT;
    }
}

#define MINPRESSURE 20
#define MAXPRESSURE 1000
TSPoint tp;
bool touch_getPoint(int point[2]) {
    tp = ts.getPoint();

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);

    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE)
        return false;

    point[1] = map(tp.x, left, right, 240, 0);
    point[0] = map(tp.y, top, bottom, 0, 320);
    return true;
}