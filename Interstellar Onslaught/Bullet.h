#pragma once
#include "Object.h"
#include "EventCollision.h"

namespace df {
    class Bullet : public Object {

    private:
        void hit(const EventCollision* p_collision_event);
        void out();

    public:
        Bullet(Vector start_pos);
        int eventHandler(const Event* p_e) override;

    };
}
