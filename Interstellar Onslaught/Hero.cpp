#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "Hero.h"
#include <iostream>
#include "ResourceManager.h"
#include "Bullet.h"


namespace df {
	Hero::Hero() {

	

		setType("Hero");
		if (setSprite("ship") != 0) {
			std::cout << "Hero Sprite load failed! \n";
		}
		

		// set starting location
		Vector p((float)DM.getHorizontal()/2, (float)DM.getVertical()-1);
		//Vector p((float)DM.getHorizontal()/2, (float)DM.getVertical()/2);

		setPosition(p);

		setAltitude(2);

		setSolidness(HARD);

		//setVelocity(Vector(0, 0));
		//setDirection(Vector(0, 1));

		// Create reticle for firing bullets.
		//p_reticle = new Reticle();
		//p_reticle->draw();

		move_slowdown = 2;
		move_countdown = move_slowdown;

		fire_slowdown = 20;
		fire_countdown = fire_slowdown;


	}

	Hero::~Hero() {


	}

	int Hero::eventHandler(const Event* p_e) {

		if (p_e->getType() == KEYBOARD_EVENT) {
			const EventKeyboard* p_keyboard_event =
				dynamic_cast <const EventKeyboard*> (p_e);
			//printf("keyboard event found!");
			kbd(p_keyboard_event);
			return 1;
		}
		if (p_e->getType() == "Collision") {
			printf("Hero collided! \n");
			return 1;
		}
		if (p_e->getType() == OUT_EVENT) {
			printf("Hero is out of bounds! \n");
			return 1;
		}
		if (p_e->getType() == MSE_EVENT) {
			const EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
			if ((p_mouse_event->getMouseAction() == CLICKED) &&
				(p_mouse_event->getMouseButton() == Mouse::LEFT)) {
				fire(this->getPosition());
			}
			return 1;
		}
		if (p_e->getType() == "Step") {
			//printf("step event received!");
			step();
			return 1;
		}
		else {
			//printf("event not handled: %s", p_e->getType().c_str());
		}
		return 0;
	}

	void Hero::kbd(const EventKeyboard* p_keyboard_event) {
		//printf("key: %d", p_keyboard_event->getKey());
		switch (p_keyboard_event->getKey()) {
			///*
		case Keyboard::W:     // up
			if (p_keyboard_event->getKeyboardAction() == 5) {
				move(0, -.7);
			}
			break;
		case Keyboard::S:       // down
			if (p_keyboard_event->getKeyboardAction() == 5) {
				move(0, +.7);
			}
			break;
			//*/
		case Keyboard::A:     // left
			if (p_keyboard_event->getKeyboardAction() == 5) {
				move(-2, 0);
			}
			break;
		case Keyboard::D:       // right
			if (p_keyboard_event->getKeyboardAction() == 5) {
				move(+2, 0);
			}
			break;
		case Keyboard::Space:
			if (p_keyboard_event->getKeyboardAction() == 5) {
				//RM.getSound("weapon swap")->play();
			}
			break;
		default: // Key not handled.
			//printf("key not handled: %i \n", p_keyboard_event->getKey());
			return;
		};

		return;
	}

	// Move up or down.
	void Hero::move(float dx, float dy) {

		// See if time to move.
		if (move_countdown == 0) {

			// If stays on window, allow move.
			Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);

			if ((new_pos.getX() > 0) &&
				(new_pos.getX() < WM.getBoundary().getHorizontal()))
				WM.moveObject(this, new_pos);

			move_countdown = move_slowdown;
		}

	}

	void Hero::fire(Vector target) {

		//printf("Fire at X: %f \n", target.getX());

		if (fire_countdown == 0) {

			Vector v = Vector(target.getX(), target.getY() - 1500);

			v.normalize();

			//printf("target vector: %f, %f \n", v.getX(), v.getY());

			v.scale(0.5);
			Bullet* p = new Bullet(Vector(getPosition().getX() - 2, getPosition().getY() - 2));

			p->setVelocity(v);

			// Play "fire" sound.
			df::Sound* f_sound = RM.getSound("fire");
			if (f_sound)
				f_sound->play();

			fire_countdown = fire_slowdown;
		}
	}


	void Hero::step() {
		// Move countdown.
		move_countdown--;
		if (move_countdown < 0)
			move_countdown = 0;

		// Fire countdown.
		fire_countdown--;
		if (fire_countdown < 0)
			fire_countdown = 0;
	}
	
	
}