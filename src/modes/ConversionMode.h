
//
//  ConversionMode.hpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//
#pragma once

#include "modes/Mode.h"
#include <stdio.h>

class ConversionMode : public Mode {
private:
	std::string title;

public:
	ConversionMode(ofTrueTypeFont & fontRef, ofJson & settingsRef);
	~ConversionMode();

	void setup() override;
	void draw() override;
	void update() override;
	void exit() override;
	void keyPressed(int key) override{ }

	void _keyPressed(ofKeyEventArgs & e);

	simpleButton goToMidiOutSetMode;
	simpleButton goToMidiInSetMode;
	simpleButton gotToOSCOutSetMode;
	simpleButton goToOSCInSetMode;
	
};
