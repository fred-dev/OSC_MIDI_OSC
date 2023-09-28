#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //load a json settings file to an ofJson Object
    if (ofFile("MIDI_OSC_SETTINGS.json")) {
        ofFile jsonSettingsFile("MIDI_OSC_SETTINGS.json");
        jsonSettings = ofLoadJson(jsonSettingsFile);
    }
    if (!jsonSettings["Log_level"].is_null()) {
        ofSetLogLevel(jsonSettings["Log_level"]);
        ofLogVerbose() << "Log level set to " << jsonSettings["Log_level"] << endl;
    } else {
        ofSetLogLevel(OF_LOG_VERBOSE);
        ofLogVerbose() << "Log level set to OF_LOG_VERBOSE" << endl;
    }
#ifdef TARGET_OSX
    if (!jsonSettings["useVirtualPort"].is_null()) {
        useVirtualPort = jsonSettings["useVirtualPort"];
        ofLogVerbose()<<"useVirtualPort set to "<<useVirtualPort<<endl;
    } else {
        useVirtualPort = true;
    }
#else
    useVirtualPort = false;
#endif
    //set the incomingPortOsc from the jsonSettings
    if (!jsonSettings["incomingPortOsc"].is_null()) {
        incomingPortOsc = jsonSettings["incomingPortOsc"];
        ofLogVerbose()<<"incomingPortOsc set to "<<incomingPortOsc<<endl;
    } else {
        incomingPortOsc = 12345;
    }
    if (!jsonSettings["outGoingPortOsc"].is_null()) {
        outGoingPortOsc = jsonSettings["outGoingPortOsc"];
        ofLogVerbose()<<"outGoingPortOsc set to "<<outGoingPortOsc<<endl;
    }
    else {
        outGoingPortOsc = 1234;
    }
    
    if (!jsonSettings["outgoingIpOSC"].is_null()) {
        outgoingIpOSC = jsonSettings["outgoingIpOSC"];
        ofLogVerbose()<<"outgoingIpOSC set to "<<outgoingIpOSC<<endl;
    }
    else {
        outgoingIpOSC = "127.0.0.1";
    }
    
    if (!jsonSettings["midiInDevice"].is_null()) {
        if (jsonSettings["midiInDevice"].is_number()) {
            midiInDeviceByString = false;
            midiInDeviceNum = jsonSettings["midiInDevice"];
            ofLogVerbose() << "midiInDevice set to " << midiInDeviceNum << endl;
        } else if (jsonSettings["midiInDevice"].is_string()) {
            midiInDeviceByString = true;
            midiInDeviceName = jsonSettings["midiInDevice"];
            ofLogVerbose() << "midiInDevice set to " << midiInDeviceName << endl;
        }
    }
    else {
        midiInDeviceByString = false;
        midiInDeviceNum = 0;
        ofLogVerbose() << "midiInDevice set to " << midiInDeviceNum << endl;
    }
    
    if (!jsonSettings["midiOutDevice"].is_null()) {
        if (jsonSettings["midiOutDevice"].is_number()) {
            midiOutDeviceByString = false;
            midiOutDeviceNum = jsonSettings["midiOutDevice"];
            ofLogVerbose() << "midiOutDevice set to " << midiOutDeviceNum << endl;
        } else if (jsonSettings["midiOutDevice"].is_string()) {
            midiOutDeviceByString = true;
            midiOutDeviceName = jsonSettings["midiOutDevice"];
            ofLogVerbose() << "midiOutDevice set to " << midiOutDeviceName << endl;
        }
    } else {
        midiOutDeviceByString = false;
        midiOutDeviceNum = 0;
        ofLogVerbose() << "midiInDevice set to " << midiOutDeviceNum << endl;
    }
    
    if (!jsonSettings["midiOutChannel"].is_null()) {
        midiOutChannel = jsonSettings["midiOutChannel"];
        ofLogVerbose() << "midiOutChannel set to " << midiOutChannel << endl;
    } else {
        midiOutChannel = 1;
    }
    if (!jsonSettings["midiInChannel"].is_null()) {
        midiInChannel = jsonSettings["midiInChannel"];
        ofLogVerbose() << "midiInChannel set to " << midiInChannel << endl;
    } else {
        midiInChannel = 1;
    }
    if (!jsonSettings["frameRate"].is_null()) {
        frameRate = jsonSettings["frameRate"];
        ofLogVerbose()<<"frameRate set to "<<frameRate<<endl;
    }
    else {
        frameRate = 25;
    }
    
    
    ofSetFrameRate(frameRate);
    
    //if we are on OSX we need to set the midi port to virtual
#ifdef TARGET_OSX
    if(useVirtualPort){
        midiOut.openVirtualPort("OSC_MIDI_OSC_OUT");
        midiIn.openVirtualPort("OSC_MIDI_OSC_IN");
        ofLogVerbose() << "Midi In Device set to OSC_MIDI_OSC_IN - Virtual port"  << endl;
        ofLogVerbose() << "Midi Out Device set to OSC_MIDI_OSC_OUT - Virtual port" << endl;
    }
    //if we are on windows we need to set the midi port to the selected port
#endif
    if(!useVirtualPort){
        if (midiOutDeviceByString) {
            midiIn.openPort(midiInDeviceName);
        } else {
            midiIn.openPort(midiInDeviceNum);
        }
        ofLogVerbose() << "Midi In Device initialised and set to port: " << midiIn.getPort() << " With name: "<<  midiIn.getName() << endl;
        if (midiOutDeviceByString) {
            midiOut.openPort(midiOutDeviceName);
        } else {
            midiOut.openPort(midiOutDeviceNum);
        }
        ofLogVerbose() << "Midi Out Device initialised and set to port: " << midiOut.getPort() << " With name: " << midiOut.getName() << endl;
    }
    
    
    
    midiIn.listInPorts();
    midiOut.listOutPorts();
    //save a list of midi in ports to the json file
    jsonSettings["midiInPorts"] = midiIn.getInPortList();
    //save a list of midi out ports to the json file
    jsonSettings["midiOutPorts"] = midiOut.getOutPortList();
    //save the json file
    ofSavePrettyJson("MIDI_OSC_SETTINGS.json", jsonSettings);
    
    midiIn.ignoreTypes(false, false,false);
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
                midiOut.sendNoteOn(midiOutChannel,m.getArgAsInt32(0),m.getArgAsInt32(1));
                message ="Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity "+ ofToString(m.getArgAsInt32(1));
                ofLogVerbose()<<message<<endl;
            }
            
            if (m.getNumArgs()==1) {
                midiOut.sendNoteOn(midiOutChannel, m.getArgAsInt32(0));
                message ="Sending note on: Note ID " + ofToString(m.getArgAsInt32(0)) + " With Velocity "+ ofToString(64);
                ofLogVerbose()<<message<<endl;
            }
        }
        
        if(m.getAddress() == "/noteOff"){
            midiOut.sendNoteOff(midiOutChannel, m.getArgAsInt32(0));
            message ="Sending note off Note ID " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/cc"){
            midiOut.sendControlChange(midiOutChannel, m.getArgAsInt32(0), m.getArgAsInt32(1));
            message ="Sending cc Controller ID " + ofToString(m.getArgAsInt32(0)) + " Controller value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/ProgramChange"){
            midiOut.sendProgramChange(midiOutChannel, m.getArgAsInt32(0));
            message ="Sending program change ID: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/PitchBend"){
            midiOut.sendPitchBend(midiOutChannel, m.getArgAsInt32(0));
            message ="Sending pitch bend value: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/Aftertouch"){
            midiOut.sendAftertouch(midiOutChannel, m.getArgAsInt32(0));
            message ="Sending aftertouch Value: " + ofToString(m.getArgAsInt32(0));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/PolyAftertouch"){
            midiOut.sendPolyAftertouch(midiOutChannel, m.getArgAsInt32(0), m.getArgAsInt32(1));
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        
        if(m.getAddress() == "/MMCCommand/stop"){
            buildSysExMMCMessage(0x01);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/MMCCommand/play"){
            buildSysExMMCMessage(0x02);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/MMCCommand/forward"){
            buildSysExMMCMessage(0x04);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/MMCCommand/rewind"){
            buildSysExMMCMessage(0x05);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/MMCCommand/punchIn"){
            buildSysExMMCMessage(0x06);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/MMCCommand/punchOut"){
            buildSysExMMCMessage(0x07);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/MMCCommand/recordPause"){
            buildSysExMMCMessage(0x08);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
        
        if(m.getAddress() == "/MMCCommand/pause"){
            buildSysExMMCMessage(0x09);
            midiOut.sendMidiBytes(sysexMMCMsg);
            message ="Sending poly aftertouch Note: " + ofToString(m.getArgAsInt32(0)) + " value " + ofToString(m.getArgAsInt32(1));
            ofLogVerbose()<<message<<endl;
        }
    }
}


void ofApp::buildSysExMMCMessage(char ID) {
    sysexMMCMsg.clear();
    sysexMMCMsg.push_back(MIDI_SYSEX);
    sysexMMCMsg.push_back(0x7F);
    sysexMMCMsg.push_back(0x7F);
    sysexMMCMsg.push_back(0x06);
    sysexMMCMsg.push_back(ID);
    sysexMMCMsg.push_back(MIDI_SYSEX_END);
    
}


void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    midiMessage=msg;
    if (midiMessage.channel == midiInChannel) {
        if (midiMessage.status == MIDI_SYSEX) {
            ofLogVerbose() << "Sysex Message" << endl;
            ofLogVerbose() << "Message Size " + ofToString(midiMessage.bytes.size()) << endl;
            ofxOscMessage m;
            
            if (midiMessage.bytes[4] == 0x01) {
                m.setAddress("/MMCCommand/stop");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Stop";
            }
            if (midiMessage.bytes[4] == 0x02) {
                m.setAddress("/MMCCommand/play");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Play";
            }
            if (midiMessage.bytes[4] == 0x04) {
                m.setAddress("/MMCCommand/forward");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Fast forward";
            }
            if (midiMessage.bytes[4] == 0x05) {
                m.setAddress("/MMCCommand/rewind");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Rewind";
            }
            if (midiMessage.bytes[4] == 0x06) {
                m.setAddress("/MMCCommand/punchIn");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Pucnh in";
            }
            if (midiMessage.bytes[4] == 0x07) {
                m.setAddress("/MMCCommand/punchOut");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Puch Out";
            }
            if (midiMessage.bytes[4] == 0x08) {
                m.setAddress("/MMCCommand/recordPause");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Record Pause";
            }
            if (midiMessage.bytes[4] == 0x09) {
                m.setAddress("/MMCCommand/pause");
                m.addIntArg(0);
                message = "Received Midi Machine Control message: " + ofToString(midiMessage.pitch) + " Command: Pause";
            }
            
            oscSend.sendMessage(m);
            
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_NOTE_ON) {
            ofxOscMessage m;
            m.setAddress("/noteOn");
            m.addIntArg(midiMessage.pitch);
            m.addIntArg(midiMessage.velocity);
            oscSend.sendMessage(m);
            message = "Received Note on Note ID: " + ofToString(midiMessage.pitch) + " With Velocity " + ofToString(midiMessage.velocity);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_NOTE_OFF) {
            ofxOscMessage m;
            m.setAddress("/noteOff");
            m.addIntArg(midiMessage.pitch);
            oscSend.sendMessage(m);
            message = "Received Note off Note ID: " + ofToString(midiMessage.pitch);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_CONTROL_CHANGE) {
            ofxOscMessage m;
            m.setAddress("/cc");
            m.addIntArg(midiMessage.control);
            m.addIntArg(midiMessage.value);
            oscSend.sendMessage(m);
            message = "Received Controller ID: " + ofToString(midiMessage.control) + "  Value: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_TIME_CODE) {
            ofxOscMessage m;
            m.setAddress("/MTC");
            m.addIntArg(midiMessage.deltatime);
            oscSend.sendMessage(m);
            message = "Received MTC: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_PROGRAM_CHANGE) {
            ofxOscMessage m;
            m.setAddress("/ProgramChange");
            m.addIntArg(midiMessage.value);
            oscSend.sendMessage(m);
            message = "Received Program Change ID: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_PITCH_BEND) {
            ofxOscMessage m;
            m.setAddress("/PitchBend");
            m.addIntArg(midiMessage.value);
            oscSend.sendMessage(m);
            message = "Received pitch bend Value: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_AFTERTOUCH) {
            ofxOscMessage m;
            m.setAddress("/Aftertouch");
            m.addIntArg(midiMessage.value);
            oscSend.sendMessage(m);
            message = "Received Aftertouch Value: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
        
        if (midiMessage.status == MIDI_POLY_AFTERTOUCH) {
            ofxOscMessage m;
            m.setAddress("/PolyAftertouch");
            m.addIntArg(midiMessage.value);
            m.addIntArg(midiMessage.pitch);
            oscSend.sendMessage(m);
            message = "Received Poly Aftertouch Pitch: " + ofToString(midiMessage.pitch) + " Value: " + ofToString(midiMessage.value);
            ofLogVerbose() << message << endl;
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    ofDrawBitmapString(message,10,10);
    ofDrawBitmapString("Midi input on port " + midiIn.getName(), 10, 25);
    ofDrawBitmapString("Midi output on port " + midiOut.getName(), 10, 40);
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
