#pragma once

#include "modes/Mode.h"
#include <memory>

class ModeManager {
public:
	ModeManager();
	~ModeManager();

	void setMode(std::shared_ptr<Mode> newMode);
	void update();
	void draw();
	void keyPressed(int key);
	void exit();

private:
	std::shared_ptr<Mode> currentMode;
};