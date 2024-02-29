#include "Object.h"
#include "EventCollision.h"

#define POWER_DURATION 150 // number of steps before losing a powerup

enum PowerUpType {
	UNDEFINED_TYPE = -1, ///< Undefined
	SPREAD,			  ///< Fires two extra bullets
	RAPID,			  ///< Reduces fire slowdown
	PIERCE,			  ///< Fires piercing bullets
	NONE,			  ///< No powerup
};

class PowerUp : public df::Object {

private:
	//PowerUpType power;
	void hit(const df::EventCollision* p_collision_event);
	void out();

public:
	PowerUp(df::Vector start_pos);
	//PowerUpType getPower() const;
	int eventHandler(const df::Event* p_e) override;
};