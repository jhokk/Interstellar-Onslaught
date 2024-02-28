#include "Bullet.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventOut.h"

namespace df {


	Bullet::Bullet(Vector start_pos) {

		setType("Bullet");
		setSprite("bullet");

		Vector p(start_pos.getX() + 1.5, start_pos.getY() - .5);
		setPosition(p);

		setSpeed(1);

		setSolidness(SOFT);
	}

	void Bullet::out() {
		printf("bullet out of bounds, getting deleted");
		WM.markForDelete(this);
	}

	int Bullet::eventHandler(const Event* p_e) {

		if (p_e->getType() == OUT_EVENT) {
			out();
			return 1;
		}
		if (p_e->getType() == "Collision") {
			const EventCollision* p_collision_event = dynamic_cast <const EventCollision*> (p_e);
			hit(p_collision_event);
			return 1;
		}
		return 0;
	}

	void Bullet::hit(const EventCollision* p_collision_event) {
		if ((p_collision_event->getObject1()->getType() == "Enemy") ||
			(p_collision_event->getObject2()->getType() == "Enemy")) {
			WM.markForDelete(p_collision_event->getObject1());
			WM.markForDelete(p_collision_event->getObject2());
		}
	}

	

}