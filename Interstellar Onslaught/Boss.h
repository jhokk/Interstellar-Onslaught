#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "Music.h"

class Boss : public df::Object {

private:
	void hit(const df::EventCollision* p_collision_event);
	void step(const df::EventStep* p_step_event);
	void fire();
	int target_angle;
	int health;
	df::Music* p_music;

public:
	Boss();
	~Boss();
	int eventHandler(const df::Event* p_e) override;
};