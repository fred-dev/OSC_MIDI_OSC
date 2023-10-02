//
//  simpleButton.h
//  OSC_MIDI_OSC
//
//  Created by Fred Rodrigues on 02/10/2023.
//

#pragma once
#include "ofxMSAInteractiveObject.h"

#define IDLE_COLOR 0x2860bd
#define OVER_COLOR 0xbd5928
#define DOWN_COLOR 0xbd5928

class simpleButton : public ofxMSAInteractiveObject {
public:
	string buttonLabel;
	string buttonMessage;
	ofTrueTypeFont drawFont;

	void setup(string label, string message) {
		enableMouseEvents();
		enableKeyEvents();

		buttonLabel = label;
		buttonMessage = message;
		drawFont.load("frabk.ttf", 12);
	}

	void exit() {
	}

	void update() {
	}

	void draw() {
		ofPushStyle();

		if (isMousePressed()) {
			ofSetHexColor(DOWN_COLOR);
		} else if (isMouseOver()) {
			ofSetHexColor(OVER_COLOR);
		} else {
			ofSetHexColor(IDLE_COLOR);
		}

		ofNoFill();
		ofDrawRectRounded(x, y, width, height, 12 / 2);
		drawFont.drawString(buttonLabel, x + ((width - drawFont.getStringBoundingBox(buttonLabel, 0, 0).getWidth()) / 2), y + ((height - drawFont.getStringBoundingBox(buttonLabel, 0, 0).getHeight()) / 2) + drawFont.getStringBoundingBox(buttonLabel, 0, 0).getHeight());

		ofPopStyle();
	}

	virtual void onRollOver(int x, int y) {
	}

	virtual void onRollOut() {
	}

	virtual void onMouseMove(int x, int y) {
	}

	virtual void onDragOver(int x, int y, int button) {
	}

	virtual void onDragOutside(int x, int y, int button) {
	}

	virtual void onPress(int x, int y, int button) {
		ofSendMessage(buttonMessage);
	}

	virtual void onRelease(int x, int y, int button) {
	}

	virtual void onReleaseOutside(int x, int y, int button) {
	}

	virtual void keyPressed(int key) {
	}

	virtual void keyReleased(int key) {
	}
};
