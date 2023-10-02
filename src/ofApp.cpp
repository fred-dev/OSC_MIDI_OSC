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
    setupTextInputFields();
}

//--------------------------------------------------------------
void ofApp::update() {
    switch (operationMode) {
        case MODE_SETTING_MIDI_IN:
            updateMidiPortInSetupMode();
            break;

        case MODE_SETTING_MIDI_OUT:
            updateMidiPortOutSetupMode();
            break;

        case MODE_SETTING_OSC_IN:
            updateOSCInSetupMode();
            break;

        case MODE_SETTING_OSC_OUT:
            updateOSCOutSetupMode();
            break;

        case MODE_CONVERSION:
            updateConversionMode();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    //operationmode switch
    switch (operationMode) {
        case MODE_SETTING_MIDI_IN:
            drawMidiPortInSetupMode();
            break;

        case MODE_SETTING_MIDI_OUT:
            drawMidiPortOutSetupMode();
            break;

        case MODE_SETTING_OSC_IN:
            drawOSCInSetupMode();
            break;

        case MODE_SETTING_OSC_OUT:
            drawOSCOutSetupMode();
            break;

        case MODE_CONVERSION:
            drawConversionMode();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case '1':
            goToMode(MODE_SETTING_MIDI_IN);
            break;

        case '2':
            goToMode(MODE_SETTING_MIDI_OUT);
            break;

        case '3':
            goToMode(MODE_SETTING_OSC_IN);
            break;

        case '4':
            goToMode(MODE_SETTING_OSC_OUT);
            break;

        case '5':
            goToMode(MODE_CONVERSION);
            break;
    }

    //operationmode switch
    switch (operationMode) {
        case MODE_SETTING_MIDI_IN:

            if (key == OF_KEY_DOWN) {
                selectPort(appSettings["allInPorts"], appSettings["inPortLabel"], 1);
            }

            if (key == OF_KEY_UP) {
                selectPort(appSettings["allInPorts"], appSettings["inPortLabel"], -1);
            }

            if (key == OF_KEY_LEFT) {
                selectChannel(appSettings["midiInChannel"], -1);
            }

            if (key == OF_KEY_RIGHT) {
                selectChannel(appSettings["midiInChannel"], 1);
            }

            break;

        case MODE_SETTING_MIDI_OUT:

            if (key == OF_KEY_DOWN) {
                selectPort(appSettings["allOutPorts"], appSettings["outPortLabel"], 1);
            }

            if (key == OF_KEY_UP) {
                selectPort(appSettings["allOutPorts"], appSettings["outPortLabel"], -1);
            }

            if (key == OF_KEY_LEFT) {
                selectChannel(appSettings["midiOutChannel"], -1);
            }

            if (key == OF_KEY_RIGHT) {
                selectChannel(appSettings["midiOutChannel"], 1);
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
    font.drawString(title, 10, 15);

    // Draw the list of ports and highlight the selected one
    for (int i = 0; i < ports.size(); i++) {
        ofPushStyle();

        if (ports[i] == currentPort) {
            ofSetColor(255, 0, 0);
        } else {
            ofSetColor(0);
        }

        font.drawString(ports[i], 10, 30 + (i * 15));
        ofPopStyle();
    }

    // Draw the midi channel to the right of these messages
    ofSetColor(0);
    font.drawString("Midi channel set to: " + ofToString(channel), 320, 30);
}

bool ofApp::isValidIPAddress(std::string ip) {
    //check if the string is a alid IP address
//    struct sockaddr_in sa;
//    int result = inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
//    return result != 0;

    return false;
}

void ofApp::setupTextInputFields() {
    oscInPortField.setup();
    oscInPortField.text = ofToString(appSettings["incomingPortOsc"]);
    oscInPortField.bounds.x = 10;
    oscInPortField.bounds.y = 30;
    oscInPortField.bounds.height = 15;
    oscInPortField.bounds.width = 188;
    oscInPortField.setFont(font);


    ofAddListener(oscInPortField.onTextChange, this, &ofApp::onOSCInputPortEditied);


    oscOutPortField.setup();
    oscOutPortField.text = ofToString(appSettings["outGoingPortOsc"]);
    oscOutPortField.bounds.x = 10;
    oscOutPortField.bounds.y = 30;
    oscOutPortField.bounds.height = 15;
    oscOutPortField.bounds.width = 188;
    oscOutPortField.setFont(font);


    ofAddListener(oscOutPortField.onTextChange, this, &ofApp::onOSCOutputPortEditied);


    oscOutIPField.setup();
    oscOutIPField.text = appSettings["outgoingIpOSC"];
    oscOutIPField.bounds.x = 10;
    oscOutIPField.bounds.y = 45;
    oscOutIPField.bounds.height = 15;
    oscOutIPField.bounds.width = 188;
    oscOutIPField.setFont(font);

    ofAddListener(oscOutIPField.onTextChange, this, &ofApp::onOSCOutputIPEditied);
}

void ofApp::disableAllTextInputFields() {
    oscInPortField.disable();
    oscOutPortField.disable();
    oscOutIPField.disable();
}

void ofApp::onOSCInputPortEditied(string& message) {
    ofLogNotice() << "onOSCInputPortEditied: " << message;
}

void ofApp::onOSCOutputPortEditied(string& message) {
    ofLogNotice() << "onOSCOutputPortEditied: " << message;
}

void ofApp::onOSCOutputIPEditied(string& message) {
    ofLogNotice() << "onOSCOutputIPEditied: " << message;
}

void ofApp::setupMidPortOutSetupMode() {
    saveMidiOutPortSettings.enableAllEvents();
    saveMidiOutChannelSettings.enableAllEvents();
    GoToConversionMode.enableAllEvents();
}

void ofApp::drawMidiPortOutSetupMode() {
    drawMidiSettings("Midi out settings", appSettings["allOutPorts"], appSettings["outPortLabel"], appSettings["midiOutChannel"]);
}

void ofApp::updateMidiPortOutSetupMode() {
}

void ofApp::exitMidiPortOutSetupMode() {
    saveMidiOutPortSettings.disableAllEvents();
    saveMidiOutChannelSettings.disableAllEvents();
    GoToConversionMode.disableAllEvents();
}

void ofApp::setupMidPortInSetupMode() {
    saveMidiInPortSettings.enableAllEvents();
    saveMidiInChannelSettings.enableAllEvents();
    GoToConversionMode.enableAllEvents();
}

void ofApp::drawMidiPortInSetupMode() {
    drawMidiSettings("Midi in settings", appSettings["allInPorts"], appSettings["inPortLabel"], appSettings["midiInChannel"]);
}

void ofApp::updateMidiPortInSetupMode() {
}

void ofApp::exitMidiPortInSetupMode() {
    saveMidiInPortSettings.disableAllEvents();
    saveMidiInChannelSettings.disableAllEvents();
    GoToConversionMode.disableAllEvents();
}

void ofApp::setupOSCInSetupMode() {
    oscInPortField.enable();
    saveOSCInPortSettings.enableAllEvents();
    GoToConversionMode.enableAllEvents();
}

void ofApp::drawOSCInSetupMode() {
    font.drawString("OSC in settings", 10, 15);
    ofSetColor(0);
    ofRectangle(oscInPortField.bounds);
    ofNoFill();
    oscInPortField.draw();
}

void ofApp::updateOSCInSetupMode() {
}

void ofApp::exitOSCInSetupMode() {
    oscInPortField.disable();
    saveOSCInPortSettings.disableAllEvents();
    GoToConversionMode.disableAllEvents();
}

void ofApp::setupOSCOutSetupMode() {
    oscOutPortField.enable();
    oscOutIPField.enable();
    saveOSCOutPortSettings.enableAllEvents();
    saveOSCOutIptSettings.enableAllEvents();
    GoToConversionMode.enableAllEvents();
}

void ofApp::drawOSCOutSetupMode() {
    font.drawString("OSC out settings", 10, 15);
    ofSetColor(0);
    ofRectangle(oscOutPortField.bounds);
    ofNoFill();
    oscOutPortField.draw();
    ofRectangle(oscOutIPField.bounds);
    ofNoFill();
    oscOutIPField.draw();
}

void ofApp::updateOSCOutSetupMode() {
}

void ofApp::exitOSCOutSetupMode() {
    oscOutPortField.disable();
    oscOutIPField.disable();
    saveOSCOutPortSettings.disableAllEvents();
    saveOSCOutIptSettings.disableAllEvents();
    GoToConversionMode.disableAllEvents();
}

void ofApp::setupConversionMode() {
    goToMidiOutSetMode.enableAllEvents();
    goToMidiInSetMode.enableAllEvents();
    gotToOSCOutSetMode.enableAllEvents();
    goToOSCInSetMode.enableAllEvents();
}

void ofApp::drawConversionMode() {
    ofSetColor(0);
    font.drawString(activityMessage, 10, 15);
    font.drawString("Midi input on port " + appSettings["inPortLabel"].get<string>(), 10, 30);
    font.drawString("Midi output on port " + appSettings["outPortLabel"].get<string>(), 10, 45);
    font.drawString("Osc input on port " + ofToString(appSettings["incomingPortOsc"]), 10, 60);
    font.drawString("Osc output on port " + ofToString(appSettings["outGoingPortOsc"]), 10, 75);
    font.drawString("Osc output to host " + ofToString(appSettings["outgoingIpOSC"]), 10, 90);
}

void ofApp::updateConversionMode() {
    oscManager.handleIncomingMessages();
}

void ofApp::exitConversionMode() {
    goToMidiOutSetMode.disableAllEvents();
    goToMidiInSetMode.disableAllEvents();
    gotToOSCOutSetMode.disableAllEvents();
    goToOSCInSetMode.disableAllEvents();
}

void ofApp::goToMode(int mode) {
    exitAllModes();
    switch (mode) {
        case MODE_SETTING_MIDI_IN:
            setupMidPortInSetupMode();
            break;

        case MODE_SETTING_MIDI_OUT:
            setupMidPortOutSetupMode();
            break;

        case MODE_SETTING_OSC_IN:
            setupOSCInSetupMode();
            break;

        case MODE_SETTING_OSC_OUT:
            setupOSCOutSetupMode();
            break;

        case MODE_CONVERSION:
            setupConversionMode();
            break;
    }
    operationMode = mode;
}

void ofApp::exitAllModes() {
    exitMidiPortOutSetupMode();
    exitMidiPortInSetupMode();
    exitOSCInSetupMode();
    exitOSCOutSetupMode();
    exitConversionMode();
}

void ofApp::setupAllButtons() {
    goToMidiOutSetMode.setup("Midi out setup", "BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_OUT");
    goToMidiOutSetMode.set(200, 200, 200, 20);
    goToMidiOutSetMode.disableAllEvents();

    goToMidiInSetMode.setup("Midi in setup", "BTN_MSG_GOTOMODE_MODE_SETTING_MIDI_IN");
    goToMidiInSetMode.set(200, 200, 200, 20);
    goToMidiInSetMode.disableAllEvents();

    gotToOSCOutSetMode.setup("OSC out setup", "BTN_MSG_GOTOMODE_MODE_SETTING_OSC_OUT");
    gotToOSCOutSetMode.set(200, 200, 200, 20);
    gotToOSCOutSetMode.disableAllEvents();

    goToOSCInSetMode.setup("OSC in setup", "BTN_MSG_GOTOMODE_MODE_SETTING_OSC_IN");
    goToOSCInSetMode.set(200, 200, 200, 20);
    goToOSCInSetMode.disableAllEvents();

    GoToConversionMode.setup("Conversion mode", "BTN_MSG_GOTOMODE_MODE_CONVERSION");
    GoToConversionMode.set(200, 200, 200, 20);
    GoToConversionMode.disableAllEvents();

    saveMidiOutPortSettings.setup("Save midi out port settings", "BTN_MSG_MIDI_OUT_PORT_SET");
    saveMidiOutPortSettings.set(200, 200, 200, 20);
    saveMidiOutPortSettings.disableAllEvents();

    saveMidiOutChannelSettings.setup("Save midi out channel settings", "BTN_MSG_MIDI_OUT_CHANNEL_SET");
    saveMidiOutChannelSettings.set(200, 200, 200, 20);
    saveMidiOutChannelSettings.disableAllEvents();

    saveMidiInPortSettings.setup("Save midi in port settings", "BTN_MSG_MIDI_IN_PORT_SET");
    saveMidiInPortSettings.set(200, 200, 200, 20);
    saveMidiInPortSettings.disableAllEvents();

    saveMidiInChannelSettings.setup("Save midi in channel settings", "BTN_MSG_MIDI_IN_CHANNEL_SET");
    saveMidiInChannelSettings.set(200, 200, 200, 20);
    saveMidiInChannelSettings.disableAllEvents();

    saveOSCOutPortSettings.setup("Save OSC out port settings", "BTN_MSG_OST_OUT_PORT_SET");
    saveOSCOutPortSettings.set(200, 200, 200, 20);
    saveOSCOutPortSettings.disableAllEvents();

    saveOSCOutIptSettings.setup("Save OSC out ip settings", "BTN_MSG_OST_OUT_IP_SET");
    saveOSCOutIptSettings.set(200, 200, 200, 20);
    saveOSCOutIptSettings.disableAllEvents();

    saveOSCInPortSettings.setup("Save OSC in port settings", "BTN_MSG_OSC_IN_PORT_SET");
    saveOSCInPortSettings.set(200, 200, 200, 20);
    saveOSCInPortSettings.disableAllEvents();
}

void ofApp::disableAllButtons() {
    goToMidiOutSetMode.disableAllEvents();

    goToMidiInSetMode.disableAllEvents();

    gotToOSCOutSetMode.disableAllEvents();

    goToOSCInSetMode.disableAllEvents();

    GoToConversionMode.disableAllEvents();

    saveMidiOutPortSettings.disableAllEvents();

    saveMidiOutChannelSettings.disableAllEvents();

    saveMidiInPortSettings.disableAllEvents();

    saveMidiInChannelSettings.disableAllEvents();

    saveOSCOutPortSettings.disableAllEvents();

    saveOSCOutIptSettings.disableAllEvents();

    saveOSCInPortSettings.disableAllEvents();
}

void ofApp::disableGlobalButtons() {
    goToMidiOutSetMode.disableAllEvents();

    goToMidiInSetMode.disableAllEvents();

    gotToOSCOutSetMode.disableAllEvents();

    goToOSCInSetMode.disableAllEvents();

    GoToConversionMode.disableAllEvents();
}

void ofApp::enableGlobalButtons() {
    goToMidiOutSetMode.enableAllEvents();

    goToMidiInSetMode.enableAllEvents();

    gotToOSCOutSetMode.enableAllEvents();

    goToOSCInSetMode.enableAllEvents();

    GoToConversionMode.enableAllEvents();
}
