#pragma once
#include <ViewObject.h>

class GameOver : public df::ViewObject {

private:
	void step();
	int draw() override;
	int time_to_live;
	int eventHandler(const df::Event* p_e);


public:
	~GameOver();
	GameOver();


};

