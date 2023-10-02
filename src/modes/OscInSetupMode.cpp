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
	oscInPortField.bounds.y = 35;
    oscInPortField.bounds.height = font.getStringBoundingBox("1", 0, 0).height + 5;
	oscInPortField.bounds.width = font.getStringBoundingBox(ofToString(settings["incomingPortOsc"]), 0, 0).width + 30;
	oscInPortField.setFont(font);

	saveOSCInPortSettings.setup("Set OSC in port", "BTN_MSG_OSC_IN_PORT_SET");
	saveOSCInPortSettings.set(30, 175, 140, 20);
	saveOSCInPortSettings.disableAllEvents();

	GoToConversionMode.setup("Exit settings", "BTN_MSG_GOTOMODE_MODE_CONVERSION");
	GoToConversionMode.set(200, 175, 140, 20);
	GoToConversionMode.disableAllEvents();
}

OscInSetupMode::~OscInSetupMode() {}

void OscInSetupMode::setup() {
	oscInPortField.enable();
	saveOSCInPortSettings.enableAllEvents();
	GoToConversionMode.enableAllEvents();
	ofAddListener(oscInPortField.onTextChange, this, &OscInSetupMode::onOSCInputPortEditied);

	ofAddListener(ofEvents().keyPressed, this, &OscInSetupMode::_keyPressed);
}

void OscInSetupMode::draw() {
	font.drawString("OSC in settings", 10, 15);
	ofSetColor(0);
    ofNoFill();
    ofDrawRectRounded(oscInPortField.bounds.x, oscInPortField.bounds.y + 8, oscInPortField.bounds.width, oscInPortField.bounds.height, 3);
	oscInPortField.draw();
}

void OscInSetupMode::update() {
    // Implementation
}

void OscInSetupMode::exit() {
	oscInPortField.disable();
	saveOSCInPortSettings.disableAllEvents();
	GoToConversionMode.disableAllEvents();
	ofRemoveListener(oscInPortField.onTextChange, this, &OscInSetupMode::onOSCInputPortEditied);
	ofRemoveListener(ofEvents().keyPressed, this, &OscInSetupMode::_keyPressed);
}


void OscInSetupMode::_keyPressed(ofKeyEventArgs & e) {

}

void OscInSetupMode::onOSCInputPortEditied(string & message) {
    settings["incomingPortOsc"] = ofToInt(message);

}
