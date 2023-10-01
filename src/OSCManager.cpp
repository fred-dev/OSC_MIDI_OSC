//
//  OSCManager.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "OSCManager.h"

OscManager::OscManager() {
    SettingsManager& settingsManager = SettingsManager::getInstance();
    // Access the settings
    ofJson settings = settingsManager.getSettings();
    
    oscSender.setup(settings["outgoingIpOSC"], settings["outGoingPortOsc"]);
    ofLogVerbose() << "OSC Sender initialised and set to port: " << oscSender.getPort() << " With host: " << oscSender.getHost() << endl;
    oscReceiver.setup(settings["incomingPortOsc"]);
    ofLogVerbose() << "OSC Receiver initialised and set to port: " << oscReceiver.getPort() << endl;
}

void OscManager::handleIncomingMessages() {
    MidiManager& midiManager = MidiManager::getInstance();
    ofxMidiOut& midiOut = midiOut;

    while (oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        
        if (m.getAddress() == "/noteOn") {
            if (m.getNumArgs() > 1) {
                midiOut.sendNoteOn(settings["midiOutChannel"], m.getArgAsInt32(0), m.getArgAsInt32(1));
                message = "Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity " + ofToString(m.getArgAsInt32(1));
                ofLogVerbose() << message << endl;
            }
            
            if (m.getNumArgs() == 1) {
                midiOut.sendNoteOn(settings["midiOutChannel"], m.getArgAsInt32(0));
                message = "Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity " + ofToString(64);
                ofLogVerbose() << message << endl;
            }
        }
        
        if (m.getAddress() == "/noteOff") {
            midiOut.sendNoteOff(settings["midiOutChannel"], m.getArgAsInt32(0));
            message = "Sending note off Note ID " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/cc") {
            midiOut.sendControlChange(settings["midiOutChannel"], m.getArgAsInt32(0), m.getArgAsInt32(1));
            message = "Sending cc Controller ID " + ofToString(m.getArgAsInt32(0)) + " Controller value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/ProgramChange") {
            midiOut.sendProgramChange(settings["midiOutChannel"], m.getArgAsInt32(0));
            message = "Sending program change ID: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/PitchBend") {
            midiOut.sendPitchBend(settings["midiOutChannel"], m.getArgAsInt32(0));
            message = "Sending pitch bend value: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/Aftertouch") {
            midiOut.sendAftertouch(settings["midiOutChannel"], m.getArgAsInt32(0));
            message = "Sending aftertouch Value: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/PolyAftertouch") {
            midiOut.sendPolyAftertouch(settings["midiOutChannel"], m.getArgAsInt32(0), m.getArgAsInt32(1));
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/MMCCommand/stop") {
            buildSysExMMCMessage(0x01);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/MMCCommand/play") {
            buildSysExMMCMessage(0x02);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/MMCCommand/forward") {
            buildSysExMMCMessage(0x04);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/MMCCommand/rewind") {
            buildSysExMMCMessage(0x05);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/MMCCommand/punchIn") {
            buildSysExMMCMessage(0x06);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/MMCCommand/punchOut") {
            buildSysExMMCMessage(0x07);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/MMCCommand/recordPause") {
            buildSysExMMCMessage(0x08);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
        
        if (m.getAddress() == "/MMCCommand/pause") {
            buildSysExMMCMessage(0x09);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose() << message << endl;
        }
    }
}
