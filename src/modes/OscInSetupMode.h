//
//  OscInSetupMode.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//



#include <stdio.h>

#include "modes/Mode.h"
#include "ofxTextInputField.h" 

class OscInSetupMode : public Mode {
private:
		std::string title;

	public:
		OscInSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef);
		~OscInSetupMode();

		void setup() ;
		void draw() ;
		void update() ;
		void exit() ;
		void keyPressed(int key) ;
		simpleButton saveMidiInPortSettings;
		simpleButton saveMidiInChannelSettings;

		ofxTextInputField oscInPortField;

		void onOSCInputPortEditied(string & message);

		simpleButton saveOSCInPortSettings;
		simpleButton GoToConversionMode;
		
	};
