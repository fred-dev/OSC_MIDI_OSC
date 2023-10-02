#pragma once

#include "ofMain.h"
#include "SettingsManager.h"
#include "MidiManager.h"
#include "OscManager.h"

#define MODE_SETTING_MIDI_IN 0
#define MODE_SETTING_MIDI_OUT 1
#define MODE_SETTING_OSC_IN 2
#define MODE_SETTING_OSC_OUT 3
#define MODE_CONVERSION 4


class ofApp : public ofBaseApp {

    public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        SettingsManager& settingsManager = SettingsManager::getInstance();
        MidiManager& midiManager = MidiManager::getInstance();
        OscManager& oscManager = OscManager::getInstance();
        ofJson appSettings;
        
        std::string activityMessage;
    
    int operationMode = MODE_SETTING_MIDI_IN;
    
    std::vector<std::string> midiInPortList;
    std::vector<std::string> midiOutPortList;
    int selectedInPort, selectedOutPort;


		
};
