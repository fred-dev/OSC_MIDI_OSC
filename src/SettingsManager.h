//
//  SettingsManager.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#pragma once
#include <stdio.h>
#include "ofMain.h"

class SettingsManager {
public:
    static SettingsManager& getInstance() {
        static SettingsManager instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }
  
    ~SettingsManager(); // Private destructor

    void loadSettings(const std::string& filename);
    ofJson getSettings() const;

    // Delete copy constructor and assignment operator
    SettingsManager(SettingsManager const&) = delete;
    void operator=(SettingsManager const&) = delete;
    
    void saveSettings(const std::string& filename, ofJson remoteSettings);
    void updateSettings(ofJson remoteSettings);

private:
    SettingsManager(); // Private constructor

    ofJson settings;
    
    void setDefaultSettings();
};

