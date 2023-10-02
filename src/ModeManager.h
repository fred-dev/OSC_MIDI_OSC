#pragma once
#include "Mode.h"
#include <memory>

class ModeManager {
private:
	std::unique_ptr<Mode> currentMode;

public:
	ModeManager();
	~ModeManager();

	void setMode(std::unique_ptr<Mode> newMode);
	void update();
	void draw();
	void keyPressed(int key);
};
