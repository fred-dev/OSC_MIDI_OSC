//
//  OSCManager.hpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"
#include "MidiManager.h"
#include "SettingsManager.h" // Include the SettingsManager header

class OscManager {
public:
    static OscManager& getInstance() {
        static OscManager instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    // Delete copy and move constructors and assignment operators
    OscManager(OscManager const&) = delete;
    OscManager(OscManager&&) = delete;
    void operator=(OscManager const&) = delete;
    void operator=(OscManager&&) = delete;

    // Public methods to send and receive OSC messages
    void sendOscMessage(/* parameters */);
    // ... other public methods ...

private:
    OscManager(); // Constructor is private now

    void handleIncomingMessages();

    ofxOscSender oscSender;
    ofxOscReceiver oscReceiver;
};
