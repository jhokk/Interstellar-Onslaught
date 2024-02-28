#pragma once
#include "Object.h"
#include "EventCollision.h"

class Bullet : public df::Object {

    private:
        void hit(const df::EventCollision* p_collision_event);
        void out();

    public:
        Bullet(df::Vector start_pos);
        int eventHandler(const df::Event* p_e) override;

    };