#ifndef _COMUNICATION_H
#define _COMUNICATION_H

void communication_setup();
void communication_loop();
char* communication_read();
void communication_clear_read();
void communication_write(char* msg);

#endif