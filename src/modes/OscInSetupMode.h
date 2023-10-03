//
//  OscInSetupMode.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#pragma once


#include <stdio.h>

#include "modes/Mode.h"
#include "ofxTextInputField.h" 

class OscInSetupMode : public Mode {
private:
		std::string title;

	public:
		OscInSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef, Colours & coloursRef);
		~OscInSetupMode();

		void setup() override;
		void draw() override;
		void update() override;
		void exit() override;
		void keyPressed(int key) override{ }

		void _keyPressed(ofKeyEventArgs & e);
		simpleButton saveMidiInPortSettings;
		simpleButton saveMidiInChannelSettings;

		ofxTextInputField oscInPortField;

		void onOSCInputPortEditied(string & message);

		simpleButton saveOSCInPortSettings;
		simpleButton GoToConversionMode;
		
	};
