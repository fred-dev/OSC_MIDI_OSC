//
//  MidiInSetupMode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "OscOutSetupMode.h"

OscOutSetupMode::OscOutSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef)
	: Mode(fontRef, settingsRef) {
	oscOutPortField.setup();
	oscOutPortField.text = ofToString(settings["outGoingPortOsc"]);
	oscOutPortField.bounds.x = 10;
	oscOutPortField.bounds.y = 30;
	oscOutPortField.bounds.height = 15;
	oscOutPortField.bounds.width = 188;
	oscOutPortField.setFont(font);

	oscOutIPField.setup();
	oscOutIPField.text = settings["outgoingIpOSC"];
	oscOutIPField.bounds.x = 10;
	oscOutIPField.bounds.y = 45;
	oscOutIPField.bounds.height = 15;
	oscOutIPField.bounds.width = 188;
	oscOutIPField.setFont(font);

	saveOSCOutPortSettings.setup("Save OSC in port settings", "BTN_MSG_OSC_IN_PORT_SET");
	saveOSCOutPortSettings.set(200, 200, 200, 20);
	saveOSCOutPortSettings.disableAllEvents();

	saveOSCOutIptSettings.setup("Save OSC in port settings", "BTN_MSG_OSC_IN_PORT_SET");
	saveOSCOutIptSettings.set(200, 200, 200, 20);
	saveOSCOutIptSettings.disableAllEvents();

	GoToConversionMode.setup("Conversion mode", "BTN_MSG_GOTOMODE_MODE_CONVERSION");
	GoToConversionMode.set(200, 200, 200, 20);
	GoToConversionMode.disableAllEvents();
}

OscOutSetupMode::~OscOutSetupMode() { }

void OscOutSetupMode::setup() {
	oscOutPortField.enable();
	oscOutIPField.enable();
	saveOSCOutPortSettings.enableAllEvents();
	saveOSCOutIptSettings.enableAllEvents();
	GoToConversionMode.enableAllEvents();
	ofAddListener(oscOutPortField.onTextChange, this, &OscOutSetupMode::onOSCOutputPortEditied);
	ofAddListener(oscOutIPField.onTextChange, this, &OscOutSetupMode::onOSCOutputIPEditied);
	ofAddListener(ofEvents().keyPressed, this, &OscOutSetupMode::_keyPressed);
}

void OscOutSetupMode::draw() {
	font.drawString("OSC out settings", 10, 15);
	ofSetColor(0);
	ofRectangle(oscOutPortField.bounds);
	ofNoFill();
	oscOutPortField.draw();
	ofRectangle(oscOutIPField.bounds);
	ofNoFill();
	oscOutIPField.draw();
}

void OscOutSetupMode::update() {
	// Implementation
}

void OscOutSetupMode::exit() {
	oscOutPortField.disable();
	oscOutIPField.enable();
	saveOSCOutPortSettings.disableAllEvents();
	saveOSCOutIptSettings.disableAllEvents();
	ofRemoveListener(oscOutPortField.onTextChange, this, &OscOutSetupMode::onOSCOutputPortEditied);
	ofRemoveListener(oscOutIPField.onTextChange, this, &OscOutSetupMode::onOSCOutputIPEditied);
}


void OscOutSetupMode::_keyPressed(ofKeyEventArgs & e) {
	int key = e.key;
	ofLogVerbose("OscOutSetupMode") << "keyPressed: " << key;
}

void OscOutSetupMode::onOSCOutputIPEditied(string& message) {

}

void OscOutSetupMode::onOSCOutputPortEditied(string& message) {

}