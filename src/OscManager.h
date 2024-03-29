//
//  OSCManager.h
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
    
    void setup();
    void closeReceiver();
    void setupReceiver();
    void closeSender();
    void setupSender();
    
    ofxOscSender& getOSCSender() { return oscSender; }
    ofxOscReceiver& getOscReciever() { return oscReceiver; }
    
    void handleIncomingMessages();
  
    //public destructor
	~OscManager();
    void updateSettings();

private:
    OscManager(); // Constructor is private now

    ofJson oscManagerSettings;
    string message;
    ofxOscSender oscSender;
    ofxOscReceiver oscReceiver;
};
