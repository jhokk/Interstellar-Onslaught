#include "Bullet.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "EventWave.h"

// Create a bullet object
// piercing = the number of targets the bullet can hit before it destroys itself (default 1)
Bullet::Bullet(df::Vector start_pos, int piercing, std::string name, std::string sprite) {

	setType(name);
	
	if (setSprite(sprite) == -1) {
		printf("Bullet sprite failed to load! \n");
	}

	df::Vector p(start_pos.getX() + 1.5f, start_pos.getY() - 0.5f);
	setPosition(p);

	//setSpeed(1);

	if (strcmp(name.c_str(), "Bullet") != 0) {
		setVelocity(df::Vector(0, 0.39f));
	}
	else {
		setVelocity(df::Vector(0, -0.5f));
	}

	setSolidness(df::SOFT);

	setPierce(piercing);
}

/*
Bullet::Bullet(df::Vector start_pos, int piercing) {

	setType("Bullet");
	setSprite("bullet");

	df::Vector p(start_pos.getX() + 1.5f, start_pos.getY() - 0.5f);
	setPosition(p);

	//setSpeed(1);
	setVelocity(df::Vector(0, -0.5f));

	setSolidness(df::SOFT);

	registerInterest(WAVE_EVENT);

	setPierce(piercing);
}
*/

void Bullet::out() {
	//printf("bullet out of bounds, getting deleted");
	WM.markForDelete(this);
}

int Bullet::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == WAVE_EVENT) {
		WM.markForDelete(this);
		return 1;
	}
	return 0;
}

void Bullet::hit(const df::EventCollision* p_collision_event) {
	if (strcmp(getType().c_str(), "Bullet") == 0) {
		if (p_collision_event->getObject1()->getType() == "Enemy") {
			WM.markForDelete(p_collision_event->getObject1());
			setPierce(getPierce() - 1);
			if (getPierce() == 0)
				WM.markForDelete(this);
		}
		else if (p_collision_event->getObject2()->getType() == "Enemy") {
			WM.markForDelete(p_collision_event->getObject2());
			setPierce(getPierce() - 1);
			if (getPierce() == 0)
				WM.markForDelete(this);
		}
	}
	else if (strcmp(getType().c_str(), "EnemyBullet") == 0) {
		if (p_collision_event->getObject1()->getType() == "Hero") {
			WM.markForDelete(p_collision_event->getObject1());
			setPierce(getPierce() - 1);
			if (getPierce() == 0)
				WM.markForDelete(this);
		}
		else if (p_collision_event->getObject2()->getType() == "Hero") {
			WM.markForDelete(p_collision_event->getObject2());
			setPierce(getPierce() - 1);
			if (getPierce() <= 0)
				WM.markForDelete(this);
		}
	}
}

void Bullet::setPierce(int new_pierce) {
	pierce = new_pierce;
}

int Bullet::getPierce() const {
	return pierce;
}