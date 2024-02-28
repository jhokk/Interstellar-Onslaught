#include "Enemy.h"
#include "EventOut.h"
#include "WorldManager.h"
#include "EventView.h"

#include <stdlib.h>

Enemy::Enemy() {
	setType("Enemy");
	setSprite("enemy");

	setVelocity(df::Vector(0.05f, 0.005f));

	moveToStart();
	setSolidness(df::HARD);
}

Enemy::~Enemy() {

	// Send "view" event with points to ViewObjects.
	// Add 10 points.
	df::EventView ev("Score", 10, true);
	//WM.onEvent(&ev);
}

void Enemy::out() {
	if (getPosition().getY() <= 0) {
		WM.markForDelete(this);
		//lose a life
	}
}

int Enemy::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == "Collision") {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == "Step") {
		//printf("step event received!");
		const df::EventStep* p_step_event = dynamic_cast <df::EventStep const*> (p_e);
		step(p_step_event);
		return 1;
	}

	return 0;
}

void Enemy::hit(const df::EventCollision* p_collision_event) {

	if ((p_collision_event->getObject1()->getType()) == "Bullet") {
		WM.markForDelete(p_collision_event->getObject2());
		printf("enemy hit! \n");
		//lose a life
	}
	else if ((p_collision_event->getObject2()->getType()) == "Bullet") {
		WM.markForDelete(p_collision_event->getObject1());
		//lose a life
		printf("enemy hit! \n");

	}
}

void Enemy::moveToStart() {

	df::Vector temp_pos;

	// Get world boundaries.
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();

	temp_pos.setX(6.0f);
	temp_pos.setY(7.0f);

	// If collision, move right slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		if (temp_pos.getX() + 8 > world_horiz - 6) {
			temp_pos.setX(6.0f);
			temp_pos.setY(temp_pos.getY() - 3);
		}
		else {
			temp_pos.setX(temp_pos.getX() + 8);
		}
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}

void Enemy::step(const df::EventStep* p_step_event) {
	if (p_step_event->getStepCount() % 360 == 180) {
		setVelocity(df::Vector(-1 * getVelocity().getX(), getVelocity().getY()));
	}
}