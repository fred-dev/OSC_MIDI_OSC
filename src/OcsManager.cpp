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

    while (oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);

        if (m.getAddress() == "/noteOn") {
            if (m.getNumArgs() > 1) {
                midiOut.sendNoteOn(oscManagerSettings["midiOutChannel"], m.getArgAsInt32(0), m.getArgAsInt32(1));
                message = "Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity " + ofToString(m.getArgAsInt32(1));
            }

            if (m.getNumArgs() == 1) {
                midiOut.sendNoteOn(oscManagerSettings["midiOutChannel"], m.getArgAsInt32(0));
                message = "Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity " + ofToString(64);
            }
        }

        if (m.getAddress() == "/noteOff") {
            midiOut.sendNoteOff(oscManagerSettings["midiOutChannel"], m.getArgAsInt32(0));
            message = "Sending note off Note ID " + ofToString(m.getArgAsInt32(0));
        }

        if (m.getAddress() == "/cc") {
            midiOut.sendControlChange(oscManagerSettings["midiOutChannel"], m.getArgAsInt32(0), m.getArgAsInt32(1));
            message = "Sending cc Controller ID " + ofToString(m.getArgAsInt32(0)) + " Controller value " + ofToString(m.getArgAsInt32(1));
        }

        if (m.getAddress() == "/ProgramChange") {
            midiOut.sendProgramChange(oscManagerSettings["midiOutChannel"], m.getArgAsInt32(0));
            message = "Sending program change ID: " + ofToString(m.getArgAsInt32(0));
        }

        if (m.getAddress() == "/PitchBend") {
            midiOut.sendPitchBend(oscManagerSettings["midiOutChannel"], m.getArgAsInt32(0));
            message = "Sending pitch bend value: " + ofToString(m.getArgAsInt32(0));
        }

        if (m.getAddress() == "/Aftertouch") {
            midiOut.sendAftertouch(oscManagerSettings["midiOutChannel"], m.getArgAsInt32(0));
            message = "Sending aftertouch Value: " + ofToString(m.getArgAsInt32(0));
        }

        if (m.getAddress() == "/PolyAftertouch") {
            midiOut.sendPolyAftertouch(oscManagerSettings["midiOutChannel"], m.getArgAsInt32(0), m.getArgAsInt32(1));
            message = "Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
        }

        if (m.getAddress() == "/MMCCommand") {
            int deviceId = m.getArgAsInt32(0);
            std::string command = m.getArgAsString(1);

            // Convert the command string back to its corresponding MMC byte
            uint8_t commandByte = 0x00;
            for (const auto& pair : MIDI_MACHINE_CONTROL_COMMAND_TYPE) {
                if (pair.second == command) {
                    commandByte = pair.first;
                    break;
                }
            }
            std::vector<unsigned char> midiBytes = midiManager.buildMMCMessaage(deviceId, command);
            midiOut.sendMidiBytes(midiBytes);
            message = "Sending MMC Command: " + command + " DeviceID: " + ofToString(deviceId);
        }
        if(m.getAddress() == "/MidiShowControl"){
            int deviceId = m.getArgAsInt32(0);
            std::string command = m.getArgAsString(1);
            std::string commandFormat = m.getArgAsString(2);
            std::vector<int> commandData;
            for(int i = 3; i < m.getNumArgs(); i++){  
                commandData.push_back(m.getArgAsInt(i));
            }
            std::vector<unsigned char> midiBytes = midiManager.buildMidiShowControlMessage(deviceId, command, commandFormat, commandData);
            midiOut.sendMidiBytes(midiBytes);
            message = "Sending MSC Command: " + command + " DeviceID: " + ofToString(deviceId);
            
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
