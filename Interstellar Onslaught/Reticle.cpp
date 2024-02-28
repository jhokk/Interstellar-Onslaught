#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "Reticle.h"

namespace df {
    Reticle::Reticle() {


        setType("Reticle");

        setSolidness(SPECTRAL);     // CHANGE BACK TO SPECTRAL

        setAltitude(WM.MAX_ALTITUDE);

        //registerInterest(MSE_EVENT);

        
    }


    int Reticle::eventHandler(const Event* p_e) {

        if (p_e->getType() == MSE_EVENT) {
            const EventMouse* p_mouse_event =
                dynamic_cast <const EventMouse*> (p_e);
            if (p_mouse_event->getMouseAction() == MOVED) {
                // Change location to new mouse position.
                
                setPosition(DM.pixelsToSpaces(p_mouse_event->getMousePosition()));
                return 1;
            }
        }

        // If get here, have ignored this event.
        return 0;
    }

    // Draw reticle on window.
    int Reticle::draw() {
        return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
    }

}