// Engine includes.
#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "ViewObject.h"
#include "EventView.h"

// Game includes.
#include "GameStart.h"
#include "Hero.h"
#include "Music.h"
#include "Points.h"
#include "Enemy.h"
#include "EventWave.h"

GameStart::GameStart() {
    setType("GameStart");

    // Link to "message" sprite.
    setSprite("gamestart");

    // Put in center of screen.
    setLocation(df::CENTER_CENTER);

    // Register for "keyboard" event.
    registerInterest(df::KEYBOARD_EVENT);
    registerInterest(WAVE_EVENT);

    // Play start music.
    p_music = RM.getMusic("start music");
    playMusic();
}

// Play start music.
void GameStart::playMusic() {
    if (p_music)
        p_music->play();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P: 			// play
            start();
            break;
        case df::Keyboard::Q:			// quit
            GM.setGameOver();
            break;
        default:
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

void GameStart::start() {

    new Hero;

    new Points;

    // Pause start music.
    p_music->pause();

    // When game starts, become inactive.
    setActive(false);
}

// Override default draw so as not to display "value".
int GameStart::draw() {
    return df::Object::draw();
}

void GameStart::reactivate() {
    setActive(true);
    playMusic();
}