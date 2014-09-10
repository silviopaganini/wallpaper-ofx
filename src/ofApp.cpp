#include "ofApp.h"

#define MAX_CIRCLES 400

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    
    ofSetBackgroundAuto(false);
    
    startLoc = ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    fibNums = ofPoint(0,1);
    
    gui.setup();
    gui.add(stateKaleidoscopePass.setup("Kaleidoscope", false));
    gui.add(stateBloomPass.setup("Bloom", false));
    gui.add(statePixelatePass.setup("Pixelate", false));
    gui.add(stateGodRaysPass.setup("GodRays", false));
    gui.add(stateDofPass.setup("DoF", false));
    gui.add(stateFxaaPass.setup("Fxaa", false));
    gui.add(stateNoiseWarpPass.setup("NoiseWarp", false));
    gui.add(stateEdgePass.setup("Edge", false));
    gui.add(stateVerticalTiltShifPass.setup("Vertical", false));
    gui.loadFromFile("settings.xml");
    
    post.init(ofGetWidth(), ofGetHeight());
    
    post.createPass<KaleidoscopePass>()->setEnabled(stateKaleidoscopePass);
    post.createPass<BloomPass>()->setEnabled(stateBloomPass);
    post.createPass<PixelatePass>()->setEnabled(statePixelatePass);
    post.createPass<GodRaysPass>()->setEnabled(stateGodRaysPass);
    post.createPass<DofPass>()->setEnabled(stateDofPass);
    post.createPass<FxaaPass>()->setEnabled(stateFxaaPass);
    post.createPass<NoiseWarpPass>()->setEnabled(stateNoiseWarpPass);
    post.createPass<EdgePass>()->setEnabled(stateEdgePass);
    post.createPass<VerticalTiltShifPass>()->setEnabled(stateVerticalTiltShifPass);
    
    statePass.push_back(stateKaleidoscopePass);
    statePass.push_back(stateBloomPass);
    statePass.push_back(statePixelatePass);
    statePass.push_back(stateGodRaysPass);
    statePass.push_back(stateDofPass);
    statePass.push_back(stateFxaaPass);
    statePass.push_back(stateNoiseWarpPass);
    statePass.push_back(stateEdgePass);
    statePass.push_back(stateVerticalTiltShifPass);
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    if(fibNums.x > MAX_CIRCLES)
    {
        fibNums.x = 0;
        fibNums.y = 1;
    }
    
    fibonacci();
}

float ofApp::fibonacci()
{
    int temp = fibNums.x;
    fibNums.x = fibNums.y;
    fibNums.y = temp + fibNums.x;
    return fibNums.y;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /*
    ofFill();
    ofSetColor(0,0,0,.1);
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
     */
   
    post.begin();
    
    ofLog() << ofToString(statePass.size());
    
    for (int s = 0; s < statePass.size(); s++) {
        post[s]->setEnabled(statePass[s]);
    }
    
    ofNoFill();
    ofSetColor(255, 255, 255, 200);
    ofSetLineWidth(2);
    ofSetCircleResolution(100);
    
    for (int i = 0; i<MAX_CIRCLES; i++) {
    
        float r = (ofNoise(ofRandom(MAX_CIRCLES), fibNums[1]) * MAX_CIRCLES);
        
        if(mode == 1)
        {
            ofCircle(getRandomLoc(startLoc.x, r), getRandomLoc(startLoc.y, r), r);
        } else
        {
            ofRect(getRandomLoc(startLoc.x, r) - r/2, getRandomLoc(startLoc.y, r) - r/2, r, r);
        }
        
    }
    
    post.end();
    
    if(drawGui) gui.draw();
}

float ofApp::getRandomLoc(float pos, float radius)
{
    //float factor = ofRandom(-fibNums[1], fibNums[1]);
    //float factor = 2;
    float factor = ofNoise(ofGetWindowWidth() / 2, ofGetWindowHeight()/ 2);
    return ofRandom(pos - radius / factor, pos + radius / factor);
    // +
}

void ofApp::resetCanvas()
{
    startLoc = ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    ofFill();
    ofSetColor(0,0,0,255);
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key)
    {
        case 'h':
            drawGui = !drawGui;
            break;
            
        case 's':
            ofSaveFrame();
            break;
        
        case 'r':
            resetCanvas();
            break;
        
        case 'w':
            resetCanvas();
            mode = mode == 1 ? 0 : 1;
            break;
            
        case 'f':
            
            ofToggleFullscreen();
            post.init(ofGetWidth(), ofGetHeight());
            resetCanvas();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
