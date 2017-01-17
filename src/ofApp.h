#pragma once

#include "ofMain.h"

#include "Grid.hpp"

class ofApp : public ofBaseApp {
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
	/*ofCamera x;*/
    Grid grid;
	ofEasyCam cam;			//initialize a cam object (ofEasycam can access _most_ ofCamera and ofNode functions from the online documentation)
	ofFpsCounter fps;		//fps counter object
							//ofTrueTypeFont	verdana14;
	int prevX;				//initialization of values used for continuous tracking of mousemovement for camera positioning
	int prevY;				//these two should be able to be deleted with Oculus Implementation
};
