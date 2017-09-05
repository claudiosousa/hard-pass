#ifndef _SETTINGS_H
#define _SETTINGS_H

void settings_setup();
bool settings_getSoundIsOn();
void settings_setSoundOn(bool soundOn);
bool settings_getScreenIsRightOrientation();
void settings_setScreenIsRightOrientation(bool rightOrientation);
bool settings_getRemeberPwd();
void settings_setRemeberPwd(bool remember);

#endif