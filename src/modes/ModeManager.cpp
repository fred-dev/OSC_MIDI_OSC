
//
//  ModeManager.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "ModeManager.h"

ModeManager::ModeManager() {
	// Constructor implementation (if needed)
}

ModeManager::~ModeManager() {
	// Destructor implementation (if needed)
}

void ModeManager::setMode(std::shared_ptr<Mode> newMode) {
	if (currentMode) {
		currentMode->exit();
	}

	currentMode = newMode;
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

void ModeManager::exit() {
	if (currentMode) {
		currentMode->exit();
	}
}
