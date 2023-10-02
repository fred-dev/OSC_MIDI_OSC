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
            //dra the list of midi in ports and highlight the selcted one
            ofDrawBitmapString("Midi in settings", 10, 15);

            for (int i = 0; i < appSettings["allInPorts"].size(); i++) {
                ofPushStyle();
                if (appSettings["allInPorts"][i] == appSettings["inPortLabel"]) {
                    ofSetColor(255, 0, 0);
                } else {
                    ofSetColor(0);
                }
                ofDrawBitmapString(appSettings["allInPorts"][i], 10, 30 + (i * 15));
                ofPopStyle();
            }
            
            //draw the midi in channel to right of these messages
            ofSetColor(0);
            ofDrawBitmapString("Midi channel set to: " + ofToString(appSettings["midiInChannel"]), 320, 30);
            
            
            //MODE_SETTING_MID_IN
            break;
        case MODE_SETTING_MIDI_OUT:
            ofDrawBitmapString("Midi out settings", 10, 15);

            for (int i = 0; i < appSettings["allOutPorts"].size(); i++) {
                ofPushStyle();
                if (appSettings["allOutPorts"][i] == appSettings["outPortLabel"]) {
                    ofSetColor(255, 0, 0);
                } else {
                    ofSetColor(0);
                }
                ofDrawBitmapString(appSettings["allOutPorts"][i], 10, 30 + (i * 15));
                ofPopStyle();
            }
            
            //draw the midi in channel to right of these messages
            ofSetColor(0);
            ofDrawBitmapString("Midi channel set to: " + ofToString(appSettings["midiOutChannel"]), 320, 30);
            //MODE_SETTING_MIDI_OUT
            break;
        case MODE_SETTING_OSC_IN:
            ofDrawBitmapString("OSC in settings", 10, 15);
            //draw the osc in port
            ofDrawBitmapString("Osc in port: " + ofToString(appSettings["incomingPortOsc"]), 10, 30);

            //MODE_SETTING_OSC_IN
            break;
        case MODE_SETTING_OSC_OUT:
            ofDrawBitmapString("OSC Out settings", 10, 15);
            ofDrawBitmapString("Osc in port: " + ofToString(appSettings["outGoingPortOsc"]), 10, 30);
            ofDrawBitmapString("Osc in port: " + ofToString(appSettings["outgoingIpOSC"]), 10, 45);

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
            operationMode = MODE_SETTING_MIDI_IN;
            break;
        case '2':
            operationMode = MODE_SETTING_MIDI_OUT;
            break;
        case '3':
            operationMode = MODE_SETTING_OSC_IN;
            break;
        case '4':
            operationMode = MODE_SETTING_OSC_OUT;
            break;
        case '5':
            operationMode = MODE_CONVERSION;
            break;
    }
    
    //operationmode switch
    switch (operationMode) {
        case MODE_SETTING_MIDI_IN:
            //MODE_SETTING_MID_IN
            //use the up and down keys to select the midi in port
            //first use the appSettings["inPortLabel"] to check whci of the ports are used in appSettings["allInPorts"] then incremener them as needed
            
            if (key == OF_KEY_DOWN) {
                //increment the selected port
                for (int i = 0; i < appSettings["allInPorts"].size(); i++) {
                    if (appSettings["allInPorts"][i] == appSettings["inPortLabel"]) {
                        if (i < appSettings["allInPorts"].size() - 1) {
                            appSettings["inPortLabel"] = appSettings["allInPorts"][i + 1];
                            break;
                        }
                    }
                }
            }
            if (key == OF_KEY_UP) {
                //decrement the selected port
                for (int i = 0; i < appSettings["allInPorts"].size(); i++) {
                    if (appSettings["allInPorts"][i] == appSettings["inPortLabel"]) {
                        if (i > 0) {
                            appSettings["inPortLabel"] = appSettings["allInPorts"][i - 1];
                            break;
                        }
                    }
                }
            }
            //use the left and right arrows to slect the midi in channel, get it from the settings first appSettings["midiInChannel"] it can only be 1 - 16
            if (key == OF_KEY_LEFT) {
                if (appSettings["midiInChannel"] > 1) {
                    appSettings["midiInChannel"] = appSettings["midiInChannel"].get<int>() - 1;
                }
            }
            
            if (key == OF_KEY_RIGHT) {
                if (appSettings["midiInChannel"] < 16) {
                    appSettings["midiInChannel"] = appSettings["midiInChannel"].get<int>() + 1;
                }
            }
            
          
            break;
        case MODE_SETTING_MIDI_OUT:
            //MODE_SETTING_MIDI_OUT
            
            if (key == OF_KEY_DOWN) {
                //increment the selected port
                for (int i = 0; i < appSettings["allOutPorts"].size(); i++) {
                    if (appSettings["allOutPorts"][i] == appSettings["outPortLabel"]) {
                        if (i < appSettings["allOutPorts"].size() - 1) {
                            appSettings["outPortLabel"] = appSettings["allOutPorts"][i + 1];
                            break;
                        }
                    }
                }
            }
            if (key == OF_KEY_UP) {
                //decrement the selected port
                for (int i = 0; i < appSettings["allOutPorts"].size(); i++) {
                    if (appSettings["allOutPorts"][i] == appSettings["outPortLabel"]) {
                        if (i > 0) {
                            appSettings["outPortLabel"] = appSettings["allOutPorts"][i - 1];
                            break;
                        }
                    }
                }
            }
            //use the left and right arrows to slect the midi in channel, get it from the settings first appSettings["midiInChannel"] it can only be 1 - 16
            if (key == OF_KEY_LEFT) {
                if (appSettings["midiOutChannel"] > 1) {
                    appSettings["midiOutChannel"] = appSettings["midiOutChannel"].get<int>() - 1;
                }
            }
            
            if (key == OF_KEY_RIGHT) {
                if (appSettings["midiOutChannel"] < 16) {
                    appSettings["midiOutChannel"] = appSettings["midiOutChannel"].get<int>() + 1;
                }
            }
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

