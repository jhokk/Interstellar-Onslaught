// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"


int main(int argc, char* argv[]) {

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    df::splash();

    //RM.loadSprite("sprites/hero-spr.txt", "hero");

    GM.run();

    GM.shutDown();

    return 0;
}