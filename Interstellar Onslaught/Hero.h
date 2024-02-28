#pragma once
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"

class Hero : public df::Object {

private:
    void kbd(const df::EventKeyboard* p_keyboard_event);
    void move(float dx);
    int move_slowdown;
    int move_countdown;
    int fire_slowdown;
    int fire_countdown;

public:
    Hero();
    ~Hero();
    int eventHandler(const df::Event* p_e) override;
    //int draw();
    void fire(df::Vector target);
    void step();
};