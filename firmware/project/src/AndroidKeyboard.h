#ifndef _GREY_KEYBOARD_H
#define _GREY_KEYBOARD_H

#include <MCUFRIEND_kbv.h>

class Keyboard {
   public:
    void draw();
    char * processKeys();
};

#endif