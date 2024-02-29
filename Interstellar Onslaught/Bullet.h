#pragma once
#include "Object.h"
#include "EventCollision.h"

class Bullet : public df::Object {

    private:
        int pierce;
        void hit(const df::EventCollision* p_collision_event);
        void out();

    public:
        Bullet(df::Vector start_pos, df::Vector velocity);
        Bullet(df::Vector start_pos, int piercing = 1, std::string name = "Bullet", std::string sprite = "bullet");
        int eventHandler(const df::Event* p_e) override;
        void setPierce(int new_pierce);
        int getPierce() const;
    };