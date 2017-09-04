#ifndef _BASE_STATE_H
#define _BASE_STATE_H

class BaseState {
   public:
    virtual int loop() = 0;
    virtual ~BaseState() {
    }
};
#endif