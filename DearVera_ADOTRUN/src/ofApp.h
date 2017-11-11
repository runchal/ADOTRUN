#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <mutex>

class ofApp : public ofBaseApp{

	public:
		void setup();
        void update();
		void draw();

        void exit();
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
        void updateValues(int wordIndex, float _emotion, float _height, float _width, float _startLength1, float lengthMult1, float _startSlope1, float _flattenY1, float _emotion2, float _height2, float _width2, float r0, float g0, float b0, float r1, float g1, float b1, float r2, float g2, float b2);
        void reactToFaceValues();
        void draw0(int canvasX, int canvasY, int canvasWidth, int canvasHeight);
        void draw1(int canvasX, int canvasY, int canvasWidth, int canvasHeight);
        void draw2(int canvasX, int canvasY, int canvasWidth, int canvasHeight);
        void setWord(int i, const std::string& word);
        std::string getWord(int i);
        void drawTextCentered(const std::string& text, float x, float y);
    
    // Drawing 0
    float emotion;
    float height;
    float width;
    float r0, g0, b0;
    
    // Drawing 1
    ofPoint origin1;
    ofPoint pen1;
    ofPoint nextPen1;
    bool penSwitch1;
    float emotion1;
    float startLength1;
    float length1;
    float startSlope1;
    float lengthMult1;
    float angle1;
    float margin1;
    float flattenY1;
    float r1, g1, b1;
    
    // Drawing 2
    float emotion2;
    float height2;
    float width2;
    float r2, g2, b2;

//    ofxPanel gui;
    
    ofTrueTypeFont font;
    std::mutex wordsMtx;
    std::string words[3];
    std::string wordsNext[3];
    std::string wordsSet[3];
    bool wordsTargetAlpha[3] {true, true, true};
    float wordsTime[3] {0, 0, 0};
    
    static constexpr float fadeTime = 0.5f;
		
};
