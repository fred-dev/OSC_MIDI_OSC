//
//  OSCManager.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "OscManager.h"

OscManager::OscManager() {

}

void OscManager::setup() {
    ofLogVerbose() << "OSC Manager setup" << endl;
	SettingsManager & settingsManager = SettingsManager::getInstance();
	// Access the settings
	oscManagerSettings = settingsManager.getSettings();

	oscSender.setup(oscManagerSettings["outgoingIpOSC"], oscManagerSettings["outGoingPortOsc"]);
	ofLogVerbose() << "OSC Sender initialised and set to port: " << oscSender.getPort() << " With host: " << oscSender.getHost() << endl;
	oscReceiver.setup(oscManagerSettings["incomingPortOsc"]);
	ofLogVerbose() << "OSC Receiver initialised and set to port: " << oscReceiver.getPort() << endl;
}
void OscManager::closeReceiver(){
    ///oscReceiver.stop();
}
void OscManager::setupReceiver(){
    SettingsManager & settingsManager = SettingsManager::getInstance();
    oscManagerSettings = settingsManager.getSettings();
    oscReceiver.setup(oscManagerSettings["incomingPortOsc"]);
    ofLogVerbose() << "OSC Receiver initialised and set to port: " << oscReceiver.getPort() << endl;
    oscReceiver.start();

}
void OscManager::closeSender(){
    //oscSender.clear();
    
}
void OscManager::setupSender(){
    SettingsManager & settingsManager = SettingsManager::getInstance();
    oscManagerSettings = settingsManager.getSettings();
    oscSender.setup(oscManagerSettings["outgoingIpOSC"], oscManagerSettings["outGoingPortOsc"]);
    ofLogVerbose() << "OSC Sender initialised and set to port: " << oscSender.getPort() << " With host: " << oscSender.getHost() << endl;

}
void OscManager::handleIncomingMessages() {
    MidiManager& midiManager = MidiManager::getInstance();
    ofxMidiOut& midiOut = midiManager.getMidiOut();
    int channel = oscManagerSettings.value("midiOutChannel", 1);

    while (oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        std::string address = m.getAddress();
        int numArgs = m.getNumArgs();
        message.clear();

        // Malformed messages are reported instead of crashing the app
        auto needs = [&](int count) {
            if (numArgs >= count) return true;
            message = "Ignored " + address + ": needs " + ofToString(count) + " argument(s), got " + ofToString(numArgs);
            ofLogWarning("OscManager") << message;
            return false;
        };

        if (address == "/noteOn" && needs(1)) {
            int velocity = numArgs > 1 ? m.getArgAsInt32(1) : 64;
            midiOut.sendNoteOn(channel, m.getArgAsInt32(0), velocity);
            message = "Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity " + ofToString(velocity);
        }
        else if (address == "/noteOff" && needs(1)) {
            midiOut.sendNoteOff(channel, m.getArgAsInt32(0));
            message = "Sending note off Note ID " + ofToString(m.getArgAsInt32(0));
        }
        else if (address == "/cc" && needs(2)) {
            midiOut.sendControlChange(channel, m.getArgAsInt32(0), m.getArgAsInt32(1));
            message = "Sending cc Controller ID " + ofToString(m.getArgAsInt32(0)) + " Controller value " + ofToString(m.getArgAsInt32(1));
        }
        else if (address == "/bankSelectMSB" && needs(1)) {
            midiOut.sendControlChange(channel, 0, m.getArgAsInt32(0));
            message = "Sending Bank Select MSB: " + ofToString(m.getArgAsInt32(0));
        }
        else if (address == "/bankSelectLSB" && needs(1)) {
            midiOut.sendControlChange(channel, 32, m.getArgAsInt32(0));
            message = "Sending Bank Select LSB: " + ofToString(m.getArgAsInt32(0));
        }
        else if (address == "/ProgramChange" && needs(1)) {
            midiOut.sendProgramChange(channel, m.getArgAsInt32(0));
            message = "Sending program change ID: " + ofToString(m.getArgAsInt32(0));
        }
        else if ((address == "/PitchBend" || address == "/Pitchbend") && needs(1)) {
            midiOut.sendPitchBend(channel, ofClamp(m.getArgAsInt32(0), 0, 16383));
            message = "Sending pitch bend value: " + ofToString(m.getArgAsInt32(0));
        }
        else if (address == "/Aftertouch" && needs(1)) {
            midiOut.sendAftertouch(channel, m.getArgAsInt32(0));
            message = "Sending aftertouch Value: " + ofToString(m.getArgAsInt32(0));
        }
        else if (address == "/PolyAftertouch" && needs(2)) {
            midiOut.sendPolyAftertouch(channel, m.getArgAsInt32(0), m.getArgAsInt32(1));
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
        }
        else if (address == "/MMCCommand" && needs(2)) {
            int deviceId = m.getArgAsInt32(0);
            std::string command = m.getArgAsString(1);
            std::vector<unsigned char> midiBytes = midiManager.buildMMCMessaage(deviceId, command);
            if (!midiBytes.empty()) {
                midiOut.sendMidiBytes(midiBytes);
                message = "Sending MMC Command: " + command + " DeviceID: " + ofToString(deviceId);
            } else {
                message = "Ignored unknown MMC command: " + command;
            }
        }
        else if (address == "/MidiShowControl" && needs(3)) {
            // device id, target, command, then cue number / list / path (strings
            // or numbers), a "hh:mm:ss:ff" time for timed_go and set_clock,
            // control and value for set, or a macro number for fire
            int deviceId = m.getArgAsInt32(0);
            std::string target = m.getArgAsString(1);
            std::string command = m.getArgAsString(2);
            std::vector<std::string> commandData;
            for (int i = 3; i < numArgs; i++) {
                commandData.push_back(m.getArgType(i) == OFXOSC_TYPE_STRING ? m.getArgAsString(i)
                                      : m.getArgType(i) == OFXOSC_TYPE_FLOAT ? ofToString(m.getArgAsFloat(i))
                                      : ofToString(m.getArgAsInt32(i)));
            }
            std::vector<unsigned char> midiBytes = midiManager.buildMidiShowControlMessage(deviceId, target, command, commandData);
            if (!midiBytes.empty()) {
                midiOut.sendMidiBytes(midiBytes);
                message = "Sending MSC: " + command + " Target: " + target + " DeviceID: " + ofToString(deviceId) + " Data: " + ofJoinString(commandData, " ");
            } else {
                message = "Ignored MSC with unknown target or command: " + target + " " + command;
            }
        }
        else if (address == "/sysex" && needs(1)) {
            // raw bytes as int arguments; F0 and F7 are added if missing
            std::vector<unsigned char> bytes;
            for (int i = 0; i < numArgs; i++) {
                bytes.push_back(m.getArgAsInt32(i) & 0xFF);
            }
            if (bytes.front() != MIDI_SYSEX) bytes.insert(bytes.begin(), MIDI_SYSEX);
            if (bytes.back() != MIDI_SYSEX_END) bytes.push_back(MIDI_SYSEX_END);
            midiOut.sendMidiBytes(bytes);
            message = "Sending SysEx, " + ofToString(bytes.size()) + " bytes";
        }
        else if (message.empty()) {
            message = "Ignored unknown OSC address: " + address;
        }

        ofSendMessage(message);
    }
}

//destructor
OscManager::~OscManager() {
    oscSender.clear();
 


	ofLogVerbose() << "OSC Manager destructor called" << endl;
}
void OscManager::updateSettings(){
    SettingsManager & settingsManager = SettingsManager::getInstance();
    oscManagerSettings = settingsManager.getSettings();
}
