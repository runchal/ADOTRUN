#include "ofApp.h"
#include <CoreServices/CoreServices.h>
#include <stdlib.h>


//--------------------------------------------------------------

void fileChangeCallback(ConstFSEventStreamRef streamRef,
                        void *clientCallBackInfo,
                        size_t numEvents,
                        void *eventPaths,
                        const FSEventStreamEventFlags eventFlags[],
                        const FSEventStreamEventId eventIds[]) {
    ifstream inFile;
    inFile.open("/Users/wircho/Desktop/of_v0.9.8_osx_release/examples/ADOTRUN/DearVera_ADOTRUN/face_data/data.txt");
    if (!inFile) {
        return;
    }
    float values[128];
    float value;
    int counter = 0;
    ostringstream str("");
    while (inFile >> value) {
        values[counter] = value;
        counter += 1;
        str << "/";
        str << value;
    }
    printf("%s", str.str().c_str());
}

void startListeningToFile() {
    CFStringRef mypath = CFSTR("/Users/wircho/Desktop/of_v0.9.8_osx_release/examples/ADOTRUN/DearVera_ADOTRUN/face_data");
    CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&mypath, 1, NULL);
    void *callbackInfo = NULL; // could put stream-specific data here.
    FSEventStreamRef stream;
    CFAbsoluteTime latency = 3.0; /* Latency in seconds */
    
    stream = FSEventStreamCreate(NULL,
                                 &fileChangeCallback,
                                 (FSEventStreamContext *)callbackInfo,
                                 pathsToWatch,
                                 kFSEventStreamEventIdSinceNow, /* Or a previous event ID */
                                 latency,
                                 kFSEventStreamCreateFlagNone /* Flags explained in reference */
                                 );
    
    FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
    
    FSEventStreamStart(stream);
}

void ofApp::setup(){
    
    //it's in reproducing the art that I realize that I am about to get my ass kicked and that the work I need to focus on is my emotional state of being and how attempting to reproduce mastery makes me feel
    
    //how do I feel about the piece currently? Its still not human enough

    ofBackground(250);
    gui.setup();
    gui.add(emotion.setup("emotion", 0.5,0,20));
    gui.add(height.setup("height",5,1,20));
    gui.add(width.setup("width",20,10,200));
    
    startListeningToFile();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSeedRandom(0); // put this in to fix the emotional scale of response
    
    ofSetColor(0);
    float vertSpacer = 40;
    
    //line drawing
    
    for (int h = 0; h < 40; h++){
        ofPolyline myLine;
        for (int i = 0; i < 80; i++){
            
//            float yDown = ofRandom(20,40);
            float yDown = ofRandom(height);
            float yUp = ofRandom(20);
            float xForward = ofRandom(width);
            float xBack = ofRandom(10);
            
            //what this is does is take a percentage of the range to map and create more chaos later in the function. Is this linear?
//            float pct = ofMap(i, 0, 20, 0, 1); //the more the second value is increased, the more controlled this gets
            
            float pct = ofMap(i*(h*500*0.01), 0, 1000, 0, 1); //the more the second value is increased, the less jagged the line gets
            
            if (i % 2 == 0){
//                float x = 10 + i * 20 + ofRandom(-pct*10, pct*10);//                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10); // this is before i made a param for emotion. It created sort of an effect where the program got more emotional the more they were writing to you
                float x = xBack + i * 20 + ofRandom(-emotion*10, emotion*10);
                // one thing with this param being coded in this way is that it makes the emotional state of the piece constant — it is more a reflection of mental health than it is of an emotional response to a person which grows stronger over time
                float y = -yDown + (i*0) + h * vertSpacer;
                myLine.addVertex(x,y);
            } else {
//                float x = 60 + i * 20 + ofRandom(-pct*10, pct*10); // this is before i made a param for emotion. It created sort of an effect where the program got more emotional the more they were writing to you
                float x = xBack + xForward + i * 20 + ofRandom(-emotion*10, emotion*10); // one thing with this param is that it makes the emotional state of the piece constant — it is more a reflection of mental health than it is of an emotional response to a person which grows stronger over time
                float y = yDown + (i*0) +  h * vertSpacer;
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
