//
//  MidiManager.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "MidiManager.h"

namespace {
    // MSC commands whose data starts with a 5 byte time (hr mn sc fr ff)
    bool mscHasTime(const std::string& command) {
        return command == "timed_go" || command == "set_clock";
    }

    // Cue numbers, lists and paths travel as ASCII digits and '.'
    std::string asCueText(const ofxOscMessage& m, int index) {
        switch (m.getArgType(index)) {
            case OFXOSC_TYPE_STRING: return m.getArgAsString(index);
            case OFXOSC_TYPE_FLOAT:
            case OFXOSC_TYPE_DOUBLE: {
                std::string s = ofToString(m.getArgAsFloat(index), 3);
                s.erase(s.find_last_not_of('0') + 1);
                if (!s.empty() && s.back() == '.') s.pop_back();
                return s;
            }
            default: return ofToString(m.getArgAsInt32(index));
        }
    }
}

MidiManager::MidiManager() {

}

void MidiManager::openOutPort() {
    std::vector<std::string> ports = midiOut.getOutPortList();
    if (midiManagerSettings["midiOutDevice"].is_string()) {
        std::string wanted = midiManagerSettings["midiOutDevice"];
        auto it = std::find(ports.begin(), ports.end(), wanted);
        if (it != ports.end()) {
            midiOut.openPort(wanted);
            return;
        }
        ofLogWarning("MidiManager") << "MIDI out port \"" << wanted << "\" not found, using the first port";
    } else if (midiManagerSettings["midiOutDevice"].is_number()) {
        int wanted = midiManagerSettings["midiOutDevice"];
        if (wanted >= 0 && wanted < (int)ports.size()) {
            midiOut.openPort(wanted);
            return;
        }
    }
    if (!ports.empty()) {
        midiOut.openPort(0);
    } else {
        ofLogWarning("MidiManager") << "No MIDI out ports available";
    }
}

void MidiManager::openInPort() {
    std::vector<std::string> ports = midiIn.getInPortList();
    if (midiManagerSettings["midiInDevice"].is_string()) {
        std::string wanted = midiManagerSettings["midiInDevice"];
        auto it = std::find(ports.begin(), ports.end(), wanted);
        if (it != ports.end()) {
            midiIn.openPort(wanted);
            return;
        }
        ofLogWarning("MidiManager") << "MIDI in port \"" << wanted << "\" not found, using the first port";
    } else if (midiManagerSettings["midiInDevice"].is_number()) {
        int wanted = midiManagerSettings["midiInDevice"];
        if (wanted >= 0 && wanted < (int)ports.size()) {
            midiIn.openPort(wanted);
            return;
        }
    }
    if (!ports.empty()) {
        midiIn.openPort(0);
    } else {
        ofLogWarning("MidiManager") << "No MIDI in ports available";
    }
}

void MidiManager::setup(){
    ofLogNotice("MidiManager") << "MidiManager setup";
	// Get the instance of SettingsManager
	SettingsManager & settingsManager = SettingsManager::getInstance();

	// Access the settings
	midiManagerSettings = settingsManager.getSettings();

    midiManagerSettings["allOutPorts"] = midiOut.getOutPortList();
    midiManagerSettings["allInPorts"] = midiIn.getInPortList();

	if (midiManagerSettings.value("useVirtualPort", false)) {
		midiOut.openVirtualPort("OSC_MIDI_OSC_OUT");
		midiIn.openVirtualPort("OSC_MIDI_OSC_IN");
	} else {
		openOutPort();
		openInPort();
	}
    midiManagerSettings["outPortLabel"] = midiOut.getName();
    midiManagerSettings["inPortLabel"] = midiIn.getName();

    settingsManager.saveSettings("MIDI_OSC_SETTINGS.json", midiManagerSettings);

	ofLogVerbose("MidiManager") << "MIDI out port: " + midiOut.getName() + " MIDI in port: " + midiIn.getName();
	// sysex, timing (MTC) and active sensing all come through
	midiIn.ignoreTypes(false, false, false);
	midiIn.addListener(this);
}

void MidiManager::close(){
    midiIn.removeListener(this);
    midiIn.closePort();
    midiOut.closePort();
}

void MidiManager::postActivity(const std::string& text) {
    std::lock_guard<std::mutex> lock(activityMutex);
    pendingActivity = text;
    hasPendingActivity = true;
}

bool MidiManager::getNewActivity(std::string& text) {
    std::lock_guard<std::mutex> lock(activityMutex);
    if (!hasPendingActivity) return false;
    text = pendingActivity;
    hasPendingActivity = false;
    return true;
}

void MidiManager::sendTimecode(int hours, int minutes, int seconds, int frames, int rateCode, ofxOscSender& sender) {
    static const float rates[4] = {24, 25, 29.97f, 30};
    ofxOscMessage m;
    m.setAddress("/MTC");
    m.addIntArg(hours);
    m.addIntArg(minutes);
    m.addIntArg(seconds);
    m.addIntArg(frames);
    m.addFloatArg(rates[rateCode & 3]);
    sender.sendMessage(m);
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d:%02d", hours, minutes, seconds, frames);
    postActivity("Received MTC: " + std::string(buffer) + " @ " + ofToString(rates[rateCode & 3]) + " fps");
}

// Called on ofxMidi's thread
void MidiManager::newMidiMessage(ofxMidiMessage& msg) {

    midiMessage = msg;

    OscManager& oscManager = OscManager::getInstance();
    ofxOscSender& oscSend = oscManager.getOSCSender();
    ofxOscMessage m;
    message.clear();

    const std::vector<unsigned char>& bytes = midiMessage.bytes;

    if (midiMessage.status == MIDI_SYSEX) {
        ofLogVerbose("MidiManager::newMidiMessage") << "Sysex message, " << bytes.size() << " bytes";

        bool universalRealTime = bytes.size() >= 6 && bytes[1] == 0x7F;
        int deviceId = bytes.size() > 2 ? static_cast<int>(bytes[2]) : 0;

        if (universalRealTime && bytes[3] == 0x06) {
            //Handle midi machine control messages: F0 7F dev 06 command F7
            m.setAddress("/MMCCommand");
            m.addIntArg(deviceId);
            std::string command = getMidiMachineControlCommand(bytes[4]);
            m.addStringArg(command);
            message = "Received Midi Machine Control message: Command: " + command + " DeviceID: " + ofToString(deviceId);
        }
        else if (universalRealTime && bytes[3] == 0x02) {
            //Handle midi show control messages: F0 7F dev 02 format command data F7
            std::string target = getMidiShowControTargetType(bytes[4]);
            std::string command = getMidiShowControlCommandType(bytes[5]);
            std::vector<std::string> data = getMidiShowControlCommandData(midiMessage);
            m.setAddress("/MidiShowControl");
            m.addIntArg(deviceId);
            m.addStringArg(target);
            m.addStringArg(command);
            for (auto& field : data) {
                m.addStringArg(field);
            }
            message = "Received Midi Show Control: " + command + " Target: " + target + " Device ID: " + ofToString(deviceId) + " Data: " + ofJoinString(data, " ");
        }
        else if (universalRealTime && bytes.size() >= 10 && bytes[3] == 0x01 && bytes[4] == 0x01) {
            //Full frame MTC: F0 7F dev 01 01 hr mn sc fr F7
            sendTimecode(bytes[5] & 0x1F, bytes[6] & 0x3F, bytes[7] & 0x3F, bytes[8] & 0x1F, (bytes[5] >> 5) & 0x03, oscSend);
            return;
        }
        else {
            //Anything else is passed through as raw bytes
            m.setAddress("/sysex");
            for (auto b : bytes) {
                m.addIntArg(b);
            }
            message = "Received SysEx, " + ofToString(bytes.size()) + " bytes";
        }
    }
    else if (midiMessage.status == MIDI_TIME_CODE) {
        //Quarter frame: high nibble is the piece (0-7), low nibble the value.
        //System messages have no channel, so they skip the channel filter.
        if (bytes.size() >= 2) {
            int piece = (bytes[1] >> 4) & 0x07;
            mtcPieces[piece] = bytes[1] & 0x0F;
            mtcPiecesSeen |= (1 << piece);
            if (piece == 7 && mtcPiecesSeen == 0xFF) {
                int frames = mtcPieces[0] | (mtcPieces[1] << 4);
                int seconds = mtcPieces[2] | (mtcPieces[3] << 4);
                int minutes = mtcPieces[4] | (mtcPieces[5] << 4);
                int hours = mtcPieces[6] | ((mtcPieces[7] & 0x01) << 4);
                int rate = (mtcPieces[7] >> 1) & 0x03;
                mtcPiecesSeen = 0;
                sendTimecode(hours, minutes, seconds, frames, rate, oscSend);
            }
        }
        return;
    }
    else {
        //Channel messages: 0 in the settings means any channel
        int wantedChannel = midiManagerSettings.value("midiInChannel", 1);
        if (wantedChannel != 0 && midiMessage.channel != wantedChannel) {
            return;
        }

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
            if (midiMessage.control == 0) { // Bank Select MSB
                m.setAddress("/bankSelectMSB");
                m.addIntArg(midiMessage.value);
                message = "Received Bank Select MSB: " + ofToString(midiMessage.value);

            } else if (midiMessage.control == 32) { // Bank Select LSB
                m.setAddress("/bankSelectLSB");
                m.addIntArg(midiMessage.value);
                message = "Received Bank Select LSB: " + ofToString(midiMessage.value);

            } else {
                m.setAddress("/cc");
                m.addIntArg(midiMessage.control);
                m.addIntArg(midiMessage.value);
                message = "Received Controller ID: " + ofToString(midiMessage.control) + "  Value: " + ofToString(midiMessage.value);
            }
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
            // Same order as the incoming OSC format: pitch, then value
            m.setAddress("/PolyAftertouch");
            m.addIntArg(midiMessage.pitch);
            m.addIntArg(midiMessage.value);
            message = "Received Poly Aftertouch Pitch: " + ofToString(midiMessage.pitch) + " Value: " + ofToString(midiMessage.value);
        }
    }

    // Clock, active sensing and other unhandled messages are not forwarded
    if (m.getAddress().empty()) {
        return;
    }
    oscSend.sendMessage(m);
    ofLogVerbose("MidiManager::newMidiMessage") << message;
    postActivity(message);
}

std::string MidiManager::getMidiShowControTargetType(uint8_t byte) {
    auto it = MIDI_SHOW_CONTROL_TARGET_TYPE.find(byte);

    if (it != MIDI_SHOW_CONTROL_TARGET_TYPE.end()) {
        return it->second;
    } else {
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

std::vector<std::string> MidiManager::getMidiShowControlCommandData(const ofxMidiMessage& midiMessage) {
    // Data sits between the command byte (index 5) and the end byte F7
    const std::vector<unsigned char>& bytes = midiMessage.bytes;
    std::vector<std::string> commandData;
    if (bytes.size() < 7) {
        return commandData;
    }
    size_t i = 6;
    size_t end = bytes.size() - 1;
    std::string command = getMidiShowControlCommandType(bytes[5]);

    if (mscHasTime(command) && end - i >= 5) {
        // hr mn sc fr ff, sent as one "hh:mm:ss:ff" field
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d:%02d", bytes[i] & 0x1F, bytes[i + 1] & 0x3F, bytes[i + 2] & 0x3F, bytes[i + 3] & 0x1F);
        commandData.push_back(buffer);
        i += 5;
    }
    if (command == "set" && end - i >= 4) {
        // control number and value, both 14 bit LSB first
        commandData.push_back(ofToString(bytes[i] | (bytes[i + 1] << 7)));
        commandData.push_back(ofToString(bytes[i + 2] | (bytes[i + 3] << 7)));
        return commandData;
    }
    if (command == "fire" && end > i) {
        commandData.push_back(ofToString(int(bytes[i])));
        return commandData;
    }

    // Cue number, list and path: ASCII separated by 0x00
    std::string field;
    for (; i < end; i++) {
        if (bytes[i] == 0x00) {
            commandData.push_back(field);
            field.clear();
        } else {
            field += static_cast<char>(bytes[i]);
        }
    }
    if (!field.empty()) {
        commandData.push_back(field);
    }
    return commandData;
}


std::string MidiManager::getMidiMachineControlCommand(uint8_t byte) {
    auto it = MIDI_MACHINE_CONTROL_COMMAND_TYPE.find(byte);

    if (it != MIDI_MACHINE_CONTROL_COMMAND_TYPE.end()) {
        return it->second;
    } else {
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
    bool found = false;
    for (const auto& pair : MIDI_MACHINE_CONTROL_COMMAND_TYPE) {
        if (pair.second == command) {
            sysexMMCMsg.push_back(pair.first);
            found = true;
            break;
        }
    }
    if (!found) {
        ofLogWarning("MidiManager") << "Unknown MMC command: " << command;
        sysexMMCMsg.clear();
        return sysexMMCMsg;
    }

    sysexMMCMsg.push_back(MIDI_SYSEX_END);
    return sysexMMCMsg;
}

std::vector<unsigned char> MidiManager::buildMidiShowControlMessage(int deviceID, const std::string& targetType, const std::string& commandType, const std::vector<std::string>& commandData) {
    std::vector<unsigned char> sysexMSCMsg;

    int targetByte = -1, commandByte = -1;
    for (const auto& pair : MIDI_SHOW_CONTROL_TARGET_TYPE) {
        if (pair.second == targetType) targetByte = pair.first;
    }
    for (const auto& pair : MIDI_SHOW_CONTROL_COMMAND_TYPE) {
        if (pair.second == commandType) commandByte = pair.first;
    }
    if (targetByte < 0 || commandByte < 0) {
        ofLogWarning("MidiManager") << "Unknown MSC target \"" << targetType << "\" or command \"" << commandType << "\"";
        return sysexMSCMsg;
    }

    sysexMSCMsg.push_back(MIDI_SYSEX);
    sysexMSCMsg.push_back(0x7F); // Real Time Universal SysEx ID
    sysexMSCMsg.push_back(deviceID & 0x7F); // Device ID, 0x7F is all-call
    sysexMSCMsg.push_back(0x02); // Midi Show Control Command
    sysexMSCMsg.push_back(targetByte);
    sysexMSCMsg.push_back(commandByte);

    size_t first = 0;
    if (mscHasTime(commandType) && !commandData.empty()) {
        // "hh:mm:ss:ff" -> hr mn sc fr ff
        std::vector<std::string> parts = ofSplitString(commandData[0], ":");
        for (int p = 0; p < 4; p++) {
            sysexMSCMsg.push_back(p < (int)parts.size() ? ofToInt(parts[p]) & 0x7F : 0);
        }
        sysexMSCMsg.push_back(0x00); // fractional frames
        first = 1;
    }

    if (commandType == "set") {
        // control number and value, 14 bit LSB first
        for (size_t f = 0; f < 2; f++) {
            int v = f < commandData.size() ? ofClamp(ofToInt(commandData[f]), 0, 16383) : 0;
            sysexMSCMsg.push_back(v & 0x7F);
            sysexMSCMsg.push_back((v >> 7) & 0x7F);
        }
    } else if (commandType == "fire") {
        sysexMSCMsg.push_back(commandData.empty() ? 0 : ofToInt(commandData[0]) & 0x7F);
    } else {
        // Cue number, list and path as ASCII, separated by 0x00
        for (size_t f = first; f < commandData.size(); f++) {
            if (f > first) sysexMSCMsg.push_back(0x00);
            for (char c : commandData[f]) {
                sysexMSCMsg.push_back(static_cast<unsigned char>(c) & 0x7F);
            }
        }
    }

    sysexMSCMsg.push_back(MIDI_SYSEX_END);
    return sysexMSCMsg;
}

//destructors
MidiManager::~MidiManager() {
    midiIn.removeListener(this);
    midiIn.closePort();
    midiOut.closePort();
	ofLogVerbose("MidiManager") << "Destructor called";
}

void MidiManager::updateSettings(){
    SettingsManager & settingsManager = SettingsManager::getInstance();
    midiManagerSettings = settingsManager.getSettings();
}
