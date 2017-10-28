#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // All examples share data files from example-data, so setting data path to this folder
    // This is only relevant for the example apps
    ofSetDataPathRoot(ofFile(__BASE_FILE__).getEnclosingDirectory()+"../../model/");
    
    // Setup grabber
    grabber.setup(1280,720);
    
    // Setup tracker
    tracker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
    // Update tracker when there are new frames
    if(grabber.isFrameNew()){
        tracker.update(grabber);
    }
    
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE).draw();
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE).draw();
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYEBROW).draw();
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYEBROW).draw();
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::NOSE_BRIDGE).draw();
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::NOSE_BASE).draw();
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::INNER_MOUTH).draw();
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::OUTER_MOUTH).draw();
    //    instance.getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::JAW).draw();
    
    
    //    ofxFaceTracker2Landmarks::ALL_FEATURES

    //this is attempting to create a vector whose purpose will be to store the values of 100 number that represent the distance between the eyes of one person
    vector <float> eyeDistances;
//    eyeDistances.assign(100,0.0f);

//    //this is attempting to get the distance between two eyes
//        for (int i = 0; i < tracker.getInstances().size(); i++){
//            ofRectangle right_eye_boundingbox = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE).getBoundingBox();
//            ofPoint p = ofPoint(right_eye_boundingbox.x + right_eye_boundingbox.width / 2, right_eye_boundingbox.y + right_eye_boundingbox.height / 2);
//            ofRectangle left_eye_boundingbox = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE).getBoundingBox();
//            ofPoint q = ofPoint(left_eye_boundingbox.x + left_eye_boundingbox.width / 2, left_eye_boundingbox.y + left_eye_boundingbox.height / 2);
//            //this is attempting to only capture the first 100 objects
//            if (p.distance(q) > 0){
//            for (int j = 0; j < 100; j++){
//                eyeDistances.push_back(p.distance(q));
//                if (eyeDistances.size() == 100){
//                    break;
//                }
//
//            }
//            }
//        }
    
    float eyeDistanceTotal = 0.0f;
    int count = 0;
    
    for (int i = 0; i < tracker.getInstances().size(); i++){
        ofRectangle right_eye_boundingbox = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE).getBoundingBox();
        ofPoint p = ofPoint(right_eye_boundingbox.x + right_eye_boundingbox.width / 2, right_eye_boundingbox.y + right_eye_boundingbox.height / 2);
        ofRectangle left_eye_boundingbox = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE).getBoundingBox();
        ofPoint q = ofPoint(left_eye_boundingbox.x + left_eye_boundingbox.width / 2, left_eye_boundingbox.y + left_eye_boundingbox.height / 2);
        //this is attempting to only capture the first 100 objects
        
        eyeDistanceTotal += p.distance(q);  //Same as eyeDistanceTotal = eyeDistanceTotal + p.distance(q);
        count++;  // count = count + 1;
        if(count == 100) {
            break;
        }
    }
    
    
    float eyeDistanceAverage = eyeDistanceTotal / count;
    
    cout << eyeDistanceAverage << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Draw camera image
//    grabber.draw(0, 0);

    // Draw tracker landmarks
//    tracker.drawDebug();

    // Draw estimated 3d pose
//    tracker.drawDebugPose();

    // get the ability to draw pupils for more than one person at the same time
    if (tracker.getInstances().size() > 0){
        for (int i = 0; i < tracker.getInstances().size(); i++){
            ofRectangle right_eye_boundingbox = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE).getBoundingBox();
            ofPoint p = ofPoint(right_eye_boundingbox.x + right_eye_boundingbox.width / 2, right_eye_boundingbox.y + right_eye_boundingbox.height / 2);
            ofDrawCircle(p, 10);
            ofRectangle left_eye_boundingbox = tracker.getInstances()[i].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE).getBoundingBox();
            ofPoint q = ofPoint(left_eye_boundingbox.x + left_eye_boundingbox.width / 2, left_eye_boundingbox.y + left_eye_boundingbox.height / 2);
            ofDrawCircle(q, 10);
        }
    }



//    if (tracker.getInstances().size() > 0) {
//        ofRectangle right_eye_boundingbox = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE).getBoundingBox();
//        ofPoint p = ofPoint(right_eye_boundingbox.x + right_eye_boundingbox.width / 2, right_eye_boundingbox.y + right_eye_boundingbox.height / 2);
//        ofDrawCircle(p, 5);
//        ofRectangle left_eye_boundingbox = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE).getBoundingBox();
//        ofPoint q = ofPoint(left_eye_boundingbox.x + left_eye_boundingbox.width / 2, left_eye_boundingbox.y + left_eye_boundingbox.height / 2);
//        ofDrawCircle(q, 5);
//    }



    // Draw text UI
    ofDrawBitmapStringHighlight("Framerate : "+ofToString(ofGetFrameRate()), 10, 20);
    ofDrawBitmapStringHighlight("Tracker thread framerate : "+ofToString(tracker.getThreadFps()), 10, 40);

#ifndef __OPTIMIZE__
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!",10,60);
    ofSetColor(ofColor::white);
#endif
}

