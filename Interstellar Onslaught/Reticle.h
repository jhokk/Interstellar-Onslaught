#include "Object.h"

#define RETICLE_CHAR '+'

namespace df {
    class Reticle : public Object {

    public:
        Reticle();
        int draw(void) override;
        int eventHandler(const df::Event* p_e) override;
    };
}