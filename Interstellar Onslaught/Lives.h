#include "ViewObject.h"
#include "Event.h"

class Lives : public df::ViewObject {

public:
	Lives();
	int eventHandler(const df::Event* p_e) override;
};
