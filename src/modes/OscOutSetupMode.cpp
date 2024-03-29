//
//  OscOutSetupMode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "OscOutSetupMode.h"

OscOutSetupMode::OscOutSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef, Colours & coloursRef)
    : Mode(fontRef, settingsRef, coloursRef) {
	oscOutPortField.setup();
	oscOutPortField.text = ofToString(settings["outGoingPortOsc"]);
	oscOutPortField.bounds.x = 10;
	oscOutPortField.bounds.y = 35;
    oscOutPortField.bounds.height = font.getStringBoundingBox("1", 0, 0).height + 5;
    oscOutPortField.bounds.width = font.getStringBoundingBox(ofToString(settings["outGoingPortOsc"]), 0, 0).width + 30;
	oscOutPortField.setFont(font);

	oscOutIPField.setup();
	oscOutIPField.text = settings["outgoingIpOSC"];
	oscOutIPField.bounds.x = 10;
	oscOutIPField.bounds.y = 60;
	oscOutIPField.bounds.height = font.getStringBoundingBox("1", 0, 0).height + 5;
    oscOutIPField.bounds.width = font.getStringBoundingBox(ofToString(settings["outgoingIpOSC"]), 0, 0).width + 30;;
	oscOutIPField.setFont(font);

	saveOSCOutPortSettings.setup("Set OSC out port", "BTN_MSG_OST_OUT_PORT_SET");
	saveOSCOutPortSettings.set(30, 175, 140, 20);
	saveOSCOutPortSettings.disableAllEvents();

	saveOSCOutIptSettings.setup("Set OSC IP port", "BTN_MSG_OST_OUT_IP_SET");
	saveOSCOutIptSettings.set(200, 175, 140, 20);
	saveOSCOutIptSettings.disableAllEvents();

	GoToConversionMode.setup("Exit settings", "BTN_MSG_GOTOMODE_MODE_CONVERSION");
	GoToConversionMode.set(370, 175, 140, 20);
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
    ofSetColor(colours.text);
    font.drawString("OSC out settings", 10, 15);
    ofPushStyle();
    ofFill();
    ofSetColor(colours.buttonActive);
    ofDrawRectRounded(oscOutPortField.bounds.x, oscOutPortField.bounds.y + 8, oscOutPortField.bounds.width, oscOutPortField.bounds.height, 3);
    ofDrawRectRounded(oscOutIPField.bounds.x, oscOutIPField.bounds.y + 8, oscOutIPField.bounds.width, oscOutIPField.bounds.height, 3);
    ofPopStyle();
    oscOutIPField.draw();
    oscOutPortField.draw();
	
}

void OscOutSetupMode::update() {
	// Implementation
}

void OscOutSetupMode::exit() {
	oscOutPortField.disable();
	oscOutIPField.disable();
	saveOSCOutPortSettings.disableAllEvents();
	saveOSCOutIptSettings.disableAllEvents();
    GoToConversionMode.disableAllEvents();
	ofRemoveListener(oscOutPortField.onTextChange, this, &OscOutSetupMode::onOSCOutputPortEditied);
	ofRemoveListener(oscOutIPField.onTextChange, this, &OscOutSetupMode::onOSCOutputIPEditied);
}


void OscOutSetupMode::_keyPressed(ofKeyEventArgs & e) {
	int key = e.key;
}

void OscOutSetupMode::onOSCOutputIPEditied(string& message) {
    settings["outgoingIpOSC"] = message;
}

void OscOutSetupMode::onOSCOutputPortEditied(string& message) {
    settings["outGoingPortOsc"] = ofToInt(message);
}
