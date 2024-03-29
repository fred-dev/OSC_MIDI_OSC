//
//  OscOutSetupMode.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#pragma once

#include <stdio.h>

#include "modes/Mode.h"
#include "ofxTextInputField.h"

class OscOutSetupMode : public Mode {
private:
	std::string title;

public:
	OscOutSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef, Colours & coloursRef);
	~OscOutSetupMode();

	void setup() override;
	void draw() override;
	void update() override;
	void exit() override;
	void keyPressed(int key) override { }

	void _keyPressed(ofKeyEventArgs & e);
	simpleButton saveMidiInPortSettings;
	simpleButton saveMidiInChannelSettings;

	ofxTextInputField oscOutPortField, oscOutIPField;

	void onOSCOutputIPEditied(string & message);
	void onOSCOutputPortEditied(string & message);

	simpleButton saveOSCOutPortSettings;
	simpleButton saveOSCOutIptSettings;
	simpleButton GoToConversionMode;
};
