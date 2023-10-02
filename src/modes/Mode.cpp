//
//  Mode.cpp
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#include "Mode.h"

Mode::Mode(ofTrueTypeFont & fontRef, ofJson & settingsRef)
	: font(fontRef)
	, settings(settingsRef) { 
}

Mode::~Mode() {

}