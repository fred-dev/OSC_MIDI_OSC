//
//  SettingsManager.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    // Constructor code
    setDefaultSettings();
}


void SettingsManager::loadSettings(const std::string& filename) {
    if (ofFile::doesFileExist(filename)) {
        settings = ofLoadJson(filename);

        if (!settings["Log_level"].is_null()) {
            ofLogVerbose("loadSettings") << "Log level set to " << settings["Log_level"] << endl;
            ofSetLogLevel(settings["Log_level"]);
        } else {
            settings["Log_level"] = OF_LOG_VERBOSE;
            ofLogVerbose("loadSettings fallback") << "Log level set to " << settings["Log_level"] << endl;
        }

    #ifdef TARGET_OSX

        if (!settings["useVirtualPort"].is_null()) {
            ofLogVerbose("loadSettings") << "useVirtualPort set to " << settings["useVirtualPort"] << endl;
        } else {
            settings["useVirtualPort"] = true;
            ofLogVerbose("loadSettings fallback") << "useVirtualPort set to " << settings["useVirtualPort"] << endl;
        }

    #else
        settings["useVirtualPort"] = false;
        ofLogVerbose("loadSettings") << "useVirtualPort, unavailable on windows, now set to " << settings["useVirtualPort"] << endl;
    #endif

        if (!settings["midiInDevice"].is_null()) {
            if (settings["midiInDevice"].is_number()) {
                settings["midiInDeviceByString"] = false;
                ofLogVerbose("loadSettings") << "midiInDevice set to number: " << settings["midiInDeviceNum"] << endl;
            } else if (settings["midiInDevice"].is_string()) {
                settings["midiInDeviceByString"] = true;
                ofLogVerbose("loadSettings") << "midiInDevice set to string: " << settings["midiInDeviceName"] << endl;
            }
        } else {
            settings["midiInDeviceByString"] = false;
            settings["midiInDevice"] = 0;
            ofLogVerbose("loadSettings") << "midiInDevice set to number" << settings["midiInDevice"] << endl;
        }

        if (!settings["midiOutDevice"].is_null()) {
            if (settings["midiOutDevice"].is_number()) {
                settings["midiOutDeviceByString"] = false;
                ofLogVerbose("loadSettings") << "midiOutDevice set to number: " << settings["midiOutDeviceNum"]  << endl;
            } else if (settings["midiOutDevice"].is_string()) {
                settings["midiOutDeviceByString"] = true;
                ofLogVerbose("loadSettings") << "midiOutDevice set to string: " << settings["midiOutDeviceName"] << endl;
            }
        } else {
            settings["midiOutDeviceByString"] = false;
            settings["midiOutDevice"] = 0;
            ofLogVerbose("loadSettings") << "midiOutDevice set to " << settings["midiOutDevice"]  << endl;
        }

        if (!settings["midiOutChannel"].is_null()) {
            ofLogVerbose("loadSettings") << "midiOutChannel set to " << settings["midiOutChannel"] << endl;
        } else {
            settings["midiOutChannel"] = 1;
            ofLogVerbose("loadSettings fallback") << "midiOutChannel set to " << settings["midiOutChannel"] << endl;
        }

        if (!settings["midiInChannel"].is_null()) {
            ofLogVerbose("loadSettings") << "midiInChannel set to " << settings["midiInChannel"] << endl;
        } else {
            settings["midiInChannel"] = 1;
            ofLogVerbose("loadSettings fallback") << "midiInChannel set to " << settings["midiInChannel"] << endl;
        }

        //set the incomingPortOsc from the settings
        if (!settings["incomingPortOsc"].is_null()) {
            ofLogVerbose("loadSettings") << "incomingPortOsc set to " << settings["incomingPortOsc"] << endl;
        } else {
            settings["incomingPortOsc"] = 12345;
            ofLogVerbose("loadSettings fallback") << "incomingPortOsc set to " << settings["incomingPortOsc"] << endl;
        }

        if (!settings["outGoingPortOsc"].is_null()) {
            ofLogVerbose("loadSettings") << "outGoingPortOsc set to " << settings["outGoingPortOsc"] << endl;
        } else {
            settings["outGoingPortOsc"] = 1234;
            ofLogVerbose("loadSettings fallback") << "outGoingPortOsc set to " << settings["outGoingPortOsc"] << endl;
        }

        if (!settings["outgoingIpOSC"].is_null()) {
            ofLogVerbose("loadSettings") << "outgoingIpOSC set to " << settings["outgoingIpOSC"] << endl;
        } else {
            settings["outgoingIpOSC"] = "127.0.0.1";
            ofLogVerbose("loadSettings fallback") << "outgoingIpOSC set to " << settings["outgoingIpOSC"] << endl;
        }

        if (!settings["frameRate"].is_null()) {
            ofLogVerbose("loadSettings") << "frameRate set to " << settings["frameRate"] << endl;
        } else {
            settings["frameRate"] = 25;
        }
    } else {
        ofLogError("SettingsManager::LoadSettings") << "Settings file not found: " << filename;
        setDefaultSettings();
    }
}

ofJson SettingsManager::getSettings() const {
    return settings;
}

void SettingsManager::setDefaultSettings() {
    ofLogVerbose("SettingsManager::setDefaultSettings") << "Loading defualt settings" << endl;

    settings["Log_level"] = OF_LOG_VERBOSE;
    ofLogVerbose("SettingsManager::setDefaultSettings") << "Log level set to " << settings["Log_level"] << endl;

#ifdef TARGET_OSX
    settings["useVirtualPort"] = true;
#else
    settings["useVirtualPort"] = false;
#endif
    ofLogVerbose("SettingsManager::setDefaultSettings") << "useVirtualPort set to " << settings["useVirtualPort"]  << endl;

    settings["incomingPortOsc"] = 12345;
    ofLogVerbose("SettingsManager::setDefaultSettings") << "incomingPortOsc set to " << settings["incomingPortOsc"] << endl;

    settings["outGoingPortOsc"] = 1234;
    ofLogVerbose("SettingsManager::setDefaultSettings") << "outGoingPortOsc set to " << settings["outGoingPortOsc"] << endl;

    settings["outgoingIpOSC"] = "127.0.0.1";
    ofLogVerbose("SettingsManager::setDefaultSettings") << "outgoingIpOSC set to " << settings["outgoingIpOSC"] << endl;

    settings["midiInDevice"] = 0;
    ofLogVerbose("SettingsManager::setDefaultSettings") << "midiInDevice set to " << settings["midiInDevice"] << endl;

    settings["midiOutDevice"] = 0;
    ofLogVerbose("SettingsManager::setDefaultSettings") << "midiOutDevice set to " << settings["midiOutDevice"] << endl;

    settings["midiOutChannel"] = 1;
    ofLogVerbose("SettingsManager::setDefaultSettings") << "midiOutChannel set to " << settings["midiOutChannel"] << endl;


    settings["midiInChannel"] = 1;
    ofLogVerbose("SettingsManager::setDefaultSettings") << "midiInChannel set to " << settings["midiInChannel"] << endl;

    settings["frameRate"] = 25;
    ofLogVerbose("SettingsManager::setDefaultSettings") << "frameRate set to " << settings["frameRate"] << endl;
}

void SettingsManager::saveSettings(const std::string& filename, ofJson remoteSettings){
    settings = remoteSettings;
    
    ofLogVerbose("SettingsManager::saveSettings") << "Saving settings to " << filename << endl;
    ofSavePrettyJson(filename, settings);
}

void SettingsManager::updateSettings(ofJson remoteSettings){
    settings = remoteSettings;
    ofLogVerbose("SettingsManager::updateSettings") << "Settings updated" << endl;
}
//public destructor
SettingsManager::~SettingsManager() {
	// Destructor code
}
