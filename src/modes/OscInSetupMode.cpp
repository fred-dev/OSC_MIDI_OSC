//
//  MidiInSetupMode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "OscInSetupMode.h"

OscInSetupMode::OscInSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef)
	: Mode(fontRef, settingsRef) { 
    oscInPortField.setup();
	oscInPortField.text = ofToString(settings["incomingPortOsc"]);
	oscInPortField.bounds.x = 10;
	oscInPortField.bounds.y = 30;
	oscInPortField.bounds.height = 15;
	oscInPortField.bounds.width = 188;
	oscInPortField.setFont(font);

	ofAddListener(oscInPortField.onTextChange, this, &OscInSetupMode::onOSCInputPortEditied);

	saveOSCInPortSettings.setup("Save OSC in port settings", "BTN_MSG_OSC_IN_PORT_SET");
	saveOSCInPortSettings.set(200, 200, 200, 20);
	saveOSCInPortSettings.disableAllEvents();

	GoToConversionMode.setup("Conversion mode", "BTN_MSG_GOTOMODE_MODE_CONVERSION");
	GoToConversionMode.set(200, 200, 200, 20);
	GoToConversionMode.disableAllEvents();
}

OscInSetupMode::~OscInSetupMode() {}

void OscInSetupMode::setup() {
	oscInPortField.enable();
	saveOSCInPortSettings.enableAllEvents();
	GoToConversionMode.enableAllEvents();
}

void OscInSetupMode::draw() {
	font.drawString("OSC in settings", 10, 15);
	ofSetColor(0);
	ofRectangle(oscInPortField.bounds);
	ofNoFill();
	oscInPortField.draw();
}

void OscInSetupMode::update() {
    // Implementation
}

void OscInSetupMode::exit() {
	oscInPortField.disable();
	saveOSCInPortSettings.disableAllEvents();
	GoToConversionMode.disableAllEvents();
}

void OscInSetupMode::keyPressed(int key) {
    // Implementation
}

void OscInSetupMode::onOSCInputPortEditied(string & message) {
	ofLogNotice() << "onOSCInputPortEditied: " << message;
}