#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    ofBackground(255);
//    gui.setup();
//    gui.add(emotion.setup("emotion", 0.5,0,20));
//    gui.add(length.setup("length",5,1,20));
//    gui.add(slope.setup("slope",20,10,200));
    
    pen.set(0,0);
    nextPen.set(0,0);
    penSwitch = true;
    
    emotion = 10;
    startLength = 35;
    startSlope = 0.5;
    angle = atan(slope) * 1;
    margin = 30;
    origin.set(margin,margin*3);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(0);
    ofSeedRandom(1);
    while (origin.y < ofGetHeight() - margin){
        pen.x = origin.x;
        pen.y = origin.y;
      //  ofPolyline line;
        
        while (origin.x < ofGetWidth() - margin){
            float length;
            float slope;
            if (!penSwitch){
                slope = startSlope - ofRandom(10)/20;
            }
            else {
                slope = startSlope + ofRandom(10)/20;
            }
            angle = atan(slope);
            length = ofRandom(startLength) + 5;
            
            if ((origin.y - pen.y) > 10){
                if (!penSwitch){
                    length *= 2;
                }
                else {
                    length *=0.5;
                }
            }
            
            if ((origin.y - pen.y) < -10) {
                if (!penSwitch){
                    length *= 2;
                }
                else{
                    length *=0.5;
                }
            }
            
            float xChange;
            float yChange;
            if (!penSwitch){
                xChange = cos(angle)*length;
            }
            else{
                xChange  = -cos(angle)*length;
            }
            
            if (!penSwitch){
                yChange = sin(angle)*length * 0.5;
            }
            else{
                yChange  = -sin(angle)*length * 0.5;
            }
            
            nextPen.x = pen.x + xChange;
            nextPen.y = pen.y + yChange;
            ofDrawLine(pen.x, pen.y, nextPen.x, nextPen.y);
           // line.addVertex(pen.x, pen.y);
            //line.addVertex(nextPen.x, nextPen.y);
            
            pen.x = nextPen.x;
            pen.y = nextPen.y;
            penSwitch = !penSwitch;
            origin.x += xChange;
        
        
        }
        origin.x = margin;
        origin.y += 60;
       // line.draw();
    }
    origin.y = margin*3;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
