#include "EventStep.h"
#include "Points.h"
#include "Vector.h"

namespace df {

    Points::Points() {
        setLocation(TOP_LEFT);
        setViewString("Points");
        setColor(df::YELLOW);
        setType("Points");
    }

    int Points::eventHandler(const Event* p_e) {

        if (ViewObject::eventHandler(p_e)) {
            return 1;
        }

        // If get here, have ignored this event.
        return 0;
    }

}