// Created by Mikhail S. Kataev (lpestl)
// Copyright © 2023 Mikhail S. Kataev. All rights reserved.

#pragma once

#include "ofMain.h"
#include "ofxPanel.h"
#include "ofxSlider.h"
#include "ofxSliderGroup.h"

class ofFluidSystem
{
public:
    void setup();
    void update();
    void draw();

	void resolveCollisions(ofVec2f* position, ofVec2f* velocity);
	    
private:
	int numParticles = 288;
	float particleSpacing = 0.1f;
	
	std::vector<ofVec2f> positions_;
	std::vector<ofVec2f> velocities_;
	
	ofxPanel gui_;
    ofxFloatSlider gravity_;
    ofxFloatSlider particleSize_;
	ofxFloatSlider collisionDamping_;
	ofxVec2Slider boundsSize_; 
};
