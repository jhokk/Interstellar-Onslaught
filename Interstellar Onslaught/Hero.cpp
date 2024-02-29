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
#include "GameOver.h"
#include "Enemy.h"
#include "EventWave.h"
#include "Boss.h"


	Hero::Hero() {

		setType("Hero");
		if (setSprite("hero") != 0) {
			std::cout << "Hero Sprite load failed! \n";
		}
		
		// set starting location
		//df::Vector p((float)DM.getHorizontal()/2, (float)DM.getVertical()-2);
		//setPosition(p);

		setAltitude(2);

		setSolidness(df::HARD);

		registerInterest(df::KEYBOARD_EVENT);
		registerInterest(df::MSE_EVENT);
		registerInterest(df::STEP_EVENT);
		registerInterest(WAVE_EVENT);

		move_slowdown = 3;
		//move_countdown = move_slowdown;

		fire_slowdown = 20;
		//fire_countdown = fire_slowdown;

		//power = PowerUpType::NONE;
		//power_timer = 0;

		p_power_vo = new df::ViewObject;
		p_power_vo->setLocation(df::CENTER_RIGHT);
		p_power_vo->setDrawValue(0);
		p_power_vo->setBorder(0);
		//p_power_vo->setActive(0);

		p_music = RM.getMusic("game music");
		if (p_music)
			p_music->play();

		wave_num = 0;
		newWave();
	}

	Hero::~Hero() {

		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);

		p_power_vo->setActive(false);
		p_music->stop();

		new GameOver();
	}

	int Hero::eventHandler(const df::Event* p_e) {

		if (p_e->getType() == df::KEYBOARD_EVENT) {
			const df::EventKeyboard* p_keyboard_event =
				dynamic_cast <const df::EventKeyboard*> (p_e);
			//printf("keyboard event found!\n");
			kbd(p_keyboard_event);
			return 1;
		}
		if (p_e->getType() == df::COLLISION_EVENT) {
			const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
			hit(p_collision_event);
			//printf("Hero collided! \n");
			return 1;
		}
		if (p_e->getType() == df::OUT_EVENT) {
			//printf("Hero is out of bounds! \n");
			return 1;
		}
		if (p_e->getType() == df::MSE_EVENT) {
			const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
			if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
				(p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
				//fire(this->getPosition());
				fire();
			}
			return 1;
		}
		if (p_e->getType() == df::STEP_EVENT) {
			//printf("step event received!");
			step();
			return 1;
		}
		if (p_e->getType() == WAVE_EVENT) {
			//printf("wave event received!");
			//newWave();
			new_wave_wait = 5 + 40 * (wave_num % 4 == 0);
			return 1;
		}
		else {
			//printf("event not handled: %s", p_e->getType().c_str());
		}
		return 0;
	}

	void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
		//printf("key: %d\n", p_keyboard_event->getKey());
		switch (p_keyboard_event->getKey()) {
		case df::Keyboard::A:     // left
			if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
				move(-1);
			}
			break;
		case df::Keyboard::D:       // right
			if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN) {
				move(+1);
			}
			break;
		case df::Keyboard::SPACE:
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
				//RM.getSound("weapon swap")->play();
			}
			break;
		case df::Keyboard::Q:
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
				// game over!
				WM.markForDelete(this);
			}
			break;
		default: // Key not handled.
			//printf("key not handled: %i \n", p_keyboard_event->getKey());
			return;
		};

		return;
	}

	// Move left or right
	void Hero::move(float dx) {

		// See if time to move.
		if (move_countdown == 0) {

			// If stays on window, allow move.
			df::Vector new_pos(getPosition().getX() + dx, getPosition().getY());

			if ((new_pos.getX() > 2) &&
				(new_pos.getX() < DM.getHorizontal() - 3)) {
				WM.moveObject(this, new_pos);
			}
			move_countdown = move_slowdown;
		}
	}

	void Hero::fire() {

		if (fire_countdown == 0 || 
			(fire_countdown <= 10 && power == PowerUpType::RAPID)) {

			int pierce = 1 + (power == PowerUpType::PIERCE);
			new Bullet(df::Vector(getPosition().getX() - 1.5f, getPosition().getY() - 2), pierce, "Bullet", "bullet");
			if (power == PowerUpType::SPREAD) {
				new Bullet(df::Vector(getPosition().getX() + 1, getPosition().getY() - 2), pierce, "Bullet", "bullet");
				new Bullet(df::Vector(getPosition().getX() - 4, getPosition().getY() - 2), pierce, "Bullet", "bullet");
			}

			// Play "fire" sound.
			df::Sound* f_sound = RM.getSound("fire");
			if (f_sound)
				f_sound->play();

			fire_countdown = fire_slowdown;
		}
	}

	void Hero::step() {
		//printf("move_countdown: %d\n", move_countdown);
		// Move countdown.
		move_countdown--;
		if (move_countdown < 0)
			move_countdown = 0;

		// Fire countdown.
		fire_countdown--;
		if (fire_countdown < 0)
			fire_countdown = 0;

		power_timer--;
		if (power_timer < 0) {
			power_timer = 0;
			power = PowerUpType::NONE;
			p_power_vo->setActive(0);
		}
		
		// Powerup ViewObject flashes cyan/magenta
		if (power_timer % 10 == 0) {
			if (p_power_vo->getColor() == df::CYAN)
				p_power_vo->setColor(df::MAGENTA);
			else
				p_power_vo->setColor(df::CYAN);
		}

		if (new_wave_wait == 0)
			newWave();
		else if (new_wave_wait > 0)
			new_wave_wait--;
	}
	
	void Hero::hit(const df::EventCollision* p_collision_event) {
		if ((p_collision_event->getObject1()->getType() == "PowerUp") ||
			(p_collision_event->getObject2()->getType() == "PowerUp")) {
			power = (PowerUpType)(rand() % 3);
			power_timer = POWER_DURATION;
 
			p_power_vo->setActive(1);
			p_power_vo->setColor(df::YELLOW);
			DM.shake(1, 1, POWER_DURATION);
			if (power == PowerUpType::SPREAD) {
				p_power_vo->setViewString("Wide Shots!!");
			}
			else if (power == PowerUpType::RAPID) {
				p_power_vo->setViewString("Rapid Shots!!");
			}
			else if (power == PowerUpType::PIERCE) {
				p_power_vo->setViewString("Piercing Shots!!");
			}

			df::Sound* f_sound = RM.getSound("powerup");
			if (f_sound)
				f_sound->play();
		}
	}

	void Hero::newWave() {

		// clear enemies, bullets, and powerups
		df::ObjectList object_list = WM.getAllObjects(true);
		df::ObjectListIterator i(&object_list);
		for (i.first(); !i.isDone(); i.next()) {
			df::Object* p_o = i.currentObject();
			if (p_o->getType() == "Enemy" || p_o->getType() == "Bullet" ||
				p_o->getType() == "EnemyBullet" || p_o->getType() == "PowerUp")
				WM.markForDelete(p_o);
		}

		setPosition(df::Vector((float)DM.getHorizontal() / 2, (float)DM.getVertical() - 2));
		wave_num++;

		move_countdown = move_slowdown;
		fire_countdown = fire_slowdown;
		power = PowerUpType::NONE;
		power_timer = 0;
		p_power_vo->setActive(0);
		new_wave_wait = -1;

		if (wave_num % 4 == 0) {
			p_music->pause();
			new Boss;
		}
		else {
			p_music->play();
			for (int i = 0; i < 18; i++)
				new Enemy(wave_num, 0);
			for (int i = 0; i < 18; i++)
				new Enemy(wave_num, 1);
		}

		df::Sound* f_sound = RM.getSound("new wave");
		if (f_sound)
			f_sound->play();
	}