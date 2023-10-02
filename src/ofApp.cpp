#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
    settingsManager.loadSettings("MIDI_OSC_SETTINGS.json");
    appSettings = settingsManager.getSettings();
    midiManager.setup();
    oscManager.setup();
    ofBackground(255);
    
    activityMessage = "No messages received";
    setupTextInputFields();

    
}

//--------------------------------------------------------------
void ofApp::update() {
    oscManager.handleIncomingMessages();
}


//--------------------------------------------------------------
void ofApp::draw() {

    //operationmode switch
    switch (operationMode) {
        case MODE_SETTING_MIDI_IN:
            drawMidiSettings("Midi in settings", appSettings["allInPorts"], appSettings["inPortLabel"], appSettings["midiInChannel"]);
            break;
            
        case MODE_SETTING_MIDI_OUT:
            drawMidiSettings("Midi out settings", appSettings["allOutPorts"], appSettings["outPortLabel"], appSettings["midiOutChannel"]);
            break;
            
        case MODE_SETTING_OSC_IN:
            ofDrawBitmapString("OSC in settings", 10, 15);
            ofSetColor(0);
            ofRectangle(oscInPortField.bounds);
            ofNoFill();
            oscInPortField.draw();
            
            //draw the osc in port
            //ofDrawBitmapString("Osc in port: " + ofToString(appSettings["incomingPortOsc"]), 10, 30);

            //MODE_SETTING_OSC_IN
            break;
        case MODE_SETTING_OSC_OUT:
            ofDrawBitmapString("OSC out settings", 10, 15);
            ofSetColor(0);
            ofRectangle(oscOutPortField.bounds);
            ofNoFill();
            oscOutPortField.draw();
            ofRectangle(oscOutIPField.bounds);
            ofNoFill();
            oscOutIPField.draw();

            //MODE_SETTING_OSC_OUT
            break;
        case MODE_CONVERSION:
            ofSetColor(0);
            ofDrawBitmapString(activityMessage, 10, 15);
            ofDrawBitmapString("Midi input on port " + appSettings["inPortLabel"].get<string>(), 10, 30);
            ofDrawBitmapString("Midi output on port " + appSettings["outPortLabel"].get<string>(), 10, 45);
            ofDrawBitmapString("Osc input on port " + ofToString(appSettings["incomingPortOsc"]), 10, 60);
            ofDrawBitmapString("Osc output on port " + ofToString(appSettings["outGoingPortOsc"]), 10, 75);
            ofDrawBitmapString("Osc output to host " + ofToString(appSettings["outgoingIpOSC"]), 10, 90);
            break;
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    switch (key) {
        case '1':
            disableAllTextInputFields();
            operationMode = MODE_SETTING_MIDI_IN;
            break;
        case '2':
            disableAllTextInputFields();
            operationMode = MODE_SETTING_MIDI_OUT;
            break;
        case '3':
            disableAllTextInputFields();
            operationMode = MODE_SETTING_OSC_IN;
            oscInPortField.enable();
            
            break;
        case '4':
            disableAllTextInputFields();
            operationMode = MODE_SETTING_OSC_OUT;
            oscOutPortField.enable();
            oscOutIPField.enable();
            
            break;
        case '5':
            disableAllTextInputFields();
            operationMode = MODE_CONVERSION;
            break;
    }
    
    //operationmode switch
    switch (operationMode) {
        case MODE_SETTING_MIDI_IN:
            if (key == OF_KEY_DOWN) selectPort(appSettings["allInPorts"], appSettings["inPortLabel"], 1);
            if (key == OF_KEY_UP) selectPort(appSettings["allInPorts"], appSettings["inPortLabel"], -1);
            if (key == OF_KEY_LEFT) selectChannel(appSettings["midiInChannel"], -1);
            if (key == OF_KEY_RIGHT) selectChannel(appSettings["midiInChannel"], 1);
            
            break;
        case MODE_SETTING_MIDI_OUT:
            if (key == OF_KEY_DOWN) selectPort(appSettings["allOutPorts"], appSettings["outPortLabel"], 1);
            if (key == OF_KEY_UP) selectPort(appSettings["allOutPorts"], appSettings["outPortLabel"], -1);
            if (key == OF_KEY_LEFT) selectChannel(appSettings["midiOutChannel"], -1);
            if (key == OF_KEY_RIGHT) selectChannel(appSettings["midiOutChannel"], 1);
            break;
        case MODE_SETTING_OSC_IN:
            //MODE_SETTING_OSC_IN
            break;
        case MODE_SETTING_OSC_OUT:
            //MODE_SETTING_OSC_OUT
            break;
        case MODE_CONVERSION:
            break;
    }
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
    activityMessage = msg.message;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

// Helper function to handle port selection
void ofApp::selectPort(ofJson& ports, ofJson& currentPort, int direction) {
    for (int i = 0; i < ports.size(); i++) {
        if (ports[i] == currentPort) {
            int newIndex = ofClamp(i + direction, 0, ports.size() - 1);
            currentPort = ports[newIndex];
            break;
        }
    }
}

// Helper function to handle channel selection
void ofApp::selectChannel(ofJson& channel, int direction) {
    int newChannel = ofClamp(channel.get<int>() + direction, 1, MAX_MIDI_CHANNEL);
    channel = newChannel;
}

void ofApp::drawMidiSettings(const std::string& title, const ofJson& ports, const ofJson& currentPort, int channel) {
    // Draw the title
    ofDrawBitmapString(title, 10, 15);

    // Draw the list of ports and highlight the selected one
    for (int i = 0; i < ports.size(); i++) {
        ofPushStyle();
        if (ports[i] == currentPort) {
            ofSetColor(255, 0, 0);
        } else {
            ofSetColor(0);
        }
        ofDrawBitmapString(ports[i], 10, 30 + (i * 15));
        ofPopStyle();
    }

    // Draw the midi channel to the right of these messages
    ofSetColor(0);
    ofDrawBitmapString("Midi channel set to: " + ofToString(channel), 320, 30);
}

bool ofApp::isValidIPAddress(std::string ip){
    //check if the string is a alid IP address
//    struct sockaddr_in sa;
//    int result = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
//    return result != 0;
    
    return false;
}

void ofApp::setupTextInputFields(){

    oscInPortField.setup();
    oscInPortField.text = ofToString(appSettings["incomingPortOsc"]);
    oscInPortField.bounds.x = 10;
    oscInPortField.bounds.y = 30;
    oscInPortField.bounds.height = 15;
    oscInPortField.bounds.width = 188;
    ofAddListener(oscInPortField.onTextChange, this, &ofApp::onOSCInputPortEditied);

    
    oscOutPortField.setup();
    oscOutPortField.text = ofToString(appSettings["outGoingPortOsc"]);
    oscOutPortField.bounds.x = 10;
    oscOutPortField.bounds.y = 30;
    oscOutPortField.bounds.height = 15;
    oscOutPortField.bounds.width = 188;
    ofAddListener(oscOutPortField.onTextChange, this, &ofApp::onOSCOutputPortEditied);

    
    oscOutIPField.setup();
    oscOutIPField.text = appSettings["outgoingIpOSC"];
    oscOutIPField.bounds.x = 10;
    oscOutIPField.bounds.y = 45;
    oscOutIPField.bounds.height = 15;
    oscOutIPField.bounds.width = 188;
    ofAddListener(oscOutIPField.onTextChange, this, &ofApp::onOSCOutputIPEditied);

}

void ofApp::disableAllTextInputFields(){
    oscInPortField.disable();
    oscOutPortField.disable();
    oscOutIPField.disable();
}

void ofApp::onOSCInputPortEditied( string& message){
    
    ofLogNotice() << "onOSCInputPortEditied: " << message;
    
    
}
void ofApp::onOSCOutputPortEditied(string& message){
        
        ofLogNotice() << "onOSCOutputPortEditied: " << message;
}
void ofApp::onOSCOutputIPEditied(string& message){
    
    ofLogNotice() << "onOSCOutputIPEditied: " << message;
    
}
