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

    midiInSetupMode = std::make_unique<MidiInSetupMode>(font, appSettings);
    midiOutSetupMode = std::make_unique<MidiOutSetupMode>(font, appSettings);
    oscInSetupMode = std::make_unique<OscInSetupMode>(font, appSettings);
    oscOutSetupMode = std::make_unique<OscOutSetupMode>(font, appSettings);
    conversionMode = std::make_unique<ConversionMode>(font, appSettings);

	modeManager.setMode(std::move(conversionMode));

}

//--------------------------------------------------------------
void ofApp::update() {
   
}

//--------------------------------------------------------------
void ofApp::draw() {
  
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
