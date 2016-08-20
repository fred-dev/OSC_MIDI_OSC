#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    if (xmlSettings.loadFile("MIDI_OSC_SETTINGS.xml")) {
        ofLogVerbose()<<"XML loaded"<<endl;
    }
    
    incomingPortOsc = xmlSettings.getValue("incomingPortOsc", 12345);
    outGoingPortOsc	= xmlSettings.getValue("outGoingPortOsc", 12344);
    incomingPortMidi= xmlSettings.getValue("incomingPortMidi", 2);
    outGoingPortMidi= xmlSettings.getValue("outGoingPortMidi", 1);
    midiOutChannel=   xmlSettings.getValue("midiOutChannel", 1);
    outgoingIpOSC=    xmlSettings.getValue("outgoingIpOSC", "127.0.0.1");
    
    
    
    
    midiOut.listPorts();
    midiOut.openPort(outGoingPortMidi);
    
    midiIn.listPorts();
    midiIn.openPort(incomingPortMidi);
    midiIn.addListener(this);
    
    oscSend.setup(outgoingIpOSC, outGoingPortOsc);
    receiver.setup(incomingPortOsc);
    message="No messages yet";
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/noteOn"){
            if (m.getNumArgs()>1) {
                midiOut.sendNoteOn(1,m.getArgAsInt32(0),m.getArgAsInt32(1));
                message ="Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity "+ ofToString(m.getArgAsInt32(1));
                ofLogVerbose()<<message<<endl;
            }
            
            if (m.getNumArgs()==1) {
                midiOut.sendNoteOn(1,m.getArgAsInt32(0));
                message ="Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity "+ ofToString(64);
                ofLogVerbose()<<message<<endl;
            }
        }
        
        if(m.getAddress() == "/noteOff"){
            midiOut.sendNoteOff(1,m.getArgAsInt32(0));
            message ="Sending note off Note ID " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/cc"){
            midiOut.sendControlChange(1,m.getArgAsInt32(0),m.getArgAsInt32(1));
            message ="Sending cc Controller ID " + ofToString(m.getArgAsInt32(0)) + " Controller value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/ProgramChange"){
            midiOut.sendProgramChange(1,m.getArgAsInt32(0));
            message ="Sending program change ID: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/PitchBend"){
            midiOut.sendPitchBend(1, m.getArgAsInt32(0));
            message ="Sending pitch bend value: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/Aftertouch"){
            midiOut.sendAftertouch(1, m.getArgAsInt32(0));
            message ="Sending aftertouch Value: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/PolyAftertouch"){
            midiOut.sendPolyAftertouch(1,m.getArgAsInt32(0),m.getArgAsInt32(1));
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
    }
}
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    
    midiMessage = msg;
    
    if (midiMessage.status==MIDI_NOTE_ON) {
        ofxOscMessage m;
        m.setAddress("/noteOn");
        m.addIntArg(midiMessage.pitch);
        m.addIntArg(midiMessage.velocity);
        oscSend.sendMessage(m);
        message ="Received Note on Note ID: " + ofToString(midiMessage.pitch) + " With Velocity "+ ofToString(midiMessage.velocity);
        ofLogVerbose()<<message<<endl;
    }
    
    if (midiMessage.status==MIDI_NOTE_OFF) {
        ofxOscMessage m;
        m.setAddress("/noteOff");
        m.addIntArg(midiMessage.pitch);
        oscSend.sendMessage(m);
        message ="Received Note off Note ID: " + ofToString(midiMessage.pitch);
        ofLogVerbose()<<message<<endl;
    }
    
    if (midiMessage.status==MIDI_CONTROL_CHANGE) {
        ofxOscMessage m;
        m.setAddress("/cc");
        m.addIntArg(midiMessage.control);
        m.addIntArg(midiMessage.value);
        oscSend.sendMessage(m);
        message ="Received Controller ID: " + ofToString(midiMessage.control) + "  Value: " + ofToString(midiMessage.value);
        ofLogVerbose()<<message<<endl;
    }
    
    if (midiMessage.status==MIDI_TIME_CODE) {
        ofxOscMessage m;
        m.setAddress("/MTC");
        m.addIntArg(midiMessage.deltatime);
        oscSend.sendMessage(m);
        message ="Received MTC: " + ofToString(midiMessage.value);
        ofLogVerbose()<<message<<endl;
    }
    
    if (midiMessage.status==MIDI_PROGRAM_CHANGE) {
        ofxOscMessage m;
        m.setAddress("/ProgramChange");
        m.addIntArg(midiMessage.value);
        oscSend.sendMessage(m);
        message ="Received Program Change ID: " + ofToString(midiMessage.value);
        ofLogVerbose()<<message<<endl;
    }
    
    if (midiMessage.status==MIDI_PITCH_BEND) {
        ofxOscMessage m;
        m.setAddress("/PitchBend");
        m.addIntArg(midiMessage.value);
        oscSend.sendMessage(m);
        message ="Received pitch bend Value: " + ofToString(midiMessage.value);
        ofLogVerbose()<<message<<endl;
    }
    
    if (midiMessage.status==MIDI_AFTERTOUCH) {
        ofxOscMessage m;
        m.setAddress("/Aftertouch");
        m.addIntArg(midiMessage.value);
        oscSend.sendMessage(m);
        message ="Received Aftertouch Value: " + ofToString(midiMessage.value);
        ofLogVerbose()<<message<<endl;
    }
    
    if (midiMessage.status==MIDI_POLY_AFTERTOUCH) {
        ofxOscMessage m;
        m.setAddress("/PolyAftertouch");
        m.addIntArg(midiMessage.value);
        m.addIntArg(midiMessage.pitch);
        oscSend.sendMessage(m);
        message ="Received Poly Aftertouch Pitch: " + ofToString(midiMessage.pitch) + " Value: " + ofToString(midiMessage.value);
        ofLogVerbose()<<message<<endl;
    }
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    ofDrawBitmapString(message,10,10);
    ofDrawBitmapString("Midi input on port " + ofToString(incomingPortMidi), 10, 25);
    ofDrawBitmapString("Midi output on port " + ofToString(incomingPortMidi), 10, 40);
    ofDrawBitmapString("Osc input on port " + ofToString(incomingPortOsc), 10, 55);
    ofDrawBitmapString("Osc output on port " + ofToString(outGoingPortOsc), 10, 70);
    ofDrawBitmapString("Osc output to host " + ofToString(outgoingIpOSC), 10, 85);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
