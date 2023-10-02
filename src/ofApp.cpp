#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    font.load("Gaultier-Regular.ttf", 12);
    settingsManager.loadSettings("MIDI_OSC_SETTINGS.json");
    appSettings = settingsManager.getSettings();
    midiManager.setup();
    oscManager.setup();
    ofBackground(255);

    activityMessage = "No messages received";

    midiInSetupMode = std::make_shared<MidiInSetupMode>(font, appSettings);
	midiOutSetupMode = std::make_shared<MidiOutSetupMode>(font, appSettings);
	oscInSetupMode = std::make_shared<OscInSetupMode>(font, appSettings);
	oscOutSetupMode = std::make_shared<OscOutSetupMode>(font, appSettings);
	conversionMode = std::make_shared<ConversionMode>(font, appSettings);

	modeManager.setMode(conversionMode);
}

//--------------------------------------------------------------
void ofApp::update() {
    modeManager.update();
   
}

//--------------------------------------------------------------
void ofApp::draw() {
    modeManager.draw();
	ofDrawBitmapString(activityMessage, 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') {
		modeManager.setMode(midiInSetupMode);
	}
	if (key == '2') {
		modeManager.setMode(midiOutSetupMode);
	}
	if (key == '3') {
		modeManager.setMode(oscInSetupMode);
	}
	if (key == '4') {
		modeManager.setMode(oscOutSetupMode);
	}
	if (key == '5') {
		modeManager.setMode(conversionMode);
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
    if (msg.message.substr(0, 3) == "BTN" && buttonMessagesMap.find(msg.message) != buttonMessagesMap.end()) {
        // Get the corresponding enum value from the map
        int buttonValue = buttonMessagesMap[msg.message];
        // Use a switch statement on the enum value
        switch (buttonValue) {
            case BTN_MSG_MIDI_IN_PORT_SET:
                // Handle BTN_MSG_MIDI_IN_PORT_SET action
                break;

            case BTN_MSG_MIDI_IN_CHANNEL_SET:
                // Handle BTN_MSG_MIDI_IN_CHANNEL_SET action
                break;

            case BTN_MSG_MIDI_OUT_PORT_SET:
                // Handle BTN_MSG_MIDI_OUT_PORT_SET action
                break;

            case BTN_MSG_MIDI_OUT_CHANNEL_SET:
                // Handle BTN_MSG_MIDI_OUT_CHANNEL_SET action
                break;

            case BTN_MSG_OSC_IN_PORT_SET:
                // Handle BTN_MSG_OSC_IN_PORT_SET action
                break;

            case BTN_MSG_OST_OUT_PORT_SET:
                // Handle BTN_MSG_OSC_OUT_PORT_SET action
                break;

            case BTN_MSG_OST_OUT_IP_SET:

                break;

            case BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_IN:
                // Handle BTN_MSG_OSC_OUT_PORT_SET action
                break;

            case BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_OUT:
                // Handle BTN_MSG_CONVERSION_SET action
                break;

            case BTN_MSG_GOTOMODE_MODE_SETTING_OSC_IN:
                // Handle BTN_MSG_CONVERSION_SET action
                break;

            case BTN_MSG_GOTOMODE_MODE_SETTING_OSC_OUT:
                // Handle BTN_MSG_CONVERSION_SET action
                break;

            case BTN_MSG_GOTOMODE_MODE_CONVERSION:
                // Handle BTN_MSG_CONVERSION_SET action
                break;
        }
    } else if (msg.message.substr(0, 3) != "BTN") {
        activityMessage = msg.message;
    }
}

//--------------------------------------------------------------
