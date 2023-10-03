//
//  MidiInSetupMode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "MidiInSetupMode.h"


MidiInSetupMode::MidiInSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef, Colours & coloursRef)
    : Mode(fontRef, settingsRef, coloursRef) {
	saveMidiInPortSettings.setup("Set midi in port", "BTN_MSG_MIDI_IN_PORT_SET");
	saveMidiInPortSettings.set(30, 175, 140, 20);
	saveMidiInPortSettings.disableAllEvents();

	saveMidiInChannelSettings.setup("Set midi in channel", "BTN_MSG_MIDI_IN_CHANNEL_SET");
	saveMidiInChannelSettings.set(200, 175, 140, 20);
	saveMidiInChannelSettings.disableAllEvents();
        
    GoToConversionMode.setup("Exit settings", "BTN_MSG_GOTOMODE_MODE_CONVERSION");
    GoToConversionMode.set(370, 175, 135, 20);
    GoToConversionMode.disableAllEvents();
}

MidiInSetupMode::~MidiInSetupMode() {}

void MidiInSetupMode::setup() {

	saveMidiInPortSettings.enableAllEvents();
	saveMidiInChannelSettings.enableAllEvents();
    GoToConversionMode.enableAllEvents();
	ofAddListener(ofEvents().keyPressed, this, &MidiInSetupMode::_keyPressed);
}

void MidiInSetupMode::draw() {
    ofSetColor(colours.text);

	font.drawString(title, 10, 15);
    font.drawString("Use the up & down keys to set the port and the < and > to set the channel", 10, 35);

	// Draw the list of ports and highlight the selected one
	for (int i = 0; i < settings["allInPorts"].size(); i++) {
		ofPushStyle();

		if (settings["allInPorts"][i] == settings["inPortLabel"]) {
            ofSetColor(colours.buttonActive);
		} else {
            ofSetColor(colours.text);
		}

		font.drawString(settings["allInPorts"][i], 10, 55 + (i * 20));
		ofPopStyle();
	}

	// Draw the midi channel to the right of these messages
    ofSetColor(colours.text);
    font.drawString("Midi channel set to: ", 320, 55);
    ofSetColor(colours.buttonActive);
    int xPos = font.getStringBoundingBox("Midi channel set to: ", 320, 55).x + font.getStringBoundingBox("Midi channel set to: ", 320, 55).width;
    font.drawString( ofToString(settings["midiInChannel"]), xPos, 55);
}

void MidiInSetupMode::update() {
    // Implementation
}

void MidiInSetupMode::exit() {
	saveMidiInPortSettings.disableAllEvents();
	saveMidiInChannelSettings.disableAllEvents();
    GoToConversionMode.disableAllEvents();
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

void MidiInSetupMode::selectChannel(ofJson & channel, int direction) {
	int newChannel = ofClamp(channel.get<int>() + direction, 1, 16);

	channel = newChannel;
}
void MidiInSetupMode::saveMidiInPort(){
    settings["midiInDeviceName"] =  settings["inPortLabel"];
    settings["midiInDevice"] =  settings["inPortLabel"];
    settings["midiInDeviceByString"] =  true;
    

}

void MidiInSetupMode::saveMidiInChannel(){
    settings["midiInChannel"];
}
