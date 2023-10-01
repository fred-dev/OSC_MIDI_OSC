//
//  MidiManager.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "MidiManager.h"

MidiManager::MidiManager() {
    // Get the instance of SettingsManager
    SettingsManager& settingsManager = SettingsManager::getInstance();

    // Access the settings
    ofJson settings = settingsManager.getSettings();
    
    if (settings["useVirtualPort"]) {
        midiOut.openVirtualPort("OSC_MIDI_OSC_OUT");
        midiIn.openVirtualPort("OSC_MIDI_OSC_IN");

    } else {
        if(settings["midiOutDevice"].is_string()){
            midiOut.openPort(string(settings["midiOutDevice"]));
        }
        else if (settings["midiOutDevice"].is_number()){
            midiOut.openPort(int(settings["midiOutDevice"]));
        }
        if(settings["midiInDevice"].is_string()){
            midiIn.openPort(string(settings["midiInDevice"]));
        }
        else if (settings["midiInDevice"].is_number()){
            midiIn.openPort(int(settings["midiInDevice"]));
        }
    }
    
    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);   
 
}


void MidiManager::newMidiMessage(ofxMidiMessage& msg){
    midiMessage = msg;
    
    if (midiMessage.status == MIDI_SYSEX) {
        ofLogVerbose() << "Sysex Message" << endl;
        ofLogVerbose() << "Message Size " + ofToString(midiMessage.bytes.size()) << endl;
        ofxOscMessage m;
        if (midiMessage.bytes[3] == 0x02) {
            //this is a midi show control message
            
            //check the command byte
            int deviceId = static_cast<int>(midiMessage.bytes[2]);
            m.setAddress("/MidiShowControl");
            m.addIntArg(deviceId);
            m.addStringArg(getMidiShowControTargetType(midiMessage.bytes[4]));
            m.addStringArg(getMidiShowControlCommandType(midiMessage.bytes[5]));
            for (int i = 0; i < getMidiShowControlCommandData(midiMessage).size(); i++) {
                m.addIntArg(getMidiShowControlCommandData(midiMessage)[i]);
            }
            oscSend.sendMessage(m);
            
            string dataByteString;
            for (int i = 0; i < getMidiShowControlCommandData(midiMessage).size(); i++) {
                dataByteString += ofToString(i)  + ": " ;
            }
            //lets log the same message to the console:
            ofLogVerbose() << "Midi Show Control Message:" << " Command: " + getMidiShowControlCommandType(midiMessage.bytes[5]) << " Target: " + getMidiShowControTargetType(midiMessage.bytes[4]) << " Device ID: " + ofToString(deviceId) << " Command Data: " << dataByteString << endl;
            
        }
        
        if (midiMessage.bytes[3] == 0x06) {
            ofLogVerbose() << "Midi Machine Control Message" << endl;
            
            if (midiMessage.bytes[4] == 0x01) {
                m.setAddress("/MMCCommand/stop");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Stop";
            }
            if (midiMessage.bytes[4] == 0x02) {
                m.setAddress("/MMCCommand/play");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Play";
            }
            if (midiMessage.bytes[4] == 0x04) {
                m.setAddress("/MMCCommand/forward");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Fast forward";
            }
            if (midiMessage.bytes[4] == 0x05) {
                m.setAddress("/MMCCommand/rewind");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Rewind";
            }
            if (midiMessage.bytes[4] == 0x06) {
                m.setAddress("/MMCCommand/punchIn");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Pucnh in";
            }
            if (midiMessage.bytes[4] == 0x07) {
                m.setAddress("/MMCCommand/punchOut");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Puch Out";
            }
            if (midiMessage.bytes[4] == 0x08) {
                m.setAddress("/MMCCommand/recordPause");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Record Pause";
            }
            if (midiMessage.bytes[4] == 0x09) {
                m.setAddress("/MMCCommand/pause");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Pause";
            }
            
            oscSend.sendMessage(m);
            
            ofLogVerbose() << message << endl;
        }
    }
    if (midiMessage.channel == midiInChannel) {
        if (midiMessage.status == MIDI_NOTE_ON) {
            ofxOscMessage m;
            m.setAddress("/noteOn");
            m.addIntArg(midiMessage.pitch);
            m.addIntArg(midiMessage.velocity);
            oscSend.sendMessage(m);
            message = "Received Note on Note ID: " + ofToString(midiMessage.pitch) + " With Velocity " + ofToString(midiMessage.velocity);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_NOTE_OFF) {
            ofxOscMessage m;
            m.setAddress("/noteOff");
            m.addIntArg(midiMessage.pitch);
            oscSend.sendMessage(m);
            message = "Received Note off Note ID: " + ofToString(midiMessage.pitch);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_CONTROL_CHANGE) {
            ofxOscMessage m;
            m.setAddress("/cc");
            m.addIntArg(midiMessage.control);
            m.addIntArg(midiMessage.value);
            oscSend.sendMessage(m);
            message = "Received Controller ID: " + ofToString(midiMessage.control) + "  Value: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_TIME_CODE) {
            ofxOscMessage m;
            m.setAddress("/MTC");
            m.addIntArg(midiMessage.deltatime);
            oscSend.sendMessage(m);
            message = "Received MTC: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_PROGRAM_CHANGE) {
            ofxOscMessage m;
            m.setAddress("/ProgramChange");
            m.addIntArg(midiMessage.value);
            oscSend.sendMessage(m);
            message = "Received Program Change ID: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_PITCH_BEND) {
            ofxOscMessage m;
            m.setAddress("/PitchBend");
            m.addIntArg(midiMessage.value);
            oscSend.sendMessage(m);
            message = "Received pitch bend Value: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_AFTERTOUCH) {
            ofxOscMessage m;
            m.setAddress("/Aftertouch");
            m.addIntArg(midiMessage.value);
            oscSend.sendMessage(m);
            message = "Received Aftertouch Value: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_POLY_AFTERTOUCH) {
            ofxOscMessage m;
            m.setAddress("/PolyAftertouch");
            m.addIntArg(midiMessage.value);
            m.addIntArg(midiMessage.pitch);
            oscSend.sendMessage(m);
            message = "Received Poly Aftertouch Pitch: " + ofToString(midiMessage.pitch) + " Value: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
    }
}

std::string MidiManager::getMidiShowControTargetType(uint8_t byte) {
    
    auto it = MIDI_SHOW_CONTROL_TARGET_TYPE.find(byte);
    if (it != MIDI_SHOW_CONTROL_TARGET_TYPE.end()) {
        //ofLogVerbose() << "Midi Show Control Target " << it->second << std::endl;
        return it->second;
    } else {
        // Handle the case where the byte is not found in the map
        //ofLogVerbose() << "Midi Show Control Target Unknown" << std::endl;
        return "unknown";
    }
}

std::string MidiManager::getMidiShowControlCommandType(uint8_t byte) {
    
    auto it = MIDI_SHOW_CONTROL_COMMAND_TYPE.find(byte);
    if (it != MIDI_SHOW_CONTROL_COMMAND_TYPE.end()) {
        //ofLogVerbose() << "Midi Show Control Command " << it->second << std::endl;
        return it->second;
    } else {
        // Handle the case where the byte is not found in the map
        //ofLogVerbose() << "Midi Show Control Command Unknown" << std::endl;
        return "unknown";
    }
}

std::vector<int> MidiManager::getMidiShowControlCommandData(ofxMidiMessage midiMessage) {
    // Calculate the command data length (excluding the start byte, manufacturer ID, device ID, Sub-IDs, command format, and end byte)
    int commandDataLength = midiMessage.bytes.size() - 7;
    
    // Create a vector to store the command data
    std::vector<int> commandData;
    // Create a string to accumulate digits
    std::string numberStr;
    
    // Loop through the command data
    for (int i = 6; i < 6 + commandDataLength; i++) {
        // Check if the byte is not 0x00 (separator) and not 0xF7 (end byte)
        if (midiMessage.bytes[i] != 0x00 && midiMessage.bytes[i] != 0xF7) {
            // Accumulate digits
            numberStr += static_cast<char>(midiMessage.bytes[i]);
        } else if (!numberStr.empty()) {
            // Convert the accumulated string to an integer and add to the vector
            commandData.push_back(std::stoi(numberStr));
            // Clear the accumulated string for the next number
            numberStr.clear();
        }
    }
    
    // Handle the last number if the string is not empty
    if (!numberStr.empty()) {
        commandData.push_back(std::stoi(numberStr));
    }
    
    return commandData;
}

void MidiManager::buildSysExMMCMessage(char ID) {
    sysexMMCMsg.clear();
    sysexMMCMsg.push_back(MIDI_SYSEX);
    sysexMMCMsg.push_back(0x7F);
    sysexMMCMsg.push_back(0x7F);
    sysexMMCMsg.push_back(0x06);
    sysexMMCMsg.push_back(ID);
    sysexMMCMsg.push_back(MIDI_SYSEX_END);
}
