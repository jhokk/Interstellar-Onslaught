#include "EventStep.h"
#include "Points.h"
#include "Vector.h"

Points::Points() {
    setLocation(df::TOP_LEFT);
    setViewString("Points");
    setColor(df::YELLOW);
}

int Points::eventHandler(const df::Event* p_e) {

    if (df::ViewObject::eventHandler(p_e)) {
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}