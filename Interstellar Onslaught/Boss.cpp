#include "Boss.h"
#include "WorldManager.h"
#include "Bullet.h"
#include "EventStep.h"
#include "ResourceManager.h"
#include <utility.h>
#include "EventWave.h"
#include "EventView.h"
#include "DisplayManager.h"

#define PI 3.14159265358979

Boss::Boss() {
	setType("Boss");
	setSprite("boss");

	setVelocity(df::Vector(-0.2f, 0.02f));
	setPosition(df::Vector(WM.getBoundary().getHorizontal() / 2, 6.0f));
	setSolidness(df::HARD);
	target_angle = 0;
	health = 5;

	p_music = RM.getMusic("boss music");
	if (p_music)
		p_music->play();

	registerInterest(df::STEP_EVENT);
}

Boss::~Boss() {
	p_music->stop();

	DM.shake(2, 2, 30);

	df::addParticles(df::SPARKS, getPosition(), 3, df::GREEN);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);

	df::EventView ev("Points", 500, true);
	WM.onEvent(&ev);

	EventWave wave;
	WM.onEvent(&wave);
}

int Boss::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step_event = dynamic_cast <df::EventStep const*> (p_e);
		step(p_step_event);
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
}

void Boss::fire() {
	double radian_angle = target_angle * PI / 180.0;
	df::Vector dir = df::Vector(cos(radian_angle), abs(sin(radian_angle)));
	new Bullet(getPosition(), dir);

	df::Sound* f_sound = RM.getSound("enemy fire");
	if (f_sound)
		f_sound->play();

	target_angle += 30;
}

void Boss::step(const df::EventStep *p_event_step) {
	int s = p_event_step->getStepCount();
	if (s % 15 == 0) {
		fire();
	}

	if (s % 90 == 0) {
		setVelocity(df::Vector(getVelocity().getX() * pow(-1, (s+90) % 180 == 0), getVelocity().getY() * pow(-1, s % 180 == 0)));
	}
}

void Boss::hit(const df::EventCollision* p_collision_event) {
	if (p_collision_event->getObject1()->getType() == "Bullet" ||
		p_collision_event->getObject2()->getType() == "Bullet") {

		health--;
		if (health <= 0) {
			WM.markForDelete(this);
			df::Sound* f_sound = RM.getSound("boss explode");
			if (f_sound)
				f_sound->play();
		}
		else {
			df::Sound* f_sound = RM.getSound("explode");
			if (f_sound)
				f_sound->play();
		}
	}
}