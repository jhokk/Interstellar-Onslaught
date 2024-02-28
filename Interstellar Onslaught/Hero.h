#pragma once
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"

namespace df {
    class Hero : public Object {

    private:
        void kbd(const EventKeyboard* p_keyboard_event);
        void move(float dx, float dy);
        int move_slowdown;
        int move_countdown;
        int fire_slowdown;
        int fire_countdown;

    public:
        Hero();
        ~Hero();
        int eventHandler(const Event* p_e) override;
        //int draw();
        void fire(Vector target);
        void step();
    };
}