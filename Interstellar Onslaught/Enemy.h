#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"


class Enemy : public df::Object {

private:
	int points; //number of points this enemy is worth
	int shoot_chance; //odds to fire an enemy bullet as 1/x each step
	void out();
	void hit(const df::EventCollision* p_collision_event);
	void moveToStart();
	void step(const df::EventStep* p_step_event);
	void shoot();

public:
	Enemy(int wave, int level=0);
	~Enemy();
	int eventHandler(const df::Event* p_e) override;
};