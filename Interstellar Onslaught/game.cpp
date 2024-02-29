// Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes
#include "GameStart.h"

void loadResources(void);

int main(int argc, char* argv[]) {

    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    df::splash();


    loadResources();
    
    new GameStart();

    GM.run();

    GM.shutDown();

    return 0;
}

void loadResources(void) {
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/enemy-bullet-spr.txt", "enemy bullet");
    RM.loadSprite("sprites/enemy-spr.txt", "enemy");
    RM.loadSprite("sprites/enemy1-spr.txt", "enemy1");
    RM.loadSprite("sprites/hero-spr.txt", "hero");
    RM.loadSprite("sprites/powerup-spr.txt", "powerup");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSprite("sprites/boss-spr.txt", "boss");
    RM.loadSprite("sprites/boss-bullet-spr.txt", "boss bullet");

    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/enemy-fire.wav", "enemy fire");
    RM.loadMusic("sounds/start-music.wav", "start music");
    RM.loadMusic("sounds/game-music.wav", "game music");
    RM.loadMusic("sounds/boss-music.wav", "boss music");
    RM.loadSound("sounds/game-over-new.wav", "game over");
    RM.loadSound("sounds/powerup.wav", "powerup");
    RM.loadSound("sounds/explosion.wav", "explode");
    RM.loadSound("sounds/new-wave.wav", "new wave");
    RM.loadSound("sounds/boss-explode.wav", "boss explode");
}