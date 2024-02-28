// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"


int main(int argc, char* argv[]) {

    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    df::splash();

    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/enemy-spr.txt", "enemy");
    RM.loadSprite("sprites/hero-spr.txt", "hero");
    RM.loadSprite("sprites/powerup-spr.txt", "powerup");
    RM.loadSprite("sprites/newShip-spr.txt", "newShip");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");

    GM.run();

    GM.shutDown();

    return 0;
}