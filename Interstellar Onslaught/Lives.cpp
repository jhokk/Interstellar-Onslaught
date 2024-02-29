#include "EventStep.h"
#include "Lives.h"
#include "GameManager.h"

Lives::Lives() {
    setLocation(df::TOP_LEFT);
    setViewString("Lives");
    setColor(df::YELLOW);
    setValue(0);
}

int Lives::eventHandler(const df::Event* p_e) {

    if (df::ViewObject::eventHandler(p_e)) {
        if (getValue() <= 0)
            GM.setGameOver();
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}