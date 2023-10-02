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
#include "OscManager.h"
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
    void setup();
    void close();
    ofxMidiOut& getMidiOut() { return midiOut; }
    ofxMidiIn& getMidiIn() { return midiIn; }
    
    // Send MIDI message
    void newMidiMessage(ofxMidiMessage& msg);
    vector<unsigned char> sysexMMCMsg;
    vector<unsigned char> buildMMCMessaage(int deviceID, const std::string& command);

    //public destructor
	~MidiManager();



private:
    MidiManager();
    ofxMidiOut midiOut;
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    
    ofJson midiManagerSettings;
    
    string message;
    stringstream text;
    // Additional private members for MIDI management
    
    std::string getMidiMachineControlCommand(uint8_t byte);

    std::string getMidiShowControlCommandType(uint8_t byte);
    std::string getMidiShowControTargetType(uint8_t byte);
    uint8_t getDeviceIdByte(ofxMidiMessage midiMessage);
    int getMidiShowControldeviceId(uint8_t byte);
    std::vector<int> getMidiShowControlCommandData(ofxMidiMessage midiMessage);
    
    

};

