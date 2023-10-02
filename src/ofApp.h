#pragma once

#include "ofMain.h"
#include "SettingsManager.h"
#include "MidiManager.h"
#include "OscManager.h"
#include "ofxTextInputField.h"


enum OperationMode {
    MODE_SETTING_MIDI_IN,
    MODE_SETTING_MIDI_OUT,
    MODE_SETTING_OSC_IN,
    MODE_SETTING_OSC_OUT,
    MODE_CONVERSION
};

const int MAX_MIDI_CHANNEL = 16;

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

    // Helper function to handle port selection
    void selectPort(ofJson& ports, ofJson& currentPort, int direction);

    // Helper function to handle channel selection
    void selectChannel(ofJson& channel, int direction);
    
    void drawMidiSettings(const std::string& title, const ofJson& ports, const ofJson& currentPort, int channel);
    
    bool isValidIPAddress(std::string ip);
    
    ofxTextInputField oscInPortField, oscOutPortField, oscOutIPField;
    void setupTextInputFields();
    
    void disableAllTextInputFields();
    
    void onOSCInputPortEditied(string& message);
    void onOSCOutputPortEditied(string& message);
    void onOSCOutputIPEditied(string& message);
    
    

};
