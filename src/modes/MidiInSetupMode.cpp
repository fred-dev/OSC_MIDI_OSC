//
//  MidiInSetupMode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "MidiInSetupMode.h"


MidiInSetupMode::MidiInSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef)
	: Mode(fontRef, settingsRef) { 
	saveMidiInPortSettings.setup("Save midi in port settings", "BTN_MSG_MIDI_IN_PORT_SET");
	saveMidiInPortSettings.set(200, 200, 200, 20);
	saveMidiInPortSettings.disableAllEvents();

	saveMidiInChannelSettings.setup("Save midi in channel settings", "BTN_MSG_MIDI_IN_CHANNEL_SET");
	saveMidiInChannelSettings.set(200, 200, 200, 20);
	saveMidiInChannelSettings.disableAllEvents();
}

MidiInSetupMode::~MidiInSetupMode() {}

void MidiInSetupMode::setup() {

	saveMidiInPortSettings.enableAllEvents();
	saveMidiInChannelSettings.enableAllEvents();
	ofAddListener(ofEvents().keyPressed, this, &MidiInSetupMode::_keyPressed);
}

void MidiInSetupMode::draw() {
	font.drawString(title, 10, 15);

	// Draw the list of ports and highlight the selected one
	for (int i = 0; i < settings["allInPorts"].size(); i++) {
		ofPushStyle();

		if (settings["allInPorts"][i] == settings["inPortLabel"]) {
			ofSetColor(255, 0, 0);
		} else {
			ofSetColor(0);
		}

		font.drawString(settings["allInPorts"][i], 10, 30 + (i * 15));
		ofPopStyle();
	}

	// Draw the midi channel to the right of these messages
	ofSetColor(0);
	font.drawString("Midi channel set to: " + ofToString(settings["midiInChannel"]), 320, 30);
}

void MidiInSetupMode::update() {
    // Implementation
}

void MidiInSetupMode::exit() {
	saveMidiInPortSettings.disableAllEvents();
	saveMidiInChannelSettings.disableAllEvents();
	ofRemoveListener(ofEvents().keyPressed, this, &MidiInSetupMode::_keyPressed);
}

void MidiInSetupMode::_keyPressed(ofKeyEventArgs & e) {
	int key = e.key;

	if (key == OF_KEY_DOWN) {
		selectPort(settings["allInPorts"], settings["inPortLabel"], 1);
	}

	if (key == OF_KEY_UP) {
		selectPort(settings["allInPorts"], settings["inPortLabel"], -1);
	}

	if (key == OF_KEY_LEFT) {
		selectChannel(settings["midiInChannel"], -1);
	}

	if (key == OF_KEY_RIGHT) {
		selectChannel(settings["midiInChannel"], 1);
	}
}

void MidiInSetupMode::selectPort(ofJson & ports, ofJson & currentPort, int direction) {
	for (int i = 0; i < ports.size(); i++) {
		if (ports[i] == currentPort) {
			int newIndex = ofClamp(i + direction, 0, ports.size() - 1);
			currentPort = ports[newIndex];
			break;
		}
	}
}

// Helper function to handle channel selection
void MidiInSetupMode::selectChannel(ofJson & channel, int direction) {
	int newChannel = ofClamp(channel.get<int>() + direction, 1, 16);

	channel = newChannel;
}