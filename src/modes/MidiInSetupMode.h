//
//  MidiInSetupMode.hpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//


#pragma once

#include <stdio.h>
#include "modes/Mode.h"

class MidiInSetupMode : public Mode {
private:
	std::string title;


public:
	MidiInSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef);
	~MidiInSetupMode();

    void setup() override;
	void draw() override;
	void update() override;
	void exit() override;
	void keyPressed(int key)override { }

	void _keyPressed(ofKeyEventArgs & e);
	simpleButton saveMidiInPortSettings;
	simpleButton saveMidiInChannelSettings;
	void selectPort(ofJson & ports, ofJson & currentPort, int direction);
	void selectChannel(ofJson & channel, int direction);
};



