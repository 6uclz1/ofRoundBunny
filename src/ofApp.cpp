#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    cam.setDistance(500);
    
    ofBackground(10, 10, 10);
    
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    ofSetVerticalSync( true );
    mesh.load( "lofi-bunny.ply" );
    
    soundStream.printDeviceList();
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    output.setName("bunny");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
    if (scaledVol <= 0.10) {
        scaledVol == scaledVol;
    } else {
        scaledVol == -scaledVol;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofNoFill();
    
    ofBackgroundGradient(ofColor(32+scaledVol*100*30), ofColor(0+scaledVol*100*30));
    
    float rotY = 0.5 * ofGetFrameNum() + scaledVol * 100 * 10; // ofRotate takes degrees
    
    cam.begin();
    
    ofRotateY(rotY); // draw them with rotation
    
    glPointSize(3);
    
    ofSetColor(255 - scaledVol * 100 * 90, 255 - scaledVol * 100 * 90, 255 - scaledVol * 100 * 100);
    mesh.drawVertices();
    
    ofSetColor(200 - scaledVol * 100 * 90, 200 - scaledVol * 100 * 90, 200 - scaledVol * 100 * 100);
    mesh.drawWireframe();
    
    ofFill();
    
    output.publishScreen();
    
    cam.end();
    
}


void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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
