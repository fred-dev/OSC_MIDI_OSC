//
//  OscOutSetupMode.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//



#include <stdio.h>

#include "Mode.h"

class OscOutSetupMode : public Mode {
private:
    // Member variables specific to MidiInMode
    std::string title;
    std::vector<std::string> ports;
    std::string currentPort;
    int channel;

public:
    OscOutSetupMode();
    ~OscOutSetupMode();

    void setup() override;
    void draw() override;
    void update() override;
    void exit() override;
    void keyPressed(int key) override;
};



