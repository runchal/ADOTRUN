#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //it's in reproducing the art that I realize that I am about to get my ass kicked and that the work the

    ofBackground(250);
}

//--------------------------------------------------------------
void ofApp::update(){
    


}

//--------------------------------------------------------------
void ofApp::draw(){

    // i wrote this code because FUCK COORDINATE SYSTEMS and I was trying to understand them
    // i am directionally dyslexic I think which makes the whole thing much harder
    
//    
//    ofSetColor(10);
//    ofPoint posA = ofPoint(10,40);
//    ofPoint posB = ofPoint(60,10);
//    ofPoint posC = ofPoint(30,40);
//    ofPoint posD = ofPoint(80,10);
//    ofPoint posE = ofPoint(50,40);
//    ofPoint posF = ofPoint(100,10);
//    ofPoint posG = ofPoint(70,40);
//    
//    ofDrawLine(posB, posA);
//    ofDrawLine(posB, posC);
//    ofDrawLine(posC, posD);
//    ofDrawLine(posD, posE);
//    ofDrawLine(posE, posF);
    
//    ofSetColor(0);
//    ofPolyline myLine;
//    for (int i = 0; i < 40; i++){
//        if (i % 2 == 0){
//            float x = 10 + i * 20;
//            float y = 40 + (i*0);
//            myLine.addVertex(x,y);
//        } else {
//            float x = 60 + i * 20;
//            float y = 10 + (i*0);
//            myLine.addVertex(x,y);
//        }
//    }
//    myLine.draw();
    

    
    
    // a:
    
//    ofSeedRandom(0);
//    ofSetColor(0);
//    ofPolyline myLine;
//    for (int i = 0; i < 40; i++){
//        if (i % 2 == 0){
//            float x = 10 + i * 20 + ofRandom(-10,10);
//            float y = 40 + (i*0);
//            myLine.addVertex(x,y);
//        } else {
//            float x = 60 + i * 20 + ofRandom(-10,10);
//            float y = 10 + (i*0);
//            myLine.addVertex(x,y);
//        }
//    }
//    myLine.draw();
    
    // b:
    
//    ofSeedRandom(0);
//    ofSetColor(0);
//    ofPolyline myLine;
//    float x = 0;
//    for (int i = 0; i < 40; i++){
//        if (i % 2 == 0){
//            float x2 = 10 + x;
//            float y = 40 + (i*0);
//            myLine.addVertex(x2,y);
//        } else {
//            float x2 = 60 + x;
//            float y = 10 + (i*0);
//            myLine.addVertex(x2,y);
//        }
//        
//        x += ofRandom(mouseX,mouseY);
//        
//    }
//    myLine.draw();
    
    
    //ZACH: looks like he would use sin or ofNoise. Some of it is a linear progression (a distance function). Approach it as a linear problem. Linear is good
    //with sin, for non-linear functions you want more noise, ofNoise is like sin in that you can pass in continuous points, but you're going to get more noisy results periodically

    // ZACH: need to look at randomness, may want to add a counter to X, fixed positions that are offset from slightly to this
    
    
//    ofSetColor(0);
//    int vertSpacer = 30;
//    
//    for (int j = 0; j < 10; j++){
//        ofPolyline myLine;
//        for (int i = 0; i < 40; i++){
//            if (i % 2 == 0){
//                float x = 10 + i * 20 + ofRandom(-5,5);
//                float y = 40 + (i*0) + j*vertSpacer;
//                myLine.addVertex(x,y);
//            } else {
//                float x = 60 + i * 20 + ofRandom(-5,5);
//                float y = 10 + (i*0) + j*vertSpacer;
//                myLine.addVertex(x,y);
//            }
//        }
//        myLine.draw();
//    }
    
    
//    ofSeedRandom(0);
    
    ofSetColor(0);
    float vertSpacer = 40;
    
    //color chooser
//    ofBackground(255);
//    ofSetColor(ofMap(sin(ofGetElapsedTimef()) * 2, -1, 1, 30, 200),
//               ofMap(sin(ofGetElapsedTimef()) * 3, -1, 1, 30, 200),
//               ofMap(sin(ofGetElapsedTimef()) * 6, -1, 1, 30, 200));
//
    
//    //line drawing
//    
//    for (int h = 0; h < 40; h++){
//        ofPolyline myLine;
//        for (int i = 0; i < 80; i++){
//            
//            //what this is does is take a percentage of the range to map and create more chaos later in the function. Is this linear?
////            float pct = ofMap(i, 0, 20, 0, 1); //the more the second value is increased, the more controlled this gets
//            
//            float pct = ofMap(i*(h*mouseX*0.01), 0, 1000, 0, 1); //the more the second value is increased, the less jagged the line gets
//            
//            if (i % 2 == 0){
//                float x = 10 + i * 20 + ofRandom(-pct*10, pct*10);
//                float y = 40 + (i*0) + h * vertSpacer;
//                myLine.addVertex(x,y);
//            } else {
//                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10);
//                float y = 10 + (i*0) + h * vertSpacer;
//                myLine.addVertex(x,y);
//            }
//        myLine.draw();
//        }
//    }
////}
    
    
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
