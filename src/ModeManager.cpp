#include "ModeManager.h"

ModeManager::ModeManager() { }

ModeManager::~ModeManager() { }

void ModeManager::setMode(std::unique_ptr<Mode> newMode) {
	if (currentMode) {
		currentMode->exit(); // Call exit on the current mode before switching
	}

	currentMode = std::move(newMode);
	currentMode->setup();
}


void ModeManager::update() {
	if (currentMode) {
		currentMode->update();
	}
}

void ModeManager::draw() {
	if (currentMode) {
		currentMode->draw();
	}
}

void ModeManager::keyPressed(int key) {
	if (currentMode) {
		currentMode->keyPressed(key);
	}
}