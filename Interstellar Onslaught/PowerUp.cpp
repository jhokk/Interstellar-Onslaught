#include "PowerUp.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "WorldManager.h"
#include "EventWave.h"

#include <stdlib.h>

PowerUp::PowerUp(df::Vector start_pos) {
	setType("PowerUp");
	setSprite("powerup");

	df::Vector p(start_pos.getX(), start_pos.getY() + 0.5f);
	setPosition(p);

	setVelocity(df::Vector(0, 0.1f));

	setSolidness(df::SOFT);

	registerInterest(WAVE_EVENT);
}

int PowerUp::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == WAVE_EVENT) {
		WM.markForDelete(this);
		return 1;
	}
	else {
		//printf("event not handled: %s", p_e->getType().c_str());
	}
	return 0;
}

void PowerUp::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Hero") ||
		(p_collision_event->getObject2()->getType() == "Hero")) {
		WM.markForDelete(this);
	}
}

void PowerUp::out() {
	WM.markForDelete(this);
}