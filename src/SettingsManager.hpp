//
//  SettingsManager.hpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#ifndef SettingsManager_hpp
#define SettingsManager_hpp

#pragma once
#include <stdio.h>
#include "ofMain.h"

class SettingsManager {
public:
    static SettingsManager& getInstance();

    void loadSettings(const std::string& filename);
    ofJson getSettings() const;

    // Delete copy constructor and assignment operator
    SettingsManager(SettingsManager const&) = delete;
    void operator=(SettingsManager const&) = delete;

private:
    SettingsManager(); // Private constructor
    ~SettingsManager(); // Private destructor

    ofJson settings;
    
    void setDefaultSettings();
};

#endif /* SettingsManager_hpp */
