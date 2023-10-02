
//
//  ConversionMode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "ConversionMode.h"

ConversionMode::ConversionMode(ofTrueTypeFont & fontRef, ofJson & settingsRef)
	: Mode(fontRef, settingsRef) {
	goToMidiOutSetMode.setup("Midi out setup", "BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_OUT");
	goToMidiOutSetMode.set(200, 200, 200, 20);
	goToMidiOutSetMode.disableAllEvents();

	goToMidiInSetMode.setup("Midi in setup", "BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_IN");
	goToMidiInSetMode.set(200, 200, 200, 20);
	goToMidiInSetMode.disableAllEvents();

	gotToOSCOutSetMode.setup("OSC out setup", "BTN_MSG_GOTOMODE_MODE_SETTING_OSC_OUT");
	gotToOSCOutSetMode.set(200, 200, 200, 20);
	gotToOSCOutSetMode.disableAllEvents();

	goToOSCInSetMode.setup("OSC in setup", "BTN_MSG_GOTOMODE_MODE_SETTING_OSC_IN");
	goToOSCInSetMode.set(200, 200, 200, 20);
	goToOSCInSetMode.disableAllEvents();
	ofLogVerbose("ConversionMode::ConversionMode");
}

ConversionMode::~ConversionMode() { }

void ConversionMode::setup() {
	ofLogVerbose("ConversionMode::setup");

	goToMidiOutSetMode.enableAllEvents();
	goToMidiInSetMode.enableAllEvents();
	gotToOSCOutSetMode.enableAllEvents();
	goToOSCInSetMode.enableAllEvents();

	ofAddListener(ofEvents().keyPressed, this, &ConversionMode::_keyPressed);
}

void ConversionMode::draw() {
	ofSetColor(0);
	font.drawString("Midi input on port " + settings["inPortLabel"].get<string>(), 10, 30);
	font.drawString("Midi output on port " + settings["outPortLabel"].get<string>(), 10, 45);
	font.drawString("Osc input on port " + ofToString(settings["incomingPortOsc"]), 10, 60);
	font.drawString("Osc output on port " + ofToString(settings["outGoingPortOsc"]), 10, 75);
	font.drawString("Osc output to host " + ofToString(settings["outgoingIpOSC"]), 10, 90);
}

void ConversionMode::update() {
	//     oscManager.handleIncomingMessages();

}

void ConversionMode::exit() {
	goToMidiOutSetMode.disableAllEvents();
	goToMidiInSetMode.disableAllEvents();
	gotToOSCOutSetMode.disableAllEvents();
	goToOSCInSetMode.disableAllEvents();
	ofRemoveListener(ofEvents().keyPressed, this, &ConversionMode::_keyPressed);
}


void ConversionMode::_keyPressed(ofKeyEventArgs & e) {
	int key = e.key;
	ofLogVerbose("ConversionMode::keyPressed");
	keyPressed(key);
}