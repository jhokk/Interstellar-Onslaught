#include "ViewObject.h"
#include "Event.h"

namespace df {

	class Points : public ViewObject {

	public:
		Points();
		int eventHandler(const Event* p_e) override;
	};
}