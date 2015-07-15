#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    xmlSettings.loadFile("MIDI_OSC_SETTINGS.xml");
    incomingPortOsc = xmlSettings.getValue("incomingPortOsc", 12345);
    outGoingPortOsc	= xmlSettings.getValue("outGoingPortOsc", 12344);
    incomingPortMidi= xmlSettings.getValue("incomingPortMidi", 2);
    outGoingPortMidi= xmlSettings.getValue("outGoingPortMidi", 2);
    outgoingIpOSC   = xmlSettings.getValue("outgoingIpOSC", "127.0.0.1");
  

	ofSetVerticalSync(true);
	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	// print the available output ports to the console
	midiOut.listPorts(); // via instance
	//ofxMidiOut::listPorts(); // via static too
	
	// connect
	midiOut.openPort(outGoingPortMidi);	// by number
	//midiOut.openPort("IAC Driver Pure Data In");	// by name
	//midiOut.openVirtualPort("ofxMidiOut");		// open a virtual port
	
	receiver.setup(incomingPortOsc);
	message="No messages yet";
    
    midiIn.openPort(incomingPortMidi);
	midiIn.addListener(this);
    oscSend.setup(outgoingIpOSC, outGoingPortOsc);
    
}

//--------------------------------------------------------------
void ofApp::update(){
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/noteOn"){
			// both the arguments are int32's
			
				midiOut.sendNoteOn(1,m.getArgAsInt32(0));
				message ="Sending noteOff Note ID " + ofToString(m.getArgAsInt32(0));
				cout<<message<<endl;
			
		}
		if(m.getAddress() == "/noteOff"){
			// both the arguments are int32's
			
				midiOut.sendNoteOn(1,m.getArgAsInt32(0));
			message ="Sending noteOff Note ID " + ofToString(m.getArgAsInt32(0));
			cout<<message<<endl;
		}
		if(m.getAddress() == "/cc"){
			// both the arguments are int32's
			
				midiOut.sendControlChange(1,m.getArgAsInt32(0),m.getArgAsInt32(1));
		message ="Sending cc Controller ID " + ofToString(m.getArgAsInt32(0)) + " Controller value " + ofToString(m.getArgAsInt32(1));
		cout<<message<<endl;
		}
	}
}
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
	
     midiMessage = msg;
    if (midiMessage.pitch!=0 && midiMessage.velocity!=0) {
        ofxOscMessage m;
        m.setAddress("/noteOn");
        m.addIntArg(midiMessage.pitch);
        oscSend.sendMessage(m);
        message ="Received Note on Note: " + ofToString(midiMessage.pitch);
		cout<<message<<endl;
    }
    if (midiMessage.pitch!=0 && midiMessage.velocity==0) {
        ofxOscMessage m;
        m.setAddress("/noteOff");
        m.addIntArg(midiMessage.pitch);
        oscSend.sendMessage(m);
        message ="Received Note off Note: " + ofToString(midiMessage.pitch);
		cout<<message<<endl;
    }
    if (midiMessage.control!=0) {
        ofxOscMessage m;
        m.setAddress("/cc");
        m.addIntArg(midiMessage.control);
        m.addIntArg(midiMessage.value);
        oscSend.sendMessage(m);
        message ="Received cc Controller ID " + ofToString(midiMessage.control) + " Controller value " + ofToString(midiMessage.value);
		cout<<message<<endl;
    }
    
    
    // make a copy of the latest message
   
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
