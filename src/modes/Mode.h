//
//  Mode.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#pragma once

#include "ofMain.h"
#include "stdio.h"
#include "simpleButton.h"   
#include "colours.h"

class Mode {
    protected:
	ofTrueTypeFont & font;
	ofJson & settings;
	std::string title;
    Colours & colours;


public:
	Mode(ofTrueTypeFont & fontRef, ofJson & settingsRef, Colours & coloursRef);
	virtual ~Mode();

    virtual void setup() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
    virtual void keyPressed(int key) = 0;

};
