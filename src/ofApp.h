#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxMidi.h"
#include "ofxGui.h"
#include "ofxDropdown.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

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
    
    
    
    ofxOscReceiver receiver;
    ofxMidiOut midiOut;
	string message;
    void newMidiMessage(ofxMidiMessage& eventArgs);
    stringstream text;
    
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    ofxOscSender oscSend;




    ofxPanel gui;
  
    ofxDropdown_<string> midiInputDropdown {"Midi_inputs"};
    ofxDropdown_<string> midiOutputDropdown {"Midi_outputs"};

    void changeMidiInput(string & input);
    void changeMidiOutput(string & ouput);
		
};
