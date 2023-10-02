//
//  MidiOutSetupMode.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "modes/Mode.h"
#include <stdio.h>

class MidiOutSetupMode : public Mode {
private:
    std::string title = "MIDI out setup";;

public:
	MidiOutSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef);
	~MidiOutSetupMode();

	void setup() override;
	void draw() override;
	void update() override;
	void exit() override;
	void keyPressed(int key) override{ }

	void _keyPressed(ofKeyEventArgs & e);
	simpleButton saveMidiOutPortSettings;
	simpleButton saveMidiOutChannelSettings;
    simpleButton GoToConversionMode;
    
	void selectPort(ofJson & ports, ofJson & currentPort, int direction);
	void selectChannel(ofJson & channel, int direction);
};
