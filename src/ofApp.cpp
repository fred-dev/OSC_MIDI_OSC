#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
   
  
    
   
    


    
    gui.setup("DROPDOWNS", "DropdownsSettings.json");
    gui.setPosition(20,20);
    
    midiInputDropdown.addListener(this, &ofApp::changeMidiInput);
    midiOutputDropdown.addListener(this, &ofApp::changeMidiOutput);
    
    
    
    std::vector allInPortNames = midiIn.getInPortList();
    std::vector allOutPortNames = midiIn.getInPortList();
    
    for(int i = 0; i < allInPortNames.size(); i++){
        midiInputDropdown.add(allInPortNames[i]);
    }
    for(int i = 0; i < allOutPortNames.size(); i++){
        midiOutputDropdown.add(allOutPortNames[i]);
    }
    
    gui.add(& midiInputDropdown);
    gui.add(& midiOutputDropdown);
    midiInputDropdown.enableCollapseOnSelection();
    midiInputDropdown.disableMultipleSelection();
    midiOutputDropdown.enableCollapseOnSelection();
    midiOutputDropdown.disableMultipleSelection();
    
    
    
}

//--------------------------------------------------------------
void ofApp::update() {

}



void ofApp::newMidiMessage(ofxMidiMessage & msg) {
    
}
//--------------------------------------------------------------
void ofApp::draw() {
    gui.draw();
    
    ofSetColor(0);
    ofDrawBitmapString(message, 10, 10);
    ofDrawBitmapString("Midi input on port " + midiIn.getName(), 10, 25);
    ofDrawBitmapString("Midi output on port " + midiOut.getName(), 10, 40);
    ofDrawBitmapString("Osc input on port " + ofToString(incomingPortOsc), 10, 55);
    ofDrawBitmapString("Osc output on port " + ofToString(outGoingPortOsc), 10, 70);
    ofDrawBitmapString("Osc output to host " + ofToString(outgoingIpOSC), 10, 85);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}


void ofApp::changeMidiInput(string & input){
    cout<<"Dropdowncallback: " + input <<endl;
    midiIn.closePort();
    midiIn.openPort(input);
    jsonSettings["midiInDevice"]=input;
    ofSavePrettyJson("MIDI_OSC_SETTINGS.json", jsonSettings);
}
void ofApp::changeMidiOutput(string & ouput){
    cout<<"Dropdowncallback: " + ouput <<endl;
    midiOut.closePort();
    midiOut.openPort(ouput);
    jsonSettings["midOutDevice"]=ouput;
    ofSavePrettyJson("MIDI_OSC_SETTINGS.json", jsonSettings);
}
