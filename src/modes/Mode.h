//
//  Mode.hpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//
class Mode {
public:
    Mode() {}
    virtual ~Mode() {}

    virtual void setup() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
    virtual void keyPressed(int key) = 0;
};
