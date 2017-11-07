#pragma once

#include "ofMain.h"
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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    float emotion;
    float startLength;
    float length;
    float startSlope;
    float slope;
    float angle;
    float margin;
    
    ofPoint origin;
 
    ofPolyline line;
//    ofxFloatSlider emotion;
//    ofxFloatSlider length;
//    ofxFloatSlider slope;
    ofxPanel gui;
    
    ofPoint pen;
    ofPoint nextPen;
    bool penSwitch;
  
    
    
		
};
