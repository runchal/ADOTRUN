#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //it's in reproducing the art that I realize that I am about to get my ass kicked and that the work the

    ofBackground(250);
    gui.setup();
    gui.add(emotion.setup("emotion", 0.5,0,20));
}

//--------------------------------------------------------------
void ofApp::update(){
    


}

//--------------------------------------------------------------
void ofApp::draw(){

    
    
    
//    ofSeedRandom(0); // put this in to fix the emotional scale of response
    
    ofSetColor(0);
    float vertSpacer = 40;
    
    //line drawing
    
    for (int h = 0; h < 40; h++){
        ofPolyline myLine;
        for (int i = 0; i < 80; i++){
            
            //what this is does is take a percentage of the range to map and create more chaos later in the function. Is this linear?
//            float pct = ofMap(i, 0, 20, 0, 1); //the more the second value is increased, the more controlled this gets
            
            float pct = ofMap(i*(h*mouseX*0.01), 0, 1000, 0, 1); //the more the second value is increased, the less jagged the line gets
            
            if (i % 2 == 0){
//                float x = 10 + i * 20 + ofRandom(-pct*10, pct*10);//                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10); // this is before i made a param for emotion. It created sort of an effect where the program got more emotional the more they were writing to you
                float x = 10 + i * 20 + ofRandom(-emotion*10, emotion*10); // one thing with this param being coded in this way is that it makes the emotional state of the piece constant — it is more a reflection of mental health than it is of an emotional response to a person which grows stronger over time
                float y = 40 + (i*0) + h * vertSpacer;
                myLine.addVertex(x,y);
            } else {
//                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10); // this is before i made a param for emotion. It created sort of an effect where the program got more emotional the more they were writing to you
                float x = 60 + i * 20 + ofRandom(-emotion*10, emotion*10); // one thing with this param is that it makes the emotional state of the piece constant — it is more a reflection of mental health than it is of an emotional response to a person which grows stronger over time
                float y = 10 + (i*0) +  h * vertSpacer;
                myLine.addVertex(x,y);
            }
        myLine.draw();
        }
        
        gui.draw();
    }
//}
    
    
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
