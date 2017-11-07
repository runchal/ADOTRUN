#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
        void update();
        void updateValues(float _emotion, float _height, float _width);
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
    
    ofPolyline line;
    ofPolyline slopeLine;
    ofxFloatSlider emotion;
    ofxFloatSlider height;
    ofxFloatSlider width;
    ofxPanel gui;
		
};
