//
//  MidiInSetupMode.hpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//



#include <stdio.h>
#include "modes/Mode.h"

class MidiInSetupMode : public Mode {
private:
	std::string title;


public:
	MidiInSetupMode(ofTrueTypeFont & fontRef, ofJson & settingsRef);
	~MidiInSetupMode();

    void setup() ;
    void draw() ;
    void update() ;
    void exit() ;
    void keyPressed(int key) ;
	simpleButton saveMidiInPortSettings;
	simpleButton saveMidiInChannelSettings;
	void selectPort(ofJson & ports, ofJson & currentPort, int direction);
	void selectChannel(ofJson & channel, int direction);
};



