#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    float fibonacci();
    float getRandomLoc(float pos, float radius);
    void resetCanvas();
    
    ofPoint fibNums;
    ofPoint startLoc;
    
    int mode = 0;
    bool drawGui = true;
    
    ofxPostProcessing post;
    ofEasyCam cam;
    
    ofxPanel gui;
    ofxToggle stateFxaaPass;
    ofxToggle stateBloomPass;
    ofxToggle stateDofPass;
    ofxToggle stateKaleidoscopePass;
    ofxToggle stateNoiseWarpPass;
    ofxToggle statePixelatePass;
    ofxToggle stateEdgePass;
    ofxToggle stateVerticalTiltShifPass;
    ofxToggle stateGodRaysPass;
    
    vector<ofxToggle> statePass;
};
