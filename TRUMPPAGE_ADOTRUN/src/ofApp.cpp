#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    /*
     INSTRUCTIONS
     1. Change imgWidth
     2. Change imgHeight
     3. Change string dirName
     4. Change mix.save (this could be automated somehow but don't know how to combine strings in oF
    */
    
    imgWidth = 800;
    imgHeight = 1400;
    
    mix.allocate(imgWidth, imgHeight, OF_IMAGE_COLOR);
    ofDirectory dir;
    string dirName = "resizedtest4dot1";
    dir.listDir(dirName);
    
    int * pixelSum;
    pixelSum = new int[ imgWidth * imgHeight * 3];
    
    for (int i = 0; i<imgWidth*imgHeight*3; i++){
        pixelSum[i]=0;
    }
    
     dir.sort();
    
    for (int i = 0; i < dir.size(); i++){
        cout << "loading: " << dir.getPath(i) << endl; // this is not returning things that I want it to return.
        ofImage temp; // creates a temporary ofImage to store individual pixel data in the loops
        temp.setUseTexture(false); // this takes the temp ofImage thing and makes it not store the texture
        temp.load(dir.getPath(i)); // this will load in each image from the path.
        
        /*
         ofImage has texture, and texture uploads things to graphic cards and turning it off will make it not load to the graphic card and make it run faster
         */
        
        /* now we want to add to the pixel sum (the value of each first pixel) by creating a for loop
         that takes the red green and blue image, going to grab the data
         */
        
        for (int j = 0; j<imgWidth; j++){
            for (int k = 0; k < imgHeight; k++){ //Zach wants to point out that this is where you can get a lot of bugs in your code, when you have a for loop inside of for loop
                ofColor c = temp.getColor(j, k); // this is going though every single pixel and getting the color from that pixel. j,k are the pixel coordinates and what it's doing is getting the file from the folder associated with temp, and then getting the pixel color
                int index = (k * imgWidth + j)*3; // zach has this as funky math. As he explains, this is a one-dimensional array, we need to figure out where we are inside that one dimensional array, we are in a two dimensional for loop.
                pixelSum[index] += c.r;
                pixelSum[index+1] += c.g;
                pixelSum[index+2] += c.b;
                
                
            }
        }
        
        cout << "pixel sum of red for pixel 0 " << pixelSum[0] << endl;
        
    }
    
    for (int i = 0; i<imgWidth; i++){
        for (int j = 0; j < imgHeight; j++){
            ofColor c; // this initializes this
            int index = (j*imgWidth+i)*3;
            c.r = (float)pixelSum[index] / (float)dir.size();
            c.g = (float)pixelSum[index+1] / (float)dir.size();
            c.b = (float)pixelSum[index+2] / (float)dir.size();
            mix.setColor(i,j, c);
            
            
            
        }
    }
    
    mix.update();
    mix.save("trumppage_pass03.jpg", OF_IMAGE_QUALITY_BEST);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
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
