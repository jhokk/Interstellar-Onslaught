#include "Bullet.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "EventWave.h"
#include "PowerUp.h"

// Create a bullet object
// piercing = the number of targets the bullet can hit before it destroys itself (default 1)
Bullet::Bullet(df::Vector start_pos, int piercing, std::string name, std::string sprite) {

	setType(name);
	
	if (setSprite(sprite) == -1) {
		printf("Bullet sprite failed to load! \n");
	}

	df::Vector p(start_pos.getX() + 1.5f, start_pos.getY() - 0.5f);
	setPosition(p);

	if (strcmp(name.c_str(), "Bullet") != 0) {
		setVelocity(df::Vector(0, 0.39f));
	}
	else {
		setVelocity(df::Vector(0, -0.45f));
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

	// This is a bullet from the hero
	if (strcmp(getType().c_str(), "Bullet") == 0) {

		// Hit an enemy
		if (p_collision_event->getObject1()->getType() == "Enemy" || 
			p_collision_event->getObject2()->getType() == "Enemy") {

			// Play sound
			df::Sound* f_sound = RM.getSound("explode");
			if (f_sound)
				f_sound->play();

			if (getPierce() <= 1) {
				WM.markForDelete(p_collision_event->getObject1());
				WM.markForDelete(p_collision_event->getObject2());
			}
			else {
				setPierce(getPierce() - 1);
				if (p_collision_event->getObject1()->getType() == "Enemy")
					WM.markForDelete(p_collision_event->getObject1());
				else
					WM.markForDelete(p_collision_event->getObject2());
			}

			// 10% chance to create powerup
			if ((rand() % 10) == 0)
				new PowerUp(getPosition());
		}
	}
	// This is an enemy bullet
	else if (strcmp(getType().c_str(), "EnemyBullet") == 0) {
		if (p_collision_event->getObject1()->getType() == "Hero" || 
			p_collision_event->getObject2()->getType() == "Hero" || 
			p_collision_event->getObject1()->getType() == "Bullet" ||
			p_collision_event->getObject2()->getType() == "Bullet") {
			WM.markForDelete(p_collision_event->getObject1());
			WM.markForDelete(p_collision_event->getObject2());
		}
	}
}

void Bullet::setPierce(int new_pierce) {
	pierce = new_pierce;
}

int Bullet::getPierce() const {
	return pierce;
}