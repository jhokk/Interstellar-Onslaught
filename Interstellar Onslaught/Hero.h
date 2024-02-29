#pragma once
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "Object.h"
#include "PowerUp.h"
#include "ViewObject.h"

class Hero : public df::Object {

private:
    void kbd(const df::EventKeyboard* p_keyboard_event);
    void move(float dx);
    void hit(const df::EventCollision* p_collision_event);
    int move_slowdown;
    int move_countdown;
    int fire_slowdown;
    int fire_countdown;
    PowerUpType power;
    int power_timer;
    df::ViewObject* p_power_vo;
    void newWave();
    int toCreateWave;
    int wave_num;

public:
    Hero();
    ~Hero();
    int eventHandler(const df::Event* p_e) override;
    //int draw();
    //void fire(df::Vector target);
    void fire();
    void step();
};