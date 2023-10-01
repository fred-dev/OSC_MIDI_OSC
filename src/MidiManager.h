//
//  MidiManager.hpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//


#pragma once
#include <stdio.h>

#include "ofMain.h"
#include "ofxMidi.h"
#include "SettingsManager.h" // Include the SettingsManager header
#include "MSCConstants.h"


class MidiManager: public ofxMidiListener {
public:
    static MidiManager& getInstance() {
        static MidiManager instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    // Delete copy constructor and assignment operator
    MidiManager(MidiManager const&) = delete;
    void operator=(MidiManager const&) = delete;

    ofxMidiOut& getMidiOut() { return midiOut; }
    ofxMidiIn& getMidiIn() { return midiIn; }
    
    // Send MIDI message
    void newMidiMessage(ofxMidiMessage& msg);


private:
    MidiManager();
    ofxMidiOut midiOut;
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;

    string message;
    stringstream text;
    // Additional private members for MIDI management
    
    string getMidiShowControlCommandType(uint8_t byte);
    string getMidiShowControTargetType(uint8_t byte);
    uint8_t getDeviceIdByte(ofxMidiMessage midiMessage);
    int getMidiShowControldeviceId(uint8_t byte);
    std::vector<int> getMidiShowControlCommandData(ofxMidiMessage midiMessage);
    
    vector<unsigned char> sysexMMCMsg;
    void buildSysExMMCMessage(char ID);

};

