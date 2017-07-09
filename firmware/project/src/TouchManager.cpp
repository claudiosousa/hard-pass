
#include <TouchManager.h>
#include <TouchScreen.h>
#include <Arduino.h>

#define YP A3
#define XM A2
#define YM 9
#define XP 8
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

const uint16_t TS_LEFT = 121;
const uint16_t TS_RT = 910;
const uint16_t TS_TOP = 900;
const uint16_t TS_BOT = 78;

#define MINPRESSURE 20
#define MAXPRESSURE 1000
TSPoint tp;
bool TouchManager_getPoint(int point[2]) {
    tp = ts.getPoint();

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);

    if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE)
        return false;

    point[1] = map(tp.x, TS_LEFT, TS_RT, 240, 0);
    point[0] = map(tp.y, TS_TOP, TS_BOT, 0, 320);
    return true;
}