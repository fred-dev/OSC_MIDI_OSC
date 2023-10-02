//
//  MidiOutSetupMode.hpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "modes/Mode.h"
#include <stdio.h>

class MidiOutSetupMode : public Mode {
private:
	std::string title;

public:
	MidiOutSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef);
	~MidiOutSetupMode();

	void setup() ;
	void draw() ;
	void update() ;
	void exit() ;
	void keyPressed(int key) ;
	simpleButton saveMidiOutPortSettings;
	simpleButton saveMidiOutChannelSettings;
	void selectPort(ofJson & ports, ofJson & currentPort, int direction);
	void selectChannel(ofJson & channel, int direction);
};
