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
    midiManagerSettings = settingsManager.getSettings();

    if (midiManagerSettings["useVirtualPort"]) {
        midiOut.openVirtualPort("OSC_MIDI_OSC_OUT");
        midiIn.openVirtualPort("OSC_MIDI_OSC_IN");
    } else {
        if (midiManagerSettings["midiOutDevice"].is_string()) {
            midiOut.openPort(string(midiManagerSettings["midiOutDevice"]));
        } else if (midiManagerSettings["midiOutDevice"].is_number()) {
            midiOut.openPort(int(midiManagerSettings["midiOutDevice"]));
        }

        if (midiManagerSettings["midiInDevice"].is_string()) {
            midiIn.openPort(string(midiManagerSettings["midiInDevice"]));
        } else if (midiManagerSettings["midiInDevice"].is_number()) {
            midiIn.openPort(int(midiManagerSettings["midiInDevice"]));
        }
    }

    midiIn.ignoreTypes(false, false, false);
    midiIn.addListener(this);
}
void MidiManager::setup(){
    ofLogNotice("MidiManager") << "MidiManager setup";
}
void MidiManager::newMidiMessage(ofxMidiMessage& msg) {
    
    midiMessage = msg;
    
    SettingsManager& settingsManager = SettingsManager::getInstance();
   
    OscManager& oscManager = OscManager::getInstance();
    ofxOscSender& oscSend = oscManager.getOSCSender();
    ofxOscMessage m;


    if (midiMessage.status == MIDI_SYSEX) {
        ofLogVerbose("MidiManager::newMidiMessage") << "Sysex Message" << endl;
        ofLogVerbose("MidiManager::newMidiMessage") << "Message Size " + ofToString(midiMessage.bytes.size()) << endl;
       
        int deviceId = static_cast<int>(midiMessage.bytes[2]);

        //Handle midi machine control messages
        if (midiMessage.bytes[3] == 0x06) {
            ofLogVerbose("MidiManager::newMidiMessage") << "Midi Machine Control Message" << endl;
            
            m.setAddress("/MMCCommand");
            m.addIntArg(deviceId);
            
            std::string command = getMidiMachineControlCommand(midiMessage.bytes[4]);
            m.addStringArg(command);
            
            message = "Received Midi Machine Control message: Command: " + command + " DeviceID: " + ofToString(deviceId);
            
        }
        
        //Handle midi show control messages
        if (midiMessage.bytes[3] == 0x02) {
            ofLogVerbose("MidiManager::newMidiMessage") << "Midi Show Control Message" << endl;

            m.setAddress("/MidiShowControl");
            m.addIntArg(deviceId);
            
            
            m.addStringArg(getMidiShowControTargetType(midiMessage.bytes[4]));
            m.addStringArg(getMidiShowControlCommandType(midiMessage.bytes[5]));

            for (int i = 0; i < getMidiShowControlCommandData(midiMessage).size(); i++) {
                m.addIntArg(getMidiShowControlCommandData(midiMessage)[i]);
            }


            string dataByteString;

            for (int i = 0; i < getMidiShowControlCommandData(midiMessage).size(); i++) {
                dataByteString += ofToString(i)  + ": ";
            }
            
            message =  "Midi Show Control Message: Command: " + ofToString(getMidiShowControlCommandType(midiMessage.bytes[5])) + " Target: " +ofToString(getMidiShowControTargetType(midiMessage.bytes[4])) + " Device ID: " + ofToString(deviceId) + " Command Data: " + dataByteString;
        }

        
    }

    if (midiMessage.channel == midiManagerSettings["midiInChannel"] ) {
        if (midiMessage.status == MIDI_NOTE_ON) {
            m.setAddress("/noteOn");
            m.addIntArg(midiMessage.pitch);
            m.addIntArg(midiMessage.velocity);
            message = "Received Note on Note ID: " + ofToString(midiMessage.pitch) + " With Velocity " + ofToString(midiMessage.velocity);
     
        }

        if (midiMessage.status == MIDI_NOTE_OFF) {
            m.setAddress("/noteOff");
            m.addIntArg(midiMessage.pitch);
     
            message = "Received Note off Note ID: " + ofToString(midiMessage.pitch);
        }

        if (midiMessage.status == MIDI_CONTROL_CHANGE) {
            m.setAddress("/cc");
            m.addIntArg(midiMessage.control);
            m.addIntArg(midiMessage.value);
            
            message = "Received Controller ID: " + ofToString(midiMessage.control) + "  Value: " + ofToString(midiMessage.value);
        }

        if (midiMessage.status == MIDI_TIME_CODE) {
            m.setAddress("/MTC");
            m.addIntArg(midiMessage.deltatime);
            message = "Received MTC: " + ofToString(midiMessage.value);
        }

        if (midiMessage.status == MIDI_PROGRAM_CHANGE) {
            m.setAddress("/ProgramChange");
            m.addIntArg(midiMessage.value);
            message = "Received Program Change ID: " + ofToString(midiMessage.value);
        }

        if (midiMessage.status == MIDI_PITCH_BEND) {
            m.setAddress("/PitchBend");
            m.addIntArg(midiMessage.value);
            message = "Received pitch bend Value: " + ofToString(midiMessage.value);
        }

        if (midiMessage.status == MIDI_AFTERTOUCH) {
            m.setAddress("/Aftertouch");
            m.addIntArg(midiMessage.value);
            message = "Received Aftertouch Value: " + ofToString(midiMessage.value);
        }

        if (midiMessage.status == MIDI_POLY_AFTERTOUCH) {
            m.setAddress("/PolyAftertouch");
            m.addIntArg(midiMessage.value);
            m.addIntArg(midiMessage.pitch);
            message = "Received Poly Aftertouch Pitch: " + ofToString(midiMessage.pitch) + " Value: " + ofToString(midiMessage.value);
        }
    }
    oscSend.sendMessage(m);
    ofLogVerbose("MidiManager::newMidiMessage'") << message << endl;
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
        return it->second;
    } else {
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


std::string MidiManager::getMidiMachineControlCommand(uint8_t byte) {
    auto it = MIDI_MACHINE_CONTROL_COMMAND_TYPE.find(byte);

    if (it != MIDI_MACHINE_CONTROL_COMMAND_TYPE.end()) {
        //ofLogVerbose() << "Midi Show Control Command " << it->second << std::endl;
        return it->second;
    } else {
        // Handle the case where the byte is not found in the map
        //ofLogVerbose() << "Midi Show Control Command Unknown" << std::endl;
        return "unknown";
    }
}

vector<unsigned char> MidiManager::buildMMCMessaage(int deviceID, const std::string& command) {
    sysexMMCMsg.clear();
     sysexMMCMsg.push_back(MIDI_SYSEX);
     sysexMMCMsg.push_back(0x7F); // Real Time Universal SysEx ID
     sysexMMCMsg.push_back(deviceID & 0x7F); // Device ID (limited to 7 bits)
     sysexMMCMsg.push_back(0x06); // MMC Command

     // Find the command byte from the map
     for (const auto& pair : MIDI_MACHINE_CONTROL_COMMAND_TYPE) {
         if (pair.second == command) {
             sysexMMCMsg.push_back(pair.first);
             break;
         }
     }

     sysexMMCMsg.push_back(MIDI_SYSEX_END);
    
    return sysexMMCMsg;
}
