
//
//  MidiOutSetupMode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "MidiOutSetupMode.h"

MidiOutSetupMode::MidiOutSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef, Colours & coloursRef)
    : Mode(fontRef, settingsRef, coloursRef) { 
	saveMidiOutPortSettings.setup("Set midi out port", "BTN_MSG_MIDI_OUT_PORT_SET");
	saveMidiOutPortSettings.set(30, 175, 140, 20);
	saveMidiOutPortSettings.disableAllEvents();

	saveMidiOutChannelSettings.setup("Set midi out channel", "BTN_MSG_MIDI_OUT_CHANNEL_SET");
	saveMidiOutChannelSettings.set(200, 175, 140, 20);
	saveMidiOutChannelSettings.disableAllEvents();
        
    GoToConversionMode.setup("Exit settings", "BTN_MSG_GOTOMODE_MODE_CONVERSION");
    GoToConversionMode.set(370, 175, 140, 20);
    GoToConversionMode.disableAllEvents();
}

MidiOutSetupMode::~MidiOutSetupMode() { }

void MidiOutSetupMode::setup() {

	saveMidiOutPortSettings.enableAllEvents();
	saveMidiOutChannelSettings.enableAllEvents();
    GoToConversionMode.enableAllEvents();
	ofAddListener(ofEvents().keyPressed, this, &MidiOutSetupMode::_keyPressed);
}

void MidiOutSetupMode::draw() {
    ofSetColor(colours.text);

	font.drawString(title, 10, 15);
    font.drawString("Use the up & down keys to set the port and the < and > to set the channel", 10, 35);

	// Draw the list of ports and highlight the selected one
	for (int i = 0; i < settings["allOutPorts"].size(); i++) {
		ofPushStyle();

		if (settings["allOutPorts"][i] == settings["outPortLabel"]) {
            ofSetColor(colours.buttonActive);
		} else {
            ofSetColor(colours.text);

		}
        
		font.drawString(settings["allOutPorts"][i], 10, 55 + (i * 15));
		ofPopStyle();
	}

	// Draw the midi channel to the right of these messages
    ofSetColor(colours.text);
    // we want to draw this string font.drawString("Midi channel set to: " + ofToString(settings["midiOutChannel"]), 320, 55) but the ofToString(settings["midiOutChannel"]) part should be a different colour
    font.drawString("Midi channel set to: ", 320, 55);
    ofSetColor(colours.buttonActive);
    int xPos = font.getStringBoundingBox("Midi channel set to: ", 320, 55).x + font.getStringBoundingBox("Midi channel set to: ", 320, 55).width;
    font.drawString( ofToString(settings["midiOutChannel"]), xPos, 55);
    
    
    
    
    
    
	//font.drawString("Midi channel set to: " + ofToString(settings["midiOutChannel"]), 320, 55);
}

void MidiOutSetupMode::update() {
	// Implementation
}

void MidiOutSetupMode::exit() {
	saveMidiOutPortSettings.disableAllEvents();
	saveMidiOutChannelSettings.disableAllEvents();
    GoToConversionMode.disableAllEvents();
	ofRemoveListener(ofEvents().keyPressed, this, &MidiOutSetupMode::_keyPressed);
}

void MidiOutSetupMode::_keyPressed(ofKeyEventArgs & e) {
	int key = e.key;

	if (key == OF_KEY_DOWN) {
		selectPort(settings["allOutPorts"], settings["outPortLabel"], 1);
	}

	if (key == OF_KEY_UP) {
		selectPort(settings["allOutPorts"], settings["outPortLabel"], -1);
	}

	if (key == OF_KEY_LEFT) {
		selectChannel(settings["midiOutChannel"], -1);
	}

	if (key == OF_KEY_RIGHT) {
		selectChannel(settings["midiOutChannel"], 1);
	}
}

void MidiOutSetupMode::selectPort(ofJson & ports, ofJson & currentPort, int direction) {
	for (int i = 0; i < ports.size(); i++) {
		if (ports[i] == currentPort) {
			int newIndex = ofClamp(i + direction, 0, ports.size() - 1);
			currentPort = ports[newIndex];
			break;
		}
	}
}

// Helper function to handle channel selection
void MidiOutSetupMode::selectChannel(ofJson & channel, int direction) {
	int newChannel = ofClamp(channel.get<int>() + direction, 1, 16);

	channel = newChannel;
}
