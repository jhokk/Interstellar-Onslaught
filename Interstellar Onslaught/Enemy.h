#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"


class Enemy : public df::Object {

private:
	int points;
	void out();
	void hit(const df::EventCollision* p_collision_event);
	void moveToStart();
	void step(const df::EventStep* p_step_event);
	void shoot();

public:
	Enemy(int level=0);
	~Enemy();
	int eventHandler(const df::Event* p_e) override;
};