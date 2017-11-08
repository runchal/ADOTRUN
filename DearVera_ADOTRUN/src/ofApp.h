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
    
    private:
        void setUpServer();
        void updateValues(float _emotion, float _height, float _width, float _startLength1, float _startSlope1, float _emotion2, float _height2, float _width2);
        void reactToFaceValues();
        void draw0(int canvasX, int canvasY, int canvasWidth, int canvasHeight);
        void draw1(int canvasX, int canvasY, int canvasWidth, int canvasHeight);
        void draw2(int canvasX, int canvasY, int canvasWidth, int canvasHeight);
    
    // Drawing 0
    ofxFloatSlider emotion;
    ofxFloatSlider height;
    ofxFloatSlider width;
    
    // Drawing 1
    ofPoint origin1;
    ofPoint pen1;
    ofPoint nextPen1;
    bool penSwitch1;
    float emotion1;
    float startLength1;
    float length1;
    float startSlope1;
    float angle1;
    float margin1;
    
    // Drawing 2
    ofxFloatSlider emotion2;
    ofxFloatSlider height2;
    ofxFloatSlider width2;

    
    
    ofxPanel gui;
		
};
