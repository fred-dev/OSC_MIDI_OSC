#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
    settingsManager.loadSettings("MIDI_OSC_SETTINGS.json");    
    midiManager.setup();
    oscManager.setup();
    ofBackground(255);
    
}

//--------------------------------------------------------------
void ofApp::update() {
    oscManager.handleIncomingMessages();
}


//--------------------------------------------------------------
void ofApp::draw() {
    
    ofSetColor(0);
//    ofDrawBitmapString("Midi input on port " + midiIn.getName(), 10, 25);
//    ofDrawBitmapString("Midi output on port " + midiOut.getName(), 10, 40);
//    ofDrawBitmapString("Osc input on port " + ofToString(incomingPortOsc), 10, 55);
//    ofDrawBitmapString("Osc output on port " + ofToString(outGoingPortOsc), 10, 70);
//    ofDrawBitmapString("Osc output to host " + ofToString(outgoingIpOSC), 10, 85);
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

