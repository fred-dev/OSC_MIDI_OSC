#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    font.load("frabk.ttf", 14);
    settingsManager.loadSettings("MIDI_OSC_SETTINGS.json");
    appSettings = settingsManager.getSettings();
    midiManager.setup();
    oscManager.setup();
    ofBackground(255);

    activityMessage = "No messages received";

    midiInSetupMode = std::make_shared<MidiInSetupMode>(font, appSettings, colours);
	midiOutSetupMode = std::make_shared<MidiOutSetupMode>(font, appSettings, colours);
	oscInSetupMode = std::make_shared<OscInSetupMode>(font, appSettings, colours);
	oscOutSetupMode = std::make_shared<OscOutSetupMode>(font, appSettings, colours);
	conversionMode = std::make_shared<ConversionMode>(font, appSettings, colours);

	modeManager.setMode(conversionMode);
}

//--------------------------------------------------------------
void ofApp::update() {
    modeManager.update();
    oscManager.handleIncomingMessages();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetBackgroundColor(colours.background);
    modeManager.draw();
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
        
        ofLogVerbose() << "Button message received: " << msg.message;
        
        // Get the corresponding enum value from the map
        int buttonValue = buttonMessagesMap[msg.message];
        // Use a switch statement on the enum value
        switch (buttonValue) {
            case BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_IN:
                modeManager.setMode(midiInSetupMode);
                break;

            case BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_OUT:
                modeManager.setMode(midiOutSetupMode);
                break;

            case BTN_MSG_GOTOMODE_MODE_SETTING_OSC_IN:
                modeManager.setMode(oscInSetupMode);
                break;

            case BTN_MSG_GOTOMODE_MODE_SETTING_OSC_OUT:
                modeManager.setMode(oscOutSetupMode);
                break;

            case BTN_MSG_GOTOMODE_MODE_CONVERSION:
                modeManager.setMode(conversionMode);
                break;
                
            case BTN_MSG_MIDI_IN_PORT_SET:
                appSettings["midiInDevice"] =  appSettings["inPortLabel"].get<string>();
                appSettings["midiInDeviceByString"] =  true;
                settingsManager.saveSettings("MIDI_OSC_SETTINGS.json", appSettings);
                midiManager.close();
                midiManager.updateSettings();
                midiManager.setup();
                break;

            case BTN_MSG_MIDI_IN_CHANNEL_SET:
                settingsManager.saveSettings("MIDI_OSC_SETTINGS.json", appSettings);
                midiManager.updateSettings();
                break;

            case BTN_MSG_MIDI_OUT_PORT_SET:
                appSettings["midiOutDevice"] =  appSettings["outPortLabel"].get<string>();
                appSettings["midiOutDeviceByString"] =  true;
                settingsManager.saveSettings("MIDI_OSC_SETTINGS.json", appSettings);
                midiManager.close();
                midiManager.updateSettings();
                midiManager.setup();
                
                break;

            case BTN_MSG_MIDI_OUT_CHANNEL_SET:
                settingsManager.saveSettings("MIDI_OSC_SETTINGS.json", appSettings);
                midiManager.updateSettings();
                break;

            case BTN_MSG_OSC_IN_PORT_SET:
                oscManager.closeReceiver();
                settingsManager.saveSettings("MIDI_OSC_SETTINGS.json", appSettings);
                oscManager.updateSettings();
                oscManager.setupReceiver();

                break;

            case BTN_MSG_OST_OUT_PORT_SET:
                oscManager.closeSender();
                settingsManager.saveSettings("MIDI_OSC_SETTINGS.json", appSettings);
                oscManager.updateSettings();
                oscManager.setupSender();

                break;

            case BTN_MSG_OST_OUT_IP_SET:
                oscManager.closeSender();
                settingsManager.saveSettings("MIDI_OSC_SETTINGS.json", appSettings);
                oscManager.setupSender();
                break;

            
        }
    } else if (msg.message.substr(0, 3) != "BTN") {
        activityMessage = msg.message;
    }
}

//--------------------------------------------------------------
