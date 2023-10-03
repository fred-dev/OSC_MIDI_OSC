
//
//  ConversionMode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "ConversionMode.h"

ConversionMode::ConversionMode(ofTrueTypeFont & fontRef, ofJson & settingsRef, Colours & coloursRef)
    : Mode(fontRef, settingsRef, coloursRef) {
	goToMidiOutSetMode.setup("Midi out setup", "BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_OUT");
	goToMidiOutSetMode.set(30, 175, 140, 20);
	goToMidiOutSetMode.disableAllEvents();

	goToMidiInSetMode.setup("Midi in setup", "BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_IN");
	goToMidiInSetMode.set(200, 175, 140, 20);
	goToMidiInSetMode.disableAllEvents();

	gotToOSCOutSetMode.setup("OSC out setup", "BTN_MSG_GOTOMODE_MODE_SETTING_OSC_OUT");
	gotToOSCOutSetMode.set(370, 175, 140, 20);
	gotToOSCOutSetMode.disableAllEvents();

	goToOSCInSetMode.setup("OSC in setup", "BTN_MSG_GOTOMODE_MODE_SETTING_OSC_IN");
	goToOSCInSetMode.set(540, 175, 140, 20);
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
    ofRegisterGetMessages(this);
}

void ConversionMode::draw() {
    
	ofSetColor(colours.text);
    font.drawString("Conversion active", 10, 15);
    font.drawString(activityMessage, 10, 35);
	font.drawString("Midi input on port " + settings["inPortLabel"].get<string>() + "  Channel: " + ofToString(settings["midiInChannel"]), 10, 55);
	font.drawString("Midi output on port " + settings["outPortLabel"].get<string>() + "  Channel: " + ofToString(settings["midiOutChannel"]), 10, 75);
	font.drawString("Osc input on port " + ofToString(settings["incomingPortOsc"]), 10, 95);
	font.drawString("Osc output on port " + ofToString(settings["outGoingPortOsc"]), 10, 115);
	font.drawString("Osc output to host " + settings["outgoingIpOSC"].get<string>(), 10, 135);
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
    ofUnregisterGetMessages(this);
}


void ConversionMode::_keyPressed(ofKeyEventArgs & e) {
	int key = e.key;
	keyPressed(key);
}

void ConversionMode::gotMessage(ofMessage & msg) {
    ofLogVerbose("ConversionMode::ofGetMessage");
    
    if (msg.message.substr(0, 3) != "BTN") {
        activityMessage = msg.message;
    }
}

