#ifndef _COMUNICATION_H
#define _COMUNICATION_H

#include <stdint.h>

void communication_setup();
void communication_loop();
char* communication_read();
void communication_clear_read();
void communication_write(char* msg);
void communication_writebytes(uint8_t* bytes, int len);

#endif